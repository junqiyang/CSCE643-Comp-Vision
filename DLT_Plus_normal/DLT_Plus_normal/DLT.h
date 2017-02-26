#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;

void DLT(int n, CvPoint2D64f *p1, CvPoint2D64f *p2, CvMat *H);

Mat Normalization_DLT(int n, CvPoint2D64f * p);