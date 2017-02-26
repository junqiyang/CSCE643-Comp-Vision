#include "one_step.h"
using namespace cv;

Mat image_input;
Mat image_output;

Point3d line_point[20];
int counter = 1;

void on_mouse(int event, int x, int y, int, void*) {
	if (image_input.empty()) {
		return;
	}
	if (event == CV_EVENT_LBUTTONUP) {
		circle(image_input, Point(x, y), 2, CV_RGB(255, 0, 0), -1);
		if (counter < 21) {
			line_point[counter - 1] = Point3d(x, y, 1);
			printf("Point (%f, %f) \n", (double)x, (double)y);
		}
		if (counter == 20) {
			line(image_input, Point2f(line_point[0].x, line_point[0].y), Point2f(line_point[1].x, line_point[1].y), CV_RGB(0, 255, 0), 2);
			line(image_input, Point2f(line_point[2].x, line_point[2].y), Point2f(line_point[3].x, line_point[3].y), CV_RGB(0, 255, 0), 2);
			line(image_input, Point2f(line_point[4].x, line_point[4].y), Point2f(line_point[5].x, line_point[5].y), CV_RGB(0, 255, 0), 2);
			line(image_input, Point2f(line_point[6].x, line_point[6].y), Point2f(line_point[7].x, line_point[7].y), CV_RGB(0, 255, 0), 2);
			line(image_input, Point2f(line_point[8].x, line_point[8].y), Point2f(line_point[9].x, line_point[9].y), CV_RGB(0, 255, 0), 2);
			line(image_input, Point2f(line_point[10].x, line_point[10].y), Point2f(line_point[11].x, line_point[11].y), CV_RGB(0, 255, 0), 2);
			line(image_input, Point2f(line_point[12].x, line_point[12].y), Point2f(line_point[13].x, line_point[13].y), CV_RGB(0, 255, 0), 2);
			line(image_input, Point2f(line_point[14].x, line_point[14].y), Point2f(line_point[15].x, line_point[15].y), CV_RGB(0, 255, 0), 2);
			line(image_input, Point2f(line_point[16].x, line_point[16].y), Point2f(line_point[17].x, line_point[17].y), CV_RGB(0, 255, 0), 2);
			line(image_input, Point2f(line_point[18].x, line_point[18].y), Point2f(line_point[19].x, line_point[19].y), CV_RGB(0, 255, 0), 2);
		}
		counter++;
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