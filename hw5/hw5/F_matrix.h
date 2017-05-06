#pragma once


#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/calib3d.hpp"
#include <iostream>
#include <vector>
using namespace cv;

Mat Normalization_F(int n, CvPoint2D64f * p);

Mat Find_F(CvPoint2D64f * p1, CvPoint2D64f * p2, int n);

void Find_E(Mat  F, Mat & e, Mat & ep);

Mat find_p(Mat F,Mat ep);

Mat Find_A(Mat P1, Mat P2, CvPoint2D64f x1, CvPoint2D64f x2);
Mat three_reconstruct(Mat P1, Mat P2, CvPoint2D64f* x1, CvPoint2D64f* x2, int n);