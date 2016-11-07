#include "bg_sub.h"

using namespace std;
using namespace cv;

bg_sub::bg_sub(string _video_path)
{
    video_path = _video_path;
}

void bg_sub::processVideo() {
    VideoCapture capture(video_path);
    if(!capture.isOpened()){
        cout << "Unable to open video file : " << video_path << endl;
        return;
    }

    Mat img;
    Mat fgMask;
    Ptr<BackgroundSubtractor> pMOG2 = createBackgroundSubtractorMOG2();

    while(true){
        capture >> img;
        if(img.data == NULL) break;

        pMOG2->apply(img,fgMask);

        stringstream ss;
        rectangle(img, cv::Point(10, 2), cv::Point(100,20),cv::Scalar(255,255,255), -1);
        ss << capture.get(CAP_PROP_POS_FRAMES);
        string frameNumberString = ss.str();
        putText(img, frameNumberString.c_str(), cv::Point(15, 15),FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));

        imshow("Frame", img);
        imshow("FG Mask", fgMask);

        char c = waitKey(30);
        if (c==27) break;
    }
    capture.release();
    destroyAllWindows();
    return;
}
