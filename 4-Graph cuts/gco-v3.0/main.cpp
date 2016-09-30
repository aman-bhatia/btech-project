//////////////////////////////////////////////////////////////////////////////
// Example illustrating the use of GCoptimization.cpp
//
/////////////////////////////////////////////////////////////////////////////
//
//  Optimization problem:
//  is a set of sites (pixels) of width 10 and hight 5. Thus number of pixels is 50
//  grid neighborhood: each pixel has its left, right, up, and bottom pixels as neighbors
//  7 labels
//  Data costs: D(pixel,label) = 0 if pixel < 25 and label = 0
//            : D(pixel,label) = 10 if pixel < 25 and label is not  0
//            : D(pixel,label) = 0 if pixel >= 25 and label = 5
//            : D(pixel,label) = 10 if pixel >= 25 and label is not  5
// Smoothness costs: V(p1,p2,l1,l2) = min( (l1-l2)*(l1-l2) , 4 )
// Below in the main program, we illustrate different ways of setting data and smoothness costs
// that our interface allow and solve this optimizaiton problem

// For most of the examples, we use no spatially varying pixel dependent terms. 
// For some examples, to demonstrate spatially varying terms we use
// V(p1,p2,l1,l2) = w_{p1,p2}*[min((l1-l2)*(l1-l2),4)], with 
// w_{p1,p2} = p1+p2 if |p1-p2| == 1 and w_{p1,p2} = p1*p2 if |p1-p2| is not 1


#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>
#include "gco/GCoptimization.h"
#include <opencv2/opencv.hpp>

/*

struct ForDataFn{
	int numLab;
	int *data;
};


int smoothFn(int p1, int p2, int l1, int l2)
{
	if ( (l1-l2)*(l1-l2) <= 4 ) return((l1-l2)*(l1-l2));
	else return(4);
}

int dataFn(int p, int l, void *data)
{
	ForDataFn *myData = (ForDataFn *) data;
	int numLab = myData->numLab;
	
	return( myData->data[p*numLab+l] );
}



////////////////////////////////////////////////////////////////////////////////
// smoothness and data costs are set up one by one, individually
// grid neighborhood structure is assumed
//
void GridGraph_Individually(int width,int height,int num_pixels,int num_labels)
{

	int *result = new int[num_pixels];   // stores result of optimization



	try{
		GCoptimizationGridGraph *gc = new GCoptimizationGridGraph(width,height,num_labels);

		// first set up data costs individually
		for ( int i = 0; i < num_pixels; i++ )
			for (int l = 0; l < num_labels; l++ )
				if (i < 25 ){
					if(  l == 0 ) gc->setDataCost(i,l,0);
					else gc->setDataCost(i,l,10);
				}
				else {
					if(  l == 5 ) gc->setDataCost(i,l,0);
					else gc->setDataCost(i,l,10);
				}

		// next set up smoothness costs individually
		for ( int l1 = 0; l1 < num_labels; l1++ )
			for (int l2 = 0; l2 < num_labels; l2++ ){
				int cost = (l1-l2)*(l1-l2) <= 4  ? (l1-l2)*(l1-l2):4;
				gc->setSmoothCost(l1,l2,cost); 
			}

		printf("\nBefore optimization energy is %d",gc->compute_energy());
		gc->expansion(2);// run expansion for 2 iterations. For swap use gc->swap(num_iterations);
		printf("\nAfter optimization energy is %d",gc->compute_energy());

		for ( int  i = 0; i < num_pixels; i++ )
			result[i] = gc->whatLabel(i);

		delete gc;
	}
	catch (GCException e){
		e.Report();
	}

	delete [] result;
}

////////////////////////////////////////////////////////////////////////////////
// in this version, set data and smoothness terms using arrays
// grid neighborhood structure is assumed
//
void GridGraph_DArraySArray(int width,int height,int num_pixels,int num_labels)
{

	int *result = new int[num_pixels];   // stores result of optimization

	// first set up the array for data costs
	int *data = new int[num_pixels*num_labels];
	for ( int i = 0; i < num_pixels; i++ )
		for (int l = 0; l < num_labels; l++ )
			if (i < 25 ){
				if(  l == 0 ) data[i*num_labels+l] = 0;
				else data[i*num_labels+l] = 10;
			}
			else {
				if(  l == 5 ) data[i*num_labels+l] = 0;
				else data[i*num_labels+l] = 10;
			}
	// next set up the array for smooth costs
	int *smooth = new int[num_labels*num_labels];
	for ( int l1 = 0; l1 < num_labels; l1++ )
		for (int l2 = 0; l2 < num_labels; l2++ )
			smooth[l1+l2*num_labels] = (l1-l2)*(l1-l2) <= 4  ? (l1-l2)*(l1-l2):4;


	try{
		GCoptimizationGridGraph *gc = new GCoptimizationGridGraph(width,height,num_labels);
		gc->setDataCost(data);
		gc->setSmoothCost(smooth);
		printf("\nBefore optimization energy is %d",gc->compute_energy());
		gc->expansion(2);// run expansion for 2 iterations. For swap use gc->swap(num_iterations);
		printf("\nAfter optimization energy is %d",gc->compute_energy());

		for ( int  i = 0; i < num_pixels; i++ )
			result[i] = gc->whatLabel(i);

		delete gc;
	}
	catch (GCException e){
		e.Report();
	}

	delete [] result;
	delete [] smooth;
	delete [] data;

}
////////////////////////////////////////////////////////////////////////////////
// in this version, set data and smoothness terms using arrays
// grid neighborhood structure is assumed
//
void GridGraph_DfnSfn(int width,int height,int num_pixels,int num_labels)
{

	int *result = new int[num_pixels];   // stores result of optimization

	// first set up the array for data costs
	int *data = new int[num_pixels*num_labels];
	for ( int i = 0; i < num_pixels; i++ )
		for (int l = 0; l < num_labels; l++ )
			if (i < 25 ){
				if(  l == 0 ) data[i*num_labels+l] = 0;
				else data[i*num_labels+l] = 10;
			}
			else {
				if(  l == 5 ) data[i*num_labels+l] = 0;
				else data[i*num_labels+l] = 10;
			}


	try{
		GCoptimizationGridGraph *gc = new GCoptimizationGridGraph(width,height,num_labels);

		// set up the needed data to pass to function for the data costs
		ForDataFn toFn;
		toFn.data = data;
		toFn.numLab = num_labels;

		gc->setDataCost(&dataFn,&toFn);

		// smoothness comes from function pointer
		gc->setSmoothCost(&smoothFn);

		printf("\nBefore optimization energy is %d",gc->compute_energy());
		gc->expansion(2);// run expansion for 2 iterations. For swap use gc->swap(num_iterations);
		printf("\nAfter optimization energy is %d",gc->compute_energy());

		for ( int  i = 0; i < num_pixels; i++ )
			result[i] = gc->whatLabel(i);

		delete gc;
	}
	catch (GCException e){
		e.Report();
	}

	delete [] result;
	delete [] data;

}
////////////////////////////////////////////////////////////////////////////////
// Uses spatially varying smoothness terms. That is 
// V(p1,p2,l1,l2) = w_{p1,p2}*[min((l1-l2)*(l1-l2),4)], with 
// w_{p1,p2} = p1+p2 if |p1-p2| == 1 and w_{p1,p2} = p1*p2 if |p1-p2| is not 1
void GridGraph_DArraySArraySpatVarying(int width,int height,int num_pixels,int num_labels)
{
	int *result = new int[num_pixels];   // stores result of optimization

	// first set up the array for data costs
	int *data = new int[num_pixels*num_labels];
	for ( int i = 0; i < num_pixels; i++ )
		for (int l = 0; l < num_labels; l++ )
			if (i < 25 ){
				if(  l == 0 ) data[i*num_labels+l] = 0;
				else data[i*num_labels+l] = 10;
			}
			else {
				if(  l == 5 ) data[i*num_labels+l] = 0;
				else data[i*num_labels+l] = 10;
			}
	// next set up the array for smooth costs
	int *smooth = new int[num_labels*num_labels];
	for ( int l1 = 0; l1 < num_labels; l1++ )
		for (int l2 = 0; l2 < num_labels; l2++ )
			smooth[l1+l2*num_labels] = (l1-l2)*(l1-l2) <= 4  ? (l1-l2)*(l1-l2):4;

	// next set up spatially varying arrays V and H

	int *V = new int[num_pixels];
	int *H = new int[num_pixels];

	
	for ( int i = 0; i < num_pixels; i++ ){
		H[i] = i+(i+1)%3;
		V[i] = i*(i+width)%7;
	}


	try{
		GCoptimizationGridGraph *gc = new GCoptimizationGridGraph(width,height,num_labels);
		gc->setDataCost(data);
		gc->setSmoothCostVH(smooth,V,H);
		printf("\nBefore optimization energy is %d",gc->compute_energy());
		gc->expansion(2);// run expansion for 2 iterations. For swap use gc->swap(num_iterations);
		printf("\nAfter optimization energy is %d",gc->compute_energy());

		for ( int  i = 0; i < num_pixels; i++ )
			result[i] = gc->whatLabel(i);

		delete gc;
	}
	catch (GCException e){
		e.Report();
	}

	delete [] result;
	delete [] smooth;
	delete [] data;


}

////////////////////////////////////////////////////////////////////////////////
// in this version, set data and smoothness terms using arrays
// grid neighborhood is set up "manually"
//
void GeneralGraph_DArraySArray(int width,int height,int num_pixels,int num_labels)
{

	int *result = new int[num_pixels];   // stores result of optimization

	// first set up the array for data costs
	int *data = new int[num_pixels*num_labels];
	for ( int i = 0; i < num_pixels; i++ )
		for (int l = 0; l < num_labels; l++ )
			if (i < 25 ){
				if(  l == 0 ) data[i*num_labels+l] = 0;
				else data[i*num_labels+l] = 10;
			}
			else {
				if(  l == 5 ) data[i*num_labels+l] = 0;
				else data[i*num_labels+l] = 10;
			}
	// next set up the array for smooth costs
	int *smooth = new int[num_labels*num_labels];
	for ( int l1 = 0; l1 < num_labels; l1++ )
		for (int l2 = 0; l2 < num_labels; l2++ )
			smooth[l1+l2*num_labels] = (l1-l2)*(l1-l2) <= 4  ? (l1-l2)*(l1-l2):4;


	try{
		GCoptimizationGeneralGraph *gc = new GCoptimizationGeneralGraph(num_pixels,num_labels);
		gc->setDataCost(data);
		gc->setSmoothCost(smooth);

		// now set up a grid neighborhood system
		// first set up horizontal neighbors
		for (int y = 0; y < height; y++ )
			for (int  x = 1; x < width; x++ )
				gc->setNeighbors(x+y*width,x-1+y*width);

		// next set up vertical neighbors
		for (int y = 1; y < height; y++ )
			for (int  x = 0; x < width; x++ )
				gc->setNeighbors(x+y*width,x+(y-1)*width);

		printf("\nBefore optimization energy is %d",gc->compute_energy());
		gc->expansion(2);// run expansion for 2 iterations. For swap use gc->swap(num_iterations);
		printf("\nAfter optimization energy is %d",gc->compute_energy());

		for ( int  i = 0; i < num_pixels; i++ )
			result[i] = gc->whatLabel(i);

		delete gc;
	}
	catch (GCException e){
		e.Report();
	}

	delete [] result;
	delete [] smooth;
	delete [] data;

}
////////////////////////////////////////////////////////////////////////////////
// in this version, set data and smoothness terms using arrays
// grid neighborhood is set up "manually". Uses spatially varying terms. Namely
// V(p1,p2,l1,l2) = w_{p1,p2}*[min((l1-l2)*(l1-l2),4)], with 
// w_{p1,p2} = p1+p2 if |p1-p2| == 1 and w_{p1,p2} = p1*p2 if |p1-p2| is not 1

void GeneralGraph_DArraySArraySpatVarying(int width,int height,int num_pixels,int num_labels)
{
	int *result = new int[num_pixels];   // stores result of optimization

	// first set up the array for data costs
	int *data = new int[num_pixels*num_labels];
	for ( int i = 0; i < num_pixels; i++ )
		for (int l = 0; l < num_labels; l++ )
			if (i < 25 ){
				if(  l == 0 ) data[i*num_labels+l] = 0;
				else data[i*num_labels+l] = 10;
			}
			else {
				if(  l == 5 ) data[i*num_labels+l] = 0;
				else data[i*num_labels+l] = 10;
			}
	// next set up the array for smooth costs
	int *smooth = new int[num_labels*num_labels];
	for ( int l1 = 0; l1 < num_labels; l1++ )
		for (int l2 = 0; l2 < num_labels; l2++ )
			smooth[l1+l2*num_labels] = (l1-l2)*(l1-l2) <= 4  ? (l1-l2)*(l1-l2):4;


	try{
		GCoptimizationGeneralGraph *gc = new GCoptimizationGeneralGraph(num_pixels,num_labels);
		gc->setDataCost(data);
		gc->setSmoothCost(smooth);

		// now set up a grid neighborhood system
		// first set up horizontal neighbors
		for (int y = 0; y < height; y++ )
			for (int  x = 1; x < width; x++ ){
				int p1 = x-1+y*width;
				int p2 =x+y*width;
				gc->setNeighbors(p1,p2,p1+p2);
			}

		// next set up vertical neighbors
		for (int y = 1; y < height; y++ )
			for (int  x = 0; x < width; x++ ){
				int p1 = x+(y-1)*width;
				int p2 =x+y*width;
				gc->setNeighbors(p1,p2,p1*p2);
			}

		printf("\nBefore optimization energy is %d",gc->compute_energy());
		gc->expansion(2);// run expansion for 2 iterations. For swap use gc->swap(num_iterations);
		printf("\nAfter optimization energy is %d",gc->compute_energy());

		for ( int  i = 0; i < num_pixels; i++ )
			result[i] = gc->whatLabel(i);

		delete gc;
	}
	catch (GCException e){
		e.Report();
	}

	delete [] result;
	delete [] smooth;
	delete [] data;


}
*/
////////////////////////////////////////////////////////////////////////////////

using namespace std;
using namespace cv;

int main(int argc, char **argv)
{
	Mat img = imread(argv[1]);
	// imshow("Original Image",img);
	// waitKey(0);

	int width = img.cols;
	int height = img.rows;
	int num_labels = 5;
	int num_pixels = width*height;

	Mat samples(num_pixels, 3, CV_32F);
	for (int i=0;i<img.rows;i++){
		for (int j=0;j<img.cols;j++){
			for (int z=0;z<3;z++){
				samples.at<float>(j + i*img.cols, z) = img.at<Vec3b>(i,j)[z];
			}
		}
	}
	
	Mat labels;
	int attempts = 5;
	Mat centers;
	TermCriteria criteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS, 10000, 0.0001);
	kmeans(samples, num_labels, labels, criteria, attempts, KMEANS_PP_CENTERS, centers);

	Mat kmeans_image(img.size(), img.type());
	for(int i=0;i<img.rows;i++){
		for(int j=0;j<img.cols;j++){
			int cluster_idx = labels.at<int>(j + i*img.cols,0);
			kmeans_image.at<Vec3b>(i,j)[0] = centers.at<float>(cluster_idx, 0);
			kmeans_image.at<Vec3b>(i,j)[1] = centers.at<float>(cluster_idx, 1);
			kmeans_image.at<Vec3b>(i,j)[2] = centers.at<float>(cluster_idx, 2);
		}
	}

	// imshow("k-means image", kmeans_image);
	// waitKey(0);


	GCoptimizationGridGraph *gc = new GCoptimizationGridGraph(width,height,num_labels);
	
	// first set up data costs individually
	for ( int i = 0; i < num_pixels; i++ ){
		for (int l = 0; l < num_labels; l++ ){
			Scalar v1(centers.at<float>(l,0),centers.at<float>(l,1),centers.at<float>(l,2));
			Scalar v2(samples.at<float>(i,0),samples.at<float>(i,1),samples.at<float>(i,2));
			double cost = norm(v1,v2, NORM_L2);
			gc->setDataCost(i,l,cost);
		}
	}

	// next set up smoothness costs individually
	int smoothness = 5;
	for ( int l1 = 0; l1 < num_labels; l1++ ){
		for (int l2 = 0; l2 < num_labels; l2++ ){
			int cost = (l1==l2) ? 0 : smoothness;
			gc->setSmoothCost(l1,l2,cost); 
		}
	}

	cout << "Before optimization energy is " << gc->compute_energy() << endl;
	gc->expansion(1);
	while(true){
		cout << "After optimization energy is " << gc->compute_energy() << endl;

		Mat gc_image(img.size(), img.type());
		for(int i=0;i<img.rows;i++){
			for(int j=0;j<img.cols;j++){
				int cluster_idx = gc->whatLabel(j + i*img.cols);
				gc_image.at<Vec3b>(i,j)[0] = centers.at<float>(cluster_idx, 0);
				gc_image.at<Vec3b>(i,j)[1] = centers.at<float>(cluster_idx, 1);
				gc_image.at<Vec3b>(i,j)[2] = centers.at<float>(cluster_idx, 2);
			}
		}
		imshow("GC image", gc_image);
		int c = waitKey(0);
		if (c=='1'){
			cout << "Applying alpha-expansion... ";
			gc->expansion(1);
		} else if (c=='2'){			
			cout << "Applying alpha-beta swap... ";
			gc->swap(1);
		} else if (c=='i'){			
			cout << "Increasing smoothness... \n";
			smoothness += 5;
			for ( int l1 = 0; l1 < num_labels; l1++ ){
				for (int l2 = 0; l2 < num_labels; l2++ ){
					int cost = (l1==l2) ? 0 : smoothness;
					gc->setSmoothCost(l1,l2,cost); 
				}
			}
			cout << "Applying alpha-expansion... ";
			gc->expansion(1);

		} else break;
	}
}


	// int width = 10;
	// int height = 5;
	// int num_pixels = width*height;
	// int num_labels = 7;


	// // smoothness and data costs are set up one by one, individually
	// GridGraph_Individually(width,height,num_pixels,num_labels);

	// // smoothness and data costs are set up using arrays
	// GridGraph_DArraySArray(width,height,num_pixels,num_labels);

	// // smoothness and data costs are set up using functions
	// GridGraph_DfnSfn(width,height,num_pixels,num_labels);
	
	// // smoothness and data costs are set up using arrays. 
	// // spatially varying terms are present
	// GridGraph_DArraySArraySpatVarying(width,height,num_pixels,num_labels);

	// //Will pretend our graph is 
	// //general, and set up a neighborhood system
	// // which actually is a grid
	// GeneralGraph_DArraySArray(width,height,num_pixels,num_labels);

	// //Will pretend our graph is general, and set up a neighborhood system
	// // which actually is a grid. Also uses spatially varying terms
	// GeneralGraph_DArraySArraySpatVarying(width,height,num_pixels,num_labels);

	// printf("\n  Finished %d (%d) clock per sec %d \n\n",clock()/CLOCKS_PER_SEC,clock(),CLOCKS_PER_SEC);

	// return 0;
// }

/////////////////////////////////////////////////////////////////////////////////

