#include "4_point_rect.h"
#include "Line_infinity.h"
using namespace cv;

Mat image_input;
Mat image_output;

Point2f line_point[4];
int counter = 1;
int x_min = 1000000000000;
int x_max = 0;
int y_min = 1000000000000;
int y_max = 0;


void on_mouse(int event, int x, int y, int, void*) {
	if (image_input.empty()) {
		return;
	}
	if (event == CV_EVENT_LBUTTONUP) {
		
		printf("Point (%f, %f) \n", (double)x, (double)y);
		circle(image_input, Point(x, y), 2, CV_RGB(255, 0, 0), -1);
		if (counter < 5) {
			line_point[counter-1] = Point2f(x, y);
			if (x_min > x) {
				x_min = x;
			}
			if (y_min > y) {
				y_min = y;
			}
			if (x_max < x) {
				x_max = x;
			}
			if (y_max < y) {
				y_max = y;
			}
		}
		counter++;
	}
	imshow("window", image_input);
}

int main(int argc, char** argv) {
	char* filename_input;
	char* filename_output;



	Point2f old_pixel_point[4];
	Point2f new_pixel_point[4];

	CvMat *H_matrix = cvCreateMat(3, 3, CV_64FC1);

	char prob_num = '1';

	if (argc >= 2) {
		filename_input = argv[1];
	}
	else {
		return 0;
	}

		image_input = imread(filename_input, 1);
		IplImage *input_picutre = cvLoadImage(filename_input, 1);
	//	cv::waitKey(0);
		input_coordinate(old_pixel_point, new_pixel_point);
		four_point_H(H_matrix, old_pixel_point, new_pixel_point);
		visual_matrix(H_matrix, 3, 3);
		
		

	/*	CvMat* offset = cvCreateMat(3, 3, CV_64FC1);
		cvmSet(offset, 0, 0, 0.3);
		cvmSet(offset, 0, 1, 0);
		cvmSet(offset, 0, 2, 0);
		cvmSet(offset, 1, 0, 0);
		cvmSet(offset, 1, 1, 0.3);
		cvmSet(offset, 1, 2, 0);
		cvmSet(offset, 2, 0, 0);
		cvmSet(offset, 2, 1, 0);
		cvmSet(offset, 2, 2, 1);
		cvMatMul(H_matrix, offset, H_matrix);
		*/

		Mat H_mat = cvarrToMat(H_matrix);
	
		std::cout << H_mat << std::endl;
		warpPerspective(image_input, image_output, H_mat, cv::Size(1500, 1500));
		//imshow("test1", image_output);
		//cv::waitKey(0);
		imwrite("C:\\Users\\roast_000\\Desktop\\4_point.jpg", image_output);	
	



	return 0;
}

/*
int main(int argc, char** argv) {
	char* filename_input;
	CvMat *H_matrix = cvCreateMat(3, 3, CV_64FC1);



	if (argc >= 2) {
		filename_input = argv[1];
		image_input = imread(filename_input, 1);
		namedWindow("window", CV_WINDOW_AUTOSIZE);
		imshow("window", image_input);
		cvSetMouseCallback("window", on_mouse);

		for (;;) {
			uchar key = (uchar)waitKey();
			if (counter > 4) {
				Point2f new_pixel_point[4];
				new_pixel_point[0] = Point2f(x_min, y_max);
				new_pixel_point[1] = Point2f(x_max, y_max);
				new_pixel_point[2] = Point2f(x_min, y_min);
				new_pixel_point[3] = Point2f(x_max, y_min);
				std:: cout<< 
				four_point_H(H_matrix, line_point, new_pixel_point);

/*

				CvMat* offset = cvCreateMat(3, 3, CV_64FC1);
				cvmSet(offset, 0, 0, 0.3);
				cvmSet(offset, 0, 1, 0);
				cvmSet(offset, 0, 2, 0);
				cvmSet(offset, 1, 0, 0);
				cvmSet(offset, 1, 1, 0.3);
				cvmSet(offset, 1, 2, 0);
				cvmSet(offset, 2, 0, 0);
				cvmSet(offset, 2, 1, 0);
				cvmSet(offset, 2, 2, 1);
				cvMatMul(H_matrix, offset, H_matrix);


				Mat H_mat = cvarrToMat(H_matrix);
				H_mat.t();
				warpPerspective(image_input, image_output, H_mat, image_input.size());
				//imshow("test1", image_output);
				//cv::waitKey(0);
				imwrite("C:\\Users\\roast_000\\Desktop\\4_point.jpg", image_output);




				return 0;
			}
		}
	}
}*/