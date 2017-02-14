#pragma once

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include "visual.h"
using namespace cv;

Mat  Affline_H(Point3d point_input[4], Mat H);