#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include "image_wrap.h"
using namespace cv;


void input_coordinate(Point2f opp[4], Point2f npp[4]);
//step took to find the H matrix;
void four_point_H(CvMat *H, Point2f opp[4], Point2f npp[4]);
void fill_matrix(CvMat *T, CvMat *old, Point2f opp[4], Point2f npp[4]);
