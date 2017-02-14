#include "line_infinity.h"
#include "affline.h"

using namespace cv;

Mat image_input;
Mat image_output;

Point3d line_point[4];
int counter = 0;

void on_mouse(int event, int x, int y, int, void*) {
	if (image_input.empty()) {
		return;
	}
	if (event == CV_EVENT_LBUTTONUP) {
		counter++;
		
		circle(image_input, Point(x, y), 2, CV_RGB(255, 0, 0), -1);
		if (counter < 5) {
			line_point[counter - 1] = Point3d(x, y, 1);
			printf("Point (%f, %f) \n", (double)x, (double)y);
				//line(image_input, Point2f(line_point[counter - 2].x, line_point[counter - 2].y), Point2f(line_point[counter - 1].x, line_point[counter - 1].y), CV_RGB(0, 255, 0), 2);
		}
		if (counter == 4) {
			line(image_input, Point2f(line_point[0].x, line_point[0].y), Point2f(line_point[1].x, line_point[1].y), CV_RGB(0, 255, 0), 2);
			line(image_input, Point2f(line_point[0].x, line_point[0].y), Point2f(line_point[2].x, line_point[2].y), CV_RGB(0, 255, 0), 2);
			line(image_input, Point2f(line_point[2].x, line_point[2].y), Point2f(line_point[3].x, line_point[3].y), CV_RGB(0, 255, 0), 2);
			line(image_input, Point2f(line_point[3].x, line_point[3].y), Point2f(line_point[1].x, line_point[1].y), CV_RGB(0, 255, 0), 2);
		}
	}
	imshow("window", image_input);
}

int main(int argc, char** argv) {
		char* filename_input;

		if (argc >= 2) {
			filename_input = argv[1];
			image_input = imread(filename_input, 1);
			namedWindow("window", CV_WINDOW_AUTOSIZE);
			imshow("window", image_input);
			cvSetMouseCallback("window", on_mouse);

			for (;;) {
				uchar key = (uchar)waitKey();
				if (counter > 4) {
					Mat H = line_infinity(line_point);
					Mat offset = Mat(3, 3, CV_64FC1);
					offset.at<double>(0, 0) = 0.35;
					offset.at<double>(0, 1) = 0;
					offset.at<double>(0, 2) = 0;
					offset.at<double>(1, 0) = 0;
					offset.at<double>(1, 1) = 0.35;
					offset.at<double>(1, 2) = 0;
					offset.at<double>(2, 0) = 0;
					offset.at<double>(2, 1) = 0;
					offset.at<double>(2, 2) = 1;
				
					warpPerspective(image_input, image_output, offset *  H, image_input.size());
					imwrite("C:\\Users\\roast_000\\Desktop\\line_.jpg", image_output);
					Mat affline_H = Affline_H(line_point, H);
					warpPerspective(image_input, image_output, H * affline_H, image_input.size());
					imwrite("C:\\Users\\roast_000\\Desktop\\aff_.jpg", image_output);



					return 0;
				}
			}
		}


}