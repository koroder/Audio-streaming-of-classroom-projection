#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <tesseract/baseapi.h>
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>

using namespace cv;
using namespace std;
using namespace tesseract;

string ocr_tesseract(Mat im) {
	// Pass it to Tesseract API
    TessBaseAPI tess;
    tess.Init(NULL, "eng", OEM_DEFAULT);
    tess.SetPageSegMode(PSM_SINGLE_BLOCK);
    tess.SetImage((uchar*)im.data, im.cols, im.rows, 1, im.cols);

    // Get the text
    char* out = tess.GetUTF8Text();
    string ret = (string)out;
    
    return ret;
}

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

string refine_string(string arg) {
	for (int i = 0; i < arg.size(); ++i)
	{
		/* code */
		bool cond = ((arg[i] >= '0' && arg[i] <= '9') || (arg[i] >= 'A' && arg[i] <= 'Z') || 
		   			(arg[i] >= 'a' && arg[i] <= 'z') || arg[i] == '.' || arg[i] == '%' ||
		   			 arg[i] == '\n'); // 39 is asci value of '
		if(!cond) {
			arg[i] = ' ';
		}
	}
	return arg;
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

  	string content = ocr_tesseract(src_gray);
  	content = refine_string(content);

  	string filename = arg + ".txt";
  	ofstream myfile;
  	myfile.open (filename.c_str());
  	myfile << "This is a bullet text slide about\n";
  	myfile << content;
  	myfile.close();

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

  	string content = ocr_tesseract(src_gray);
  	content = refine_string(content);

  	string filename = arg + ".txt";
  	ofstream myfile;
  	myfile.open (filename.c_str());
  	myfile << "This is a pie chart slide about\n";
  	myfile << content;
  	myfile.close();
  	
	return;
}

void runner(string arg) {
	int type = findType(arg);
	if(type == 0) {
		cout << "Bulleted Text Slide" << endl;
		processTextSlide(arg);
		// procesing done! now send file using bluetooth
	}
	else if(type > 0) {
		cout << "Pie Chart slide" << endl;
		processPieChart(arg);
		// procesing done! now send file using bluetooth
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