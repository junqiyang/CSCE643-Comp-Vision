#include "DLT.h"
using namespace cv;
using namespace std;
const int number = 10;

CvPoint2D64f old_point[number];
CvPoint2D64f new_point[number];
Mat image_input_1;
Mat image_input_2;
Mat image_output;
int counter = 1;

void on_mouse(int event, int x, int y, int, void*) {
	if (image_input_1.empty() || image_input_2.empty()) {
		return;
	}
	if (event == CV_EVENT_LBUTTONUP && counter <= number) {
		circle(image_input_1, Point(x, y), 2, CV_RGB(255, 0, 0), -1);
		if (counter < number + 1) {
			old_point[counter - 1].x = x;
			old_point[counter - 1].y = y;
			printf("Point 1 (%f, %f) \n", (double)x, (double)y);
		}
		counter++;
	}
	else if (event == CV_EVENT_LBUTTONUP && counter <= 2*number && counter > number) {
		circle(image_input_2, Point(x, y), 2, CV_RGB(255, 0, 0), -1);
		if (counter < number*2 + 1) {
			new_point[counter - number - 1].x = x;
			new_point[counter - number - 1].y = y;
			printf("Point 2 (%f, %f) \n", (double)x, (double)y);
		}
		counter++;
	}

	if (counter <= number ) {
		imshow("window", image_input_1);
	}
	else if (counter >= number + 1 && counter <= number * 2) {
		imshow("window", image_input_2);
	}

}

int main(int argc, char** argv) {
	char* filename_input;
	char* filename_input_2;

	if (argc >= 2) {
		filename_input = argv[1];
		filename_input_2 = argv[2];
		image_input_1 = imread(filename_input_2, 1);
		image_input_2 = imread(filename_input, 1);
		namedWindow("window", CV_WINDOW_AUTOSIZE);
		imshow("window", image_input_1);
		//		namedWindow("window", CV_WINDOW_AUTOSIZE);
		//		imshow("window", image_input_2);
		cvSetMouseCallback("window", on_mouse);
		for (;;) {
			uchar key = (uchar)waitKey();
			if (counter > number * 2) {
				CvMat *H = cvCreateMat(3, 3, CV_64FC1);
			    Mat t1 =Normalization_DLT(number, old_point);
				Mat t2 =Normalization_DLT(number, new_point);
				DLT(number, old_point, new_point, H);
				Mat H_r = cvarrToMat(H);
				H_r = t2.inv() * H_r * t1;
				std::cout << H_r << std::endl;
				Mat result;

				warpPerspective(image_input_1, result, H_r, cv::Size(image_input_1.cols + image_input_2.cols, image_input_2.rows +image_input_1.rows));
				imshow("Result", result);
				waitKey(0);
				cv::Mat half(result, cv::Rect(0, 0, image_input_2.cols, image_input_2.rows));
				
				//	warpPerspective(image_input_1, image_output, H_r, cv::Size(3000, 3000));
				image_input_2.copyTo(half);
				imshow("Result", result);

				waitKey(0);
				imwrite("C:\\Users\\roast_000\\Desktop\\result_DLT_normal.jpg", result);
				return 0;

			}
		}
	}
}
/*


		
			
			if (counter > 20) {
				Mat affline_H = one_step(line_point);
				visual_matrix(affline_H, 3, 3);
				warpPerspective(image_input, image_output, affline_H.inv(), cv::Size(3000, 3000));
				imwrite("C:\\Users\\roast_000\\Desktop\\one_step.jpg", image_output);
				return 0;
			}
		}
	}
}
*/
