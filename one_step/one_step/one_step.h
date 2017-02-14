#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv; 

Mat one_step(Point3d point_input[20]) {
	Point3d l1 = point_input[0].cross(point_input[1]);
	Point3d m1 = point_input[2].cross(point_input[3]);
	Point3d l2 = point_input[4].cross(point_input[5]);
	Point3d m2 = point_input[6].cross(point_input[7]);





}