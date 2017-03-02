#pragma once
#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include <fstream>
using namespace cv;
using namespace std;



int main(int argc, char** argv) {
	char* filename_input;
	char* filename_input_2;
	Mat image_input_1;
	Mat image_input_2;
	Mat image_output;

	Mat Offset = Mat(3, 3, CV_64FC1);
	Offset.at<double>(0, 0) = 1;
	Offset.at<double>(0, 1) = 0;
	Offset.at<double>(0, 2) = 0;
	Offset.at<double>(1, 0) = 0;
	Offset.at<double>(1, 1) = 1;
	Offset.at<double>(1, 2) = 270;
	Offset.at<double>(2, 0) = 0;
	Offset.at<double>(2, 1) = 0;
	Offset.at<double>(2, 2) = 1;

	if (argc >= 2) {
		filename_input = argv[2];
		filename_input_2 = argv[1];
		image_input_1 = imread(filename_input_2, 1);
		image_input_2 = imread(filename_input, 1);
		Mat H_r = Mat(3, 3, CV_64FC1);
		H_r.at<double>(0, 0) = 1.0089;
		H_r.at<double>(0, 1) = 0.1542;
		H_r.at<double>(0, 2) = -0.0066;
		H_r.at<double>(1, 0) = -0.0590;
		H_r.at<double>(1, 1) = 0.9918;
		H_r.at<double>(1, 2) = 0.0001;
		H_r.at<double>(2, 0) = -0.0615;
		H_r.at<double>(2, 1) = -0.0059;
		H_r.at<double>(2, 2) = 0.9996;

		Mat T1 = Mat(3, 3, CV_64FC1);
		Mat T2 = Mat(3, 3, CV_64FC1);
		T1.at<double>(0, 0) = 0.01767692951809751;
		T1.at<double>(0, 1) = 0;
		T1.at<double>(0, 2) = -0.8856141688566853;
		T1.at<double>(1, 0) = 0;
		T1.at<double>(1, 1) = 0.01767692951809751;
		T1.at<double>(1, 2) = -3.949909900818888;
		T1.at<double>(2, 0) = 0;
		T1.at<double>(2, 1) = 0;
		T1.at<double>(2, 2) = 1;

		T2.at<double>(0, 0) = 0.01788164269277166;
		T2.at<double>(0, 1) = 0;
		T2.at<double>(0, 2) = -8.127206603864721;
		T2.at<double>(1, 0) = 0;
		T2.at<double>(1, 1) = 0.01788164269277166;
		T2.at<double>(1, 2) = -3.970618759929948;
		T2.at<double>(2, 0) = 0;
		T2.at<double>(2, 1) = 0;
		T2.at<double>(2, 2) = 1;

		H_r = T2.inv() * H_r * T1;

		cout << H_r << endl;
		Mat result;
		warpPerspective(image_input_1, result, Offset*H_r, cv::Size(image_input_1.cols + image_input_2.cols+ image_input_2.cols, image_input_1.rows + image_input_1.rows));
		
		cv::Mat half(result, cv::Rect(0, 270, image_input_2.cols, image_input_2.rows));

		image_input_2.copyTo(half);
		imshow("Result", result);
		imwrite("C:\\Users\\roast_000\\Desktop\\hw2_result\\MLE.jpg", result);
		ofstream myfile;
		myfile.open("C:\\Users\\roast_000\\Desktop\\hw2_result\\H_MLE.txt");
		myfile << H_r << endl;
		myfile.close();
		waitKey(0);
	}
}