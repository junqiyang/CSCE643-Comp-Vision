#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;

//step took to project image;
void project_image(Mat input, CvMat *H);

void visual_matrix(CvMat* A, int row, int col);


IplImage * back_project(IplImage *input_img, CvMat* Hmat);