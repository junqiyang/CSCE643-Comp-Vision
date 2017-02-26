#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;


void ransac_h(int num, int N, CvPoint2D64f *point_1, CvPoint2D64f *point_2, CvMat *H, CvMat *inlier_mask)