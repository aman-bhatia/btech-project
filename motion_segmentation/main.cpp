#include <iostream>
#include <vector>
#include <math.h>
#include <cassert>
#include <opencv2/opencv.hpp>
#include "gco/GCoptimization.h"

using namespace std;
using namespace cv;


// Mat graphCutSegmentation(Mat &img, int num_labels){

// 	int width = img.cols;
// 	int height = img.rows;
// 	int num_pixels = width*height;

// 	// Apply kmeans clustering on image
// 	Mat samples(num_pixels, 3, CV_32F);
// 	for (int i=0;i<img.rows;i++)
// 		for (int j=0;j<img.cols;j++)
// 			for (int z=0;z<3;z++)
// 				samples.at<float>(j + i*img.cols, z) = img.at<Vec3b>(i,j)[z];

// 	Mat labels;
// 	int attempts = 2;
// 	Mat centers;
// 	TermCriteria criteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 100, 0.01);
// 	kmeans(samples, num_labels, labels, criteria, attempts, KMEANS_PP_CENTERS, centers);

// 	GCoptimizationGridGraph graph(width,height,num_labels);

// 	// first set up data costs individually
// 	for ( int i = 0; i < num_pixels; i++ ){
// 		for (int l = 0; l < num_labels; l++ ){
// 			Scalar v1(centers.at<float>(l,0),centers.at<float>(l,1),centers.at<float>(l,2));
// 			Scalar v2(samples.at<float>(i,0),samples.at<float>(i,1),samples.at<float>(i,2));
// 			double cost = norm(v1,v2, NORM_L2);
// 			graph.setDataCost(i,l,cost);
// 		}
// 	}

// 	// next set up smoothness costs individually
// 	int smoothness=1;
// 	for ( int l1 = 0; l1 < num_labels; l1++ ){
// 		for (int l2 = 0; l2 < num_labels; l2++ ){
// 			int cost = (l1==l2) ? 0 : smoothness;
// 			graph.setSmoothCost(l1,l2,cost);
// 		}
// 	}

// 	graph.expansion(1);
// 	Mat gc_image(img.size(), img.type());
// 	for(int i=0;i<img.rows;i++){
// 		for(int j=0;j<img.cols;j++){
// 			int cluster_idx = graph.whatLabel(j + i*img.cols);
// 			gc_image.at<Vec3b>(i,j)[0] = centers.at<float>(cluster_idx, 0);
// 			gc_image.at<Vec3b>(i,j)[1] = centers.at<float>(cluster_idx, 1);
// 			gc_image.at<Vec3b>(i,j)[2] = centers.at<float>(cluster_idx, 2);
// 		}
// 	}
// 	return gc_image;
// }


void track(char* video_path){

	VideoCapture cap(video_path);
	assert(cap.isOpened());

	Mat img1, img2, img1_gray, img2_gray, flow;

	int max_frames = cap.get(CAP_PROP_FRAME_COUNT);

	int resize_factor = 2;
	cap >> img1;
	resize(img1,img1,img1.size()/resize_factor);
	// GaussianBlur(img1,img1, Size(5,5), 1);
	cvtColor(img1, img1_gray, COLOR_BGR2GRAY);

	Vec3b* white = new Vec3b(255,255,255);
	Vec3b* black = new Vec3b(0,0,0);
	Vec3b* red = new Vec3b(0,0,255);
	int mag_thresh = 0.4;
	
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
				if (mag<1){ mag=0; theta=0;}
				samples.at<float>(y + x*flow.rows, 0) = mag;
				samples.at<float>(y + x*flow.rows, 1) = theta;
			}
		}

		int num_labels = 3;
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
				if (cluster_idx==0) clr = black;
				else if (cluster_idx==1) clr = white;
				else if (cluster_idx==2) clr = red;
				
				if (cluster_idx != biggest_cluster_index)
					img2.at<Vec3b>(y,x) = *clr;
			}
		}

		resize(img2,img2,Size(resize_factor*width, resize_factor*height));
		imshow( "Motion Segmentation", img2 );

/*
		// make graph
		int smoothness = 1;
		GCoptimizationGridGraph *graph = new GCoptimizationGridGraph(width,height,num_labels);

		// first set up data costs individually
		for ( int i = 0; i < num_pixels; i++ ){
			for (int l = 0; l < num_labels; l++ ){
				Scalar v1(centers.at<float>(l,0),centers.at<float>(l,1));
				Scalar v2(samples.at<float>(i,0),samples.at<float>(i,1));
				double cost = norm(v1,v2, NORM_L2);
				graph->setDataCost(i,l,cost);
			}
		}

		// next set up smoothness costs individually
		for ( int l1 = 0; l1 < num_labels; l1++ ){
			for (int l2 = 0; l2 < num_labels; l2++ ){
				int cost = (l1==l2) ? 0 : smoothness;
				graph->setSmoothCost(l1,l2,cost);
			}
		}

		cout << "Before optimization energy is " << graph->compute_energy() << endl;
		graph->expansion(1);
		cout << "After optimization energy is " << graph->compute_energy() << endl;

		for(int i=0;i<height;i++){
			for(int j=0;j<width;j++){
				int cluster_idx = graph->whatLabel(i + j*height);

				if (cluster_idx==0) clr = black;
				else if (cluster_idx==1) clr = white;
				else if (cluster_idx==2) clr = red;
				
				img2.at<Vec3b>(i,j) = *clr;
			}
		}

		delete graph;

		resize(img2,img2,Size(resize_factor*width, resize_factor*height));
		imshow("Motion Segmentation",img2);

*/
		char c = (char)waitKey(1);
		if(c == 27) break;
	}
	destroyAllWindows();
}


int main(int argc, char** argv){
	track(argv[1]);
}