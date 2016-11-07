#include "motion_seg.h"
#include <map>

using namespace std;
using namespace cv;

int num_moving_objects = 1;
float mag_thresh = 1.0;

void track(string video_path){

    VideoCapture cap(video_path);
    assert(cap.isOpened());

    Mat img1, img2, img1_gray, img2_gray, flow;

    int resize_factor = 2;
    cap >> img1;
    resize(img1,img1,img1.size()/resize_factor);
    cvtColor(img1, img1_gray, COLOR_BGR2GRAY);

    map<int, Vec3b*> color_map;
    color_map[0] = new Vec3b(0,0,255);
    color_map[1] = new Vec3b(0,255,0);
    color_map[2] = new Vec3b(0,255,255);
    color_map[3] = new Vec3b(255,0,0);
    color_map[4] = new Vec3b(255,255,255);
    color_map[5] = new Vec3b(0,0,0);

    while(true){

        cap >> img2;
        if (img2.data==NULL) break;
        imshow("Original",img2);
        resize(img2,img2,img2.size()/resize_factor);

        cvtColor(img2, img2_gray, COLOR_BGR2GRAY);
        calcOpticalFlowFarneback(img1_gray, img2_gray, flow, 0.5, 3, 15, 3, 5, 1.2, 0);
        cvtColor(img2, img1_gray, COLOR_BGR2GRAY);

        Mat uv[2];
        split(flow,uv);

        //calculate angle and magnitude
        Mat magnitude, angle;
        cartToPolar(uv[0], uv[1], magnitude, angle, true);


        int width = flow.cols;
        int height = flow.rows;
        int num_pixels = width*height;

        // Apply kmeans clustering on image
        Mat samples(flow.rows * flow.cols, 2, CV_32F);
        for( int y = 0; y < flow.rows; y++ ){
            for( int x = 0; x < flow.cols; x++ ){
                double mag = magnitude.at<float>(y,x);
                double theta = angle.at<float>(y,x);
                if (mag<=mag_thresh){ mag=0; theta=0;}
                else mag *= 3;
                samples.at<float>(y + x*flow.rows, 0) = mag;
                samples.at<float>(y + x*flow.rows, 1) = theta;
            }
        }

        int num_labels = 1 + num_moving_objects;
        Mat labels;
        int attempts = 2;
        Mat centers;
        kmeans(samples, num_labels, labels, TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 30, 0.001), attempts, KMEANS_PP_CENTERS, centers );

        // find out biggest cluster
        int temp[num_labels];
        for (int i=0;i<num_labels;i++)
            temp[i] = 0;

        for (int i=0;i<num_pixels;i++)
            temp[labels.at<int>(i,0)]++;

        int biggest_cluster_index = 0;
        for (int i=1;i<num_labels;i++){
            if (temp[i] > temp[biggest_cluster_index]) biggest_cluster_index = i;
        }

        // show kmeans image
        Vec3b* clr;
        for( int y = 0; y < flow.rows; y++ ){
            for( int x = 0; x < flow.cols; x++ ){
                int cluster_idx = labels.at<int>(y + x*flow.rows,0);
                clr = color_map[cluster_idx];

                if (cluster_idx != biggest_cluster_index)
                    img2.at<Vec3b>(y,x) = *clr;
            }
        }

        resize(img2,img2,Size(resize_factor*width, resize_factor*height));
        putText(img2, "Threshold  = " + to_string(mag_thresh), Point(10,25), 1, 1.3, Scalar(0,0,255),2);
        putText(img2, "Moving Obj = " + to_string(num_moving_objects), Point(10,45), 1, 1.3, Scalar(0,0,255),2);
        imshow( "Motion Segmentation", img2 );

        char c = (char)waitKey(1);
        if(c == 27) break;
        else if (c=='i') mag_thresh += 0.1;
        else if (c=='d') mag_thresh -= 0.1;
        else if (c==49) num_moving_objects = 1;
        else if (c==50) num_moving_objects = 2;
        else if (c==51) num_moving_objects = 3;
        else if (c==52) num_moving_objects = 4;
        else if (c==53) num_moving_objects = 5;
    }
    destroyAllWindows();
}



motion_seg::motion_seg(std::string vpath)
{
    track(vpath);
}
