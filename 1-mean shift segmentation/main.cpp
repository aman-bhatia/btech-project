#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

TermCriteria criteria(TermCriteria::MAX_ITER + TermCriteria::EPS, 30, 0.1);
int spatial_radius = 20;
int range_radius = 64;

int main(){

	Mat src = imread("test.jpg");

	Mat dst;
	
	pyrMeanShiftFiltering(src, dst, spatial_radius, range_radius, 0, criteria);

	imwrite("output.jpg", dst);
}