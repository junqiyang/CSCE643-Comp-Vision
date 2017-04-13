#pragma once
#pragma once

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/calib3d.hpp"
#include "solver.h"
#include <iostream>
#include <vector>

void p3p(
	double fx, double fy, double cx, double cy,
	double R[4][3][3], double t[4][3],
	cv::Point2d u, cv::Point2d v, cv::Point2d w,
	cv::Point3d A, cv::Point3d B, cv::Point3d C);