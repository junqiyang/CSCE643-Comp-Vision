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
void project_image(Mat input, CvMat *H);
int main(int argc, char** argv) {
	char* filename_input;
	char* filename_output;

	Mat image_input;
	Mat image_output;

	Point2f old_pixel_point[4];
	Point2f new_pixel_point[4];

	CvMat *H_matrix = cvCreateMat(3, 3, CV_64FC1);
	
	if (argc >= 2) {
		filename_input = argv[1];
	}
	else {
		return 0;
	}

	image_input = imread(filename_input, 1);
//	imshow("testwindow", image_input);
	cv::waitKey(0);
	input_coordinate(old_pixel_point, new_pixel_point);
	find_matrix_h(H_matrix, old_pixel_point, new_pixel_point);
	visual_matrix(H_matrix, 3, 3);
	
	Mat H_mat = cvarrToMat(H_matrix);

//	perspectiveTransform(image_input, image_output, H_mat);
//	imshow("window1", image_output);
//	cv::waitKey(0);
//	imwrite("C:\\Users\\Roast\\Desktop\\perspective_trans.jpg", image_output);

	project_image(image_input, H_matrix);


  	return 0;
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




void project_image(Mat input, CvMat *H) {
	CvMat *Bound_input = cvCreateMat(3, 1, CV_64FC1);
	CvMat *Bound_output = cvCreateMat(3, 1, CV_64FC1);
	Point2f new_4_bound[4];
	CvMat *inv_H = cvCreateMat(3, 3, CV_64FC1);
	cvInvert(H, inv_H, CV_LU);
	cvmSet(Bound_input, 0, 0, 0);
	cvmSet(Bound_input, 1, 0, 0);
	cvmSet(Bound_input, 2, 0, 1);
	cvMatMul(H, Bound_input, Bound_output);
	new_4_bound[0].x = cvmGet(Bound_output, 0, 0) / cvmGet(Bound_output, 2, 0);
	new_4_bound[0].y = cvmGet(Bound_output, 1, 0) / cvmGet(Bound_output, 2, 0);


	cvmSet(Bound_input, 0, 0, input.size().width - 1);
	cvmSet(Bound_input, 1, 0, 0);
	cvmSet(Bound_input, 2, 0, 1);
	cvMatMul(H, Bound_input, Bound_output);
	new_4_bound[1].x = cvmGet(Bound_output, 0, 0) / cvmGet(Bound_output, 2, 0);
	new_4_bound[1].y = cvmGet(Bound_output, 1, 0) / cvmGet(Bound_output, 2, 0);

	cvmSet(Bound_input, 0, 0, input.size().width - 1);
	cvmSet(Bound_input, 1, 0, input.size().height - 1);
	cvmSet(Bound_input, 2, 0, 1);
	cvMatMul(H, Bound_input, Bound_output);
	new_4_bound[2].x = cvmGet(Bound_output, 0, 0) / cvmGet(Bound_output, 2, 0);
	new_4_bound[2].y = cvmGet(Bound_output, 1, 0) / cvmGet(Bound_output, 2, 0);

	cvmSet(Bound_input, 0, 0, 0);
	cvmSet(Bound_input, 1, 0, input.size().height - 1);
	cvmSet(Bound_input, 2, 0, 1);
	cvMatMul(H, Bound_input, Bound_output);
	new_4_bound[3].x = cvmGet(Bound_output, 0, 0) / cvmGet(Bound_output, 2, 0);
	new_4_bound[3].y = cvmGet(Bound_output, 1, 0) / cvmGet(Bound_output, 2, 0);

	for (int i = 0; i < 4; i++) {
		printf("(x, y): %f, %f \n", new_4_bound[i].x, new_4_bound[i].y);
	}
	double w_max = DBL_MIN;
	double w_min = DBL_MAX;
	double h_max = DBL_MIN;
	double h_min = DBL_MAX;
	for (int i = 0; i < 4; i++) {
		if (new_4_bound[i].x < w_min) {
			w_min = new_4_bound[i].x;
		}
		if (new_4_bound[i].y < h_min) {
			h_min = new_4_bound[i].y;
		}
		if (new_4_bound[i].x > w_max) {
			w_max = new_4_bound[i].x;
		}
		if (new_4_bound[i].y > h_max) {
			h_max = new_4_bound[i].y;
		}
	}
	
	double w = (w_max - w_min);
	double h = (h_max - h_min);
	double scale = input.cols / w;
	double w_out = input.cols;
	double h_out = (int)(h * scale);

	Mat H_mat = cvarrToMat(H);

	Mat out_test(h_out, w_out, CV_8UC3);
	Mat original_H_cood(3, 1, CV_64FC1);
	Mat transfor_H_cood(3, 1, CV_64FC1);
	original_H_cood.at<double>(2, 0) = 1.0;
	double step = 1;
	printf("scale: %f", step);
	double x, y;
	int count = 0;
	for (int i = 0; i < out_test.cols; i++) {
		original_H_cood.at<double>(0, 0) = i ;
		for (int j = 0; j < out_test.rows; j++) {
			original_H_cood.at<double>(1, 0) = j;
			transfor_H_cood = H_mat.inv() * original_H_cood;
			
			x = transfor_H_cood.at<double>(0,0) / transfor_H_cood.at<double>(2, 0);
			y = transfor_H_cood.at<double>(1,0) / transfor_H_cood.at<double>(2, 0);
			if (x < 0 || x > input.cols -1 || y < 0 || y > input.rows - 1) {
				count++;
				continue;
			}
			//http://blog.demofox.org/2015/08/15/resizing-images-with-bicubic-interpolation/
			double xfract = x - (int)x;
			double yfract = y - (int)y;
			Vec3b p00 = input.at<Vec3b>(int(y), int(x));
			if (xfract != 0.0 || yfract != 0.0) {
				Vec3b p10 = input.at<Vec3b>(int(y), int(x + 1));
				Vec3b p01 = input.at<Vec3b>(int(y + 1), int(x));
				Vec3b p11 = input.at<Vec3b>(int(y + 1), int(x + 1));
				out_test.at<Vec3b>(j, i) = p00 * (1 - xfract) * (1 - yfract) +
					p10 * xfract * (1 - yfract) +
					p01 * (1 - xfract) * yfract +
					p11 * xfract * yfract;	
			}
			else {
				out_test.at<Vec3b>(j, i) = p00;
			}
		}	
	}
	printf("size test: %f, %f", out_test.cols, out_test);
	printf("\n");
	printf("counter: %f", (double)count);
	imwrite("C:\\Users\\Roast\\Desktop\\current_implementation.jpg", out_test);



	













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
