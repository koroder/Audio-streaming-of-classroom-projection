#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>

using namespace cv;
using namespace std;

/** @function main */
int main(int argc, char** argv)
{
  Mat src, src_gray;

  /// Read the image
  src = imread( argv[1], 1 );

  if( !src.data )
    { return -1; }

  /// Convert it to gray
  cvtColor( src, src_gray, CV_BGR2GRAY );
  cout << src_gray.rows << " " << src_gray.cols << endl;

  /// Show your results
  namedWindow( "Hough Circle Transform Demo", CV_WINDOW_AUTOSIZE );
  imshow( "Hough Circle Transform Demo", src_gray );
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

  imshow( "Hough Circle Transform Demo", title );
  waitKey(0);

  /* Text slide content */
  // Mat content;
  // rect.x = 0;
  // rect.y = htPar*src_gray.rows+1;
  // rect.width = src_gray.cols;
  // rect.height = src_gray.rows-rect.y;
  // content = src_gray(rect).clone();

  // imshow( "Hough Circle Transform Demo", content );
  // waitKey(0);
  /* End Text slide content */

  /* Pie chart slide content */
  Mat content;
  rect.x = 0.58*src_gray.cols;
  rect.y = 0.4*src_gray.rows+1;
  rect.width = src_gray.cols-rect.x;
  rect.height = 0.7*src_gray.rows-rect.y;
  content = src_gray(rect).clone();

  imshow( "Hough Circle Transform Demo", content );
  waitKey(0);
  /* End pie chart slide content */

  return 0;
 }

