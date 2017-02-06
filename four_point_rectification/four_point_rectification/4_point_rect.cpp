#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
using namespace cv;

void visual_matrix(CvMat* A, int row, int col);
void input_coordinate(Point2f opp[4], Point2f npp[4]);
//step took to find the H matrix;
void find_matrix_h(CvMat *H, Point2f opp[4], Point2f npp[4]);
void fill_matrix(CvMat *T, CvMat *old, Point2f opp[4], Point2f npp[4]);
//step took to project image;
void project_image(IplImage *input, CvMat *H);
int main(int argc, char** argv) {
	char* filename_input;
	char* filename_output;

	IplImage* image_input;
	IplImage* image_output;

	Point2f old_pixel_point[4];
	Point2f new_pixel_point[4];

	CvMat *H_matrix = cvCreateMat(3, 3, CV_64FC1);
	
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
	
	input_coordinate(old_pixel_point, new_pixel_point);
	find_matrix_h(H_matrix, old_pixel_point, new_pixel_point);
	visual_matrix(H_matrix, 3, 3);
	project_image(image_input, H_matrix);
	return 0;
}


void project_image(IplImage *input, CvMat *H){
	CvMat *Bound_input = cvCreateMat(3, 1, CV_64FC1);
	CvMat *Bound_output = cvCreateMat(3, 1, CV_64FC1);
	double Eli_x = cvmGet(Bound_output, 0, i) / x_3;
	double Eli_y = cvmGet(Bound_output, 1, i) / x_3;

	Point2f new_4_bound[4];

	
	//CvMat in_test = cvarrToMat(input, true);

	cvmSet(Bound_input, 0, 0, 0);
	cvmSet(Bound_input, 1, 0, 0);
	cvmSet(Bound_input, 2, 0, 1);
	cvMatMul(H, Bound_input, Bound_output);	new_4_bound[0].x = cvmGet(Bound_output, 0, 0) / cvmGet(Bound_output, 2, 0);
	new_4_bound[0].y = cvmGet(Bound_output, 1, 0) / cvmGet(Bound_output, 2, 0);


	cvmSet(Bound_input, 0, 1, input->width -1);
	cvmSet(Bound_input, 1, 1, 0);
	cvmSet(Bound_input, 2, 1, 1);
	cvMatMul(H, Bound_input, Bound_output);	new_4_bound[1].x = cvmGet(Bound_output, 0, 0) / cvmGet(Bound_output, 2, 0);
	new_4_bound[1].y = cvmGet(Bound_output, 1, 0) / cvmGet(Bound_output, 2, 0);

	cvmSet(Bound_input, 0, 2, input->width - 1);
	cvmSet(Bound_input, 1, 2, input->height - 1);
	cvmSet(Bound_input, 2, 2, 1);
	cvMatMul(H, Bound_input, Bound_output);	new_4_bound[2].x = cvmGet(Bound_output, 0, 0) / cvmGet(Bound_output, 2, 0);
	new_4_bound[2].y = cvmGet(Bound_output, 1, 0) / cvmGet(Bound_output, 2, 0);

	cvmSet(Bound_input, 0, 3, 0);
	cvmSet(Bound_input, 1, 3, input->height - 1);
	cvmSet(Bound_input, 2, 3, 1);
	cvMatMul(H, Bound_input, Bound_output);	new_4_bound[3].x = cvmGet(Bound_output, 0, 0) / cvmGet(Bound_output, 2, 0);
	new_4_bound[3].y = cvmGet(Bound_output, 1, 0) / cvmGet(Bound_output, 2, 0);

	for (int i = 0; i < 4; i++) {
	
	
	
	}
	/*double w_max = DBL_MIN;
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



	double w = (w_max - w_min);
    double h = (h_max - h_min);
	/*IplImage *result = cvCreateImage(cvSize((input->height) * ratio, input->height), IPL_DEPTH_8U, 3);
	cvZero(result);
	CvMat out_test = cvarrToMat(result, true);
	*/

	//original design,  image broken because the boundary doesn't match each others.
	/*
	CvMat* original_H_cood = cvCreateMat(3, 1, CV_64FC1);
	CvMat* transfor_H_cood = cvCreateMat(3, 1, CV_64FC1);
	cvmSet(original_H_cood, 2, 0, 1.0);
	Point2f transfor_eli;
	for (int i = 0; i < input->width; i++) {
		cvmSet(original_H_cood, 0, 0, i / 1);
		for (int j = 0; j < input->height; j++) {
			cvmSet(original_H_cood, 1, 0, j / 1);
			cvMatMul(H, original_H_cood, transfor_H_cood);
			visual_matrix(transfor_H_cood, 3, 1);
			transfor_eli.x = cvmGet(transfor_H_cood, 0, 0) / cvmGet(transfor_H_cood, 2, 0);
			transfor_eli.y = cvmGet(transfor_H_cood, 1, 0) / cvmGet(transfor_H_cood, 2, 0);
			printf("original: %f, %f \n", i, j);
			printf("transfor: %f, %f \n", (int)transfor_eli.x, (int)transfor_eli.y);
			Vec3d color = in_test.at<Vec3d>(Point(i, j));
			out_test.at<Vec3d>(Point(transfor_eli.x, transfor_eli.y)) = color;
		}
	}

	IplImage a = out_test;
	imshow("window",out_test);
	
	*/

	//this is homogenious coordinate
	/*cvmSet(Bound_input, 0, 0, 0);
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
	/*
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

	double distance = 1 / ratio;
	CvMat* original_H_cood = cvCreateMat(3, 1, CV_64FC1);
	CvMat* transfor_H_cood = cvCreateMat(3, 1, CV_64FC1);
	cvmSet(original_H_cood, 2, 0, 1.0);
	for (int i = 0l i < )
	*/


}








void find_matrix_h(CvMat *H, Point2f opp[4], Point2f npp[4]) {
	CvMat *T;
	CvMat *old_mat;
	CvMat *h_mat;
	T       = cvCreateMat(8, 8, CV_64FC1);
	old_mat = cvCreateMat(8, 1, CV_64FC1);
	h_mat = cvCreateMat(8, 1, CV_64FC1);

	fill_matrix(T, old_mat, opp, npp);
	visual_matrix(T, 8, 8);
	visual_matrix(old_mat, 8, 1);
	cvSolve(T, old_mat, h_mat, CV_LU);	
	for (int i = 0; i < 8; i++) {
		cvmSet(H, i / 3, i % 3, cvmGet(h_mat, i, 0));
	}
	cvmSet(H, 2, 2, 1.0);
}


void fill_matrix(CvMat *T, CvMat *old, Point2f opp[4], Point2f npp[4]) {
	for (int i = 0; i < 4; i++) {
		cvmSet(T, i * 2, 0, opp[i].x);
		cvmSet(T, i * 2, 1, opp[i].y);
		cvmSet(T, i * 2, 2, 1.0);
		cvmSet(T, i * 2, 3, 0.0);
		cvmSet(T, i * 2, 4, 0.0);
		cvmSet(T, i * 2, 5, 0.0);
		cvmSet(T, i * 2, 6, - opp[i].x * npp[i].x );
		cvmSet(T, i * 2, 7, - opp[i].y * npp[i].x );

		cvmSet(T, i * 2 + 1, 0, 0);
		cvmSet(T, i * 2 + 1, 1, 0);
		cvmSet(T, i * 2 + 1, 2, 0);
		cvmSet(T, i * 2 + 1, 3, opp[i].x);
		cvmSet(T, i * 2 + 1, 4, opp[i].y);
		cvmSet(T, i * 2 + 1, 5, 1);
		cvmSet(T, i * 2 + 1, 6, - opp[i].x * npp[i].y);
		cvmSet(T, i * 2 + 1, 7, - opp[i].y * npp[i].y);

		cvmSet(old, i * 2 , 0, npp[i].x);
		cvmSet(old, i * 2 + 1 , 0, npp[i].y);	
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