#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <string>

using namespace cv;
using namespace std;

int findType(string arg) {

	Mat src, src_gray;

	src = imread( arg, 1 );

  	if( !src.data )
		return -1;

  	/// Convert it to gray
  	cvtColor( src, src_gray, CV_BGR2GRAY );

	  /// Reduce the noise so we avoid false circle detection
  	GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );

  	vector<Vec3f> circles;

  	/// Apply the Hough Transform to find the circles
  	HoughCircles( src_gray, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows/8, 200, 100, 0, 0 );

  	return circles.size();
}

void processTextSlide(string arg) {
	cout << "Processing text slide" << endl;

	Mat src, src_gray;

  	/// Read the image
  	src = imread( arg, 1 );

  	if( !src.data )
  		{ return; }

  	/// Convert it to gray
	cvtColor( src, src_gray, CV_BGR2GRAY );

  	/// Reduce the noise so we avoid false circle detection
  	GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );
  	imshow("gaus image",src_gray);
  	waitKey(0);

  	double htPar = 0.22;
  	double wdPar = 1;

  	Mat title;
  	Rect rect;
  	rect.x = 0;
  	rect.y = 0;
  	rect.width = src_gray.cols;
  	rect.height = htPar*src_gray.rows;
  	title = src_gray(rect).clone();

  	imshow( "Slide Title", title );
  	waitKey(0);

  	Mat content;
  	rect.x = 0;
  	rect.y = htPar*src_gray.rows+1;
  	rect.width = src_gray.cols;
  	rect.height = src_gray.rows-rect.y;
  	content = src_gray(rect).clone();

  	imshow( "Slide Content", content );
  	waitKey(0);

  	// Scalar intensity = src_gray.at<uchar>(1, 1);
  	// cout << src_gray.rows << endl;
  	// cout << src_gray.cols << endl;
  	// cout << intensity.val[0] << endl;

	return;
}

void processPieChart(string arg) {
	cout << "processPieChart" << endl;

	Mat src, src_gray;

  	/// Read the image
  	src = imread( arg, 1 );

  	if( !src.data )
  		{ return; }

  	/// Convert it to gray
	cvtColor( src, src_gray, CV_BGR2GRAY );

  	/// Reduce the noise so we avoid false circle detection
  	GaussianBlur( src_gray, src_gray, Size(9, 9), 2, 2 );
  	imshow("gaus image",src_gray);
  	waitKey(0);

  	double htPar = 0.22;
  	double htParPiTop = 0.4;
  	double htParPiBottom = 0.7;
  	double wdPar = 0.58;

  	Mat title;
  	Rect rect;
  	rect.x = 0;
  	rect.y = 0;
  	rect.width = src_gray.cols;
  	rect.height = htPar*src_gray.rows;
  	title = src_gray(rect).clone();

  	imshow( "Slide Title", title );
  	waitKey(0);

  	/* Pie chart slide content */
  	Mat content;
  	rect.x = wdPar*src_gray.cols;
  	rect.y = htParPiTop*src_gray.rows;
  	rect.width = src_gray.cols-rect.x;
  	rect.height = htParPiBottom*src_gray.rows-rect.y;
  	content = src_gray(rect).clone();

  	imshow( "Slide Content", content );
  	waitKey(0);

  	// Scalar intensity = src_gray.at<uchar>(1, 1);
  	// cout << src_gray.rows << endl;
  	// cout << src_gray.cols << endl;
  	// cout << intensity.val[0] << endl;

	return;
}

void runner(string arg) {
	int type = findType(arg);
	if(type == 0) {
		cout << "Bulleted Text Slide" << endl;
		processTextSlide(arg);
	}
	else if(type > 0) {
		cout << "Pie Chart slide" << endl;
		processPieChart(arg);
	}
	else {
		cout << "unidentified slide" << endl;
	}

	return;
}

int main(int argc, char** argv)
{
	string arg = argv[1];
	runner(arg);
	return 0;
}