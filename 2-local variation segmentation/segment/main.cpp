#include <iostream>
#include <opencv2/opencv.hpp>

#include "segment-image.h"
#include "misc.h"
#include "image.h"

using namespace cv;
using namespace std;


// convert Mat to "image" datastructure used
image<rgb>* mat2Image(Mat img){

	image<rgb> *ret = new image<rgb>(img.cols,img.rows);

	for(int i=0; i<img.rows; i++){
		for(int j=0; j<img.cols; j++){
			rgb color;
			Vec3b intensity = img.at<Vec3b>(i,j);
			color.r = intensity.val[2];
			color.g = intensity.val[1];
			color.b = intensity.val[0];
			ret->data[i*img.cols + j] = color;
		}
	}
	return ret;
}


// convert "image" datastructure instance to opencv's Mat
Mat image2Mat(image<rgb>* img){
	int w = img->width();
	int h = img->height();
	Mat ret(Size(w,h),CV_8UC3);

	for(int i =0; i<h; i++){
		for(int j=0; j<w; j++){
			rgb color = img->data[i*w + j];
			ret.at<Vec3b>(i,j)[2] = color.r;
			ret.at<Vec3b>(i,j)[1] = color.g;
			ret.at<Vec3b>(i,j)[0] = color.b;
		}
	}
	return ret;
}


// run segmentation on Mat
Mat segmentMat(Mat img, float sigma, float k, int min_size) {
	int w = img.cols;
	int h = img.rows;
	Mat ret(Size(w,h),CV_8UC3);

	image<rgb> *new_img = mat2Image(img);
	int numccs;
	image<rgb> *segmented_image = segment_image(new_img, sigma, k, min_size, &numccs);
	ret = image2Mat(segmented_image);

	delete new_img;
	delete segmented_image;
	return ret;
}


// global trackbar values
int sigma_slider = 50;
const int sigma_slider_max = 100;
int k_slider = 500;
const int k_slider_max = 1000;
int min_size_slider = 20;
const int min_size_slider_max = 100;

Mat src;
Mat segmented_img;


// trackbar callback function
void trackbarCallback(int, void*) {
	float sigma = (double) sigma_slider/sigma_slider_max ;

	segmented_img = segmentMat(src,sigma,k_slider,min_size_slider);

	imshow("Segmented Image",segmented_img);
}


int main(){
	src = imread("image.jpg");

	namedWindow("Input Image", 1);
	namedWindow("Segmented Image", 1);
	createTrackbar( "Gaussian Sigma : " , "Segmented Image", &sigma_slider, sigma_slider_max, trackbarCallback );
	createTrackbar( "k ( Threshold ) : " , "Segmented Image", &k_slider, k_slider_max, trackbarCallback);
	createTrackbar( "Min. Comp. Size: " , "Segmented Image", &min_size_slider, min_size_slider_max, trackbarCallback );
	
	imshow("Input Image",src);
	
	trackbarCallback(sigma_slider,0);

	waitKey();
}