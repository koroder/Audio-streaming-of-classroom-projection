#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <tesseract/baseapi.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>

using namespace cv;
using namespace std;

#define NORM_TH 200000

bool slideChange(string arg1, string arg2) {
	Mat im1,im1_gray,im1_bw;
	Mat im2,im2_gray,im2_bw;

  	/// Read the image
  	im1 = imread( arg1, 1 );
  	if( !im1.data )
  		{ return false; }

  	im2 = imread( arg2, 1 );
  	if( !im2.data )
  		{ return false; }

  	/// Convert it to gray
	cvtColor( im1, im1_gray, CV_BGR2GRAY );
	cvtColor( im2, im2_gray, CV_BGR2GRAY );

	/// Convert to black and white
	im1_bw = im1_gray > 128;
	im2_bw = im2_gray > 128;

	double norm_val;

	norm_val = norm( im1_bw, im2_bw, NORM_L2);
	cout << "norm_val: " << norm_val << endl;
	if(norm_val > NORM_TH)
		return true;

	return false;
}

int main(int argc, char** argv)
{
	string im1 = argv[1];
	string im2 = argv[2];
	bool x = slideChange(im1,im2);
	cout << "slideChange: " << x << endl;
	return 0;
}