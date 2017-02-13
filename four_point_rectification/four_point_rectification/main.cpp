#include "4_point_rect.h"
#include "Line_infinity.h"
using namespace cv;

Mat image_input;
Mat image_output;

Point3f line_point[4];
int counter = 0;

void on_mouse(int event, int x, int y, int, void*) {
	if (image_input.empty()) {
		return;
	}
	if (event == CV_EVENT_LBUTTONUP) {
		counter++;
		printf("Point (%f, %f) \n", (double)x, (double)y);
		circle(image_input, Point(x, y), 2, CV_RGB(255, 0, 0), -1);
		if (counter < 5) {
			line_point[counter-1] = Point3d(x, y, 1);
			if (counter > 1) {
				line(image_input, Point2f(line_point[counter - 2].x, line_point[counter - 2].y), Point2f(line_point[counter - 1].x, line_point[counter - 1].y), CV_RGB(0, 255, 0), 2);
			}
		}
	}
	imshow("window", image_input);
}

int main(int argc, char** argv) {
	char* filename_input;
	char* filename_output;



	Point2f old_pixel_point[4];
	Point2f new_pixel_point[4];

	CvMat *H_matrix = cvCreateMat(3, 3, CV_64FC1);

	char prob_num = '2';

	if (argc >= 2) {
		filename_input = argv[1];
	}
	else {
		return 0;
	}

	if (argc >= 3) {
		prob_num = *argv[2];
	}

	if (prob_num == '1') {
		image_input = imread(filename_input, 1);
		IplImage *input_picutre = cvLoadImage(filename_input, 1);
	//	cv::waitKey(0);
		input_coordinate(old_pixel_point, new_pixel_point);
		four_point_H(H_matrix, old_pixel_point, new_pixel_point);
		visual_matrix(H_matrix, 3, 3);
		
		

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
	}

	if (prob_num == '2') {
		image_input = imread(filename_input, 1);
		namedWindow("window", CV_WINDOW_AUTOSIZE);
		imshow("window", image_input);
		cvSetMouseCallback("window", on_mouse);	
	
		for (;;) {
			uchar key = (uchar)waitKey();
			if (key == 'r') {
				CvMat* H = line_infinity(line_point);
				
				CvMat* offset = cvCreateMat(3, 3, CV_64FC1);
				cvmSet(offset, 0, 0, 0.1);
				cvmSet(offset, 0, 1, 0);
				cvmSet(offset, 0, 2, 0);
				cvmSet(offset, 1, 0, 0);
				cvmSet(offset, 1, 1, 0.1);
				cvmSet(offset, 1, 2, 0);
				cvmSet(offset, 2, 0, 0);
				cvmSet(offset, 2, 1, 0);
				cvmSet(offset, 2, 2, 1);
				cvMatMul(H, offset, H);
				Mat H_mat = cvarrToMat(H);



				warpPerspective(image_input, image_output, H_mat, image_input.size());
				imwrite("C:\\Users\\roast_000\\Desktop\\line_.jpg", image_output);
			}
		}	
	
	}


	return 0;
}
