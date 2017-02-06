#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;

void visual_matrix(CvMat* A, int row, int col);
void input_coordinate(Point2f opp[4], Point2f npp[4]);
void find_matrix(CvMat *H, Point2f opp[4], Point2f npp[4]);
void fill_matrix(CvMat *T, CvMat *old, Point2f opp[4], Point2f npp[4]);

int main(int argc, char** argv) {
	char* filename_input;
	char* filename_output;

	IplImage* image_input;
	IplImage* image_output;

	Point2f old_pixel_point[4];
	Point2f new_pixel_point[4];

	CvMat *H_matrix = cvCreateMat(3, 3, CV_64FC1);
	/*
	if (argc >= 2) {
		filename_input = argv[1];
	}
	else {
		return 0;
	}

	if ((image_input = cvLoadImage(filename_input, 1)) == 0) {
		printf("fail to load the image");
		return 2;	
	}
	*/
	input_coordinate(old_pixel_point, new_pixel_point);
	find_matrix(H_matrix, old_pixel_point, new_pixel_point);
	visual_matrix(H_matrix, 3, 3);

	return 0;
}


void project_image(IplImage *input, CvMat *H, IplImage *output){
	CvMat *Bound_input = cvCreateMat(3, 4, CV_64FC1);
	CvMat *Bound_output = cvCreateMat(3, 4, CV_64FC1);
	//this is homogenious coordinate
	cvmSet(Bound_input, 0, 0, 0);
	cvmSet(Bound_input, 1, 0, 0);
	cvmSet(Bound_input, 2, 0, 1);
	cvmSet(Bound_input, 0, 1, input->width -1);
	cvmSet(Bound_input, 1, 1, 0);
	cvmSet(Bound_input, 2, 1, 1);
	cvmSet(Bound_input, 0, 2, input->width - 1);
	cvmSet(Bound_input, 1, 2, input->height - 1);
	cvmSet(Bound_input, 2, 2, 1);
	cvmSet(Bound_input, 0, 3, 0);
	cvmSet(Bound_input, 1, 3, input->height - 1);
	cvmSet(Bound_input, 2, 3, 1);

	cvMatMul(H, Bound_input, Bound_output);

	double w_max = DBL_MIN;
	double w_min = DBL_MAX;
	double h_max = DBL_MIN;
	double h_min = DBL_MAX;
	for (int i = 0; i < 4; i++) {
		double x_3 = cvmGet(Bound_output, 2, i);
		double Eli_x = cvmGet(Bound_output, 0, i) / x_3;
		double Eli_y = cvmGet(Bound_output, 1, i) / x_3;
		
		if (Eli_x < w_min) {
			w_min = Eli_x;
		}
		if (Eli_y < h_min) {
			h_min = Eli_y;
		}
		if (Eli_x > w_max) {
			w_max = Eli_x;
		}
		if (Eli_y > h_max) {
			h_max = Eli_y;
		}	
	}

	double ratio = (w_max - w_min) / (h_max - h_min);
	IplImage *result = cvCreateImage(cvSize((input->height) * ratio, input->height), IPL_DEPTH_8U, 3);
	cvZero(result);





}








void find_matrix(CvMat *H, Point2f opp[4], Point2f npp[4]) {
	CvMat *T;
	CvMat *old_mat;
	CvMat *new_mat;
	T       = cvCreateMat(8, 8, CV_64FC1);
	old_mat = cvCreateMat(8, 1, CV_64FC1);
	new_mat = cvCreateMat(8, 1, CV_64FC1);

	fill_matrix(T, old_mat, opp, npp);
	visual_matrix(T, 8, 8);
	visual_matrix(old_mat, 8, 1);



	cvSolve(T, old_mat, new_mat, CV_LU);
	
	CvMat *Hinv = cvCreateMat(3, 3, CV_64FC1);
	for (int i = 0; i < 8; i++) {
		cvmSet(Hinv, i / 3, i % 3, cvmGet(new_mat, i, 0));	
	}
	cvmSet(Hinv, 2, 2, 1.0);
	cvInvert(Hinv, H, CV_LU);
}


void fill_matrix(CvMat *T, CvMat *old, Point2f opp[4], Point2f npp[4]) {
	for (int i = 0; i < 4; i++) {
		cvmSet(T, i * 2, 0, npp[i].x);
		cvmSet(T, i * 2, 1, npp[i].y);
		cvmSet(T, i * 2, 2, 1.0);
		cvmSet(T, i * 2, 3, 0.0);
		cvmSet(T, i * 2, 4, 0.0);
		cvmSet(T, i * 2, 5, 0.0);
		cvmSet(T, i * 2, 6, - npp[i].x * opp[i].x );
		cvmSet(T, i * 2, 7, - npp[i].y * opp[i].x );

		cvmSet(T, i * 2 + 1, 0, 0);
		cvmSet(T, i * 2 + 1, 1, 0);
		cvmSet(T, i * 2 + 1, 2, 0);
		cvmSet(T, i * 2 + 1, 3, npp[i].x);
		cvmSet(T, i * 2 + 1, 4, npp[i].y);
		cvmSet(T, i * 2 + 1, 5, 1);
		cvmSet(T, i * 2 + 1, 6, - npp[i].x * opp[i].y);
		cvmSet(T, i * 2 + 1, 7, - npp[i].y * opp[i].y);

		cvmSet(old, i * 2 , 0, opp[i].x);
		cvmSet(old, i * 2 + 1 , 0, opp[i].y);
	
	}
}

void input_coordinate(Point2f opp[4], Point2f npp[4]) {
	for (int i = 0; i < 4; i++) {
		printf("input %d pair: \n", i);
		scanf("%f, %f", &(opp[i].x), &(opp[i].y));
		printf("targeted %d pair: \n", i);
		scanf("%f, %f", &(npp[i].x), &(npp[i].y));
		printf("\n");
	}
}


void visual_matrix(CvMat* A, int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%lf  ", cvmGet(A, i, j));
		}
		printf("\n");
	}
}