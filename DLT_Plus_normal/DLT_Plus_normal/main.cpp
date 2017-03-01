#include "DLT.h"
#include <iostream>
#include <fstream>
using namespace cv;
using namespace std;
const int number = 20;

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
		circle(image_input_2, Point(x, y), 2, CV_RGB(0, 255, 0), -1);
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
				imwrite("C:\\Users\\roast_000\\Desktop\\hw2_result\\input_1.jpg", image_input_1);
				imwrite("C:\\Users\\roast_000\\Desktop\\hw2_result\\input_2.jpg", image_input_2);
				CvMat *H = cvCreateMat(3, 3, CV_64FC1);

				ofstream myfile;
				myfile.open("C:\\Users\\roast_000\\Desktop\\hw2_result\\points.txt");

				for (int i = 0; i < number; i++) {
					myfile << (double)old_point[i].x << " " << (double)old_point[i].y << endl;
					myfile << (double)new_point[i].x << " " << (double)new_point[i].y << endl;
				}
				for (int i = 0; i < number; i++) {
					myfile <<"("<< (double)old_point[i].x << "," << (double)old_point[i].y << ") \Rightarrow ("<<(double)new_point[i].x << "," << (double)new_point[i].y<<")" << endl;
				}


				myfile.close();
				
				DLT(number, old_point, new_point, H);
				Mat H_r = cvarrToMat(H);
				std::cout << "H:" << std::endl;
				std::cout << H_r << std::endl;

		
				myfile.open("C:\\Users\\roast_000\\Desktop\\hw2_result\\H.txt");
				myfile << H_r << endl;
				myfile.close();

				Mat result;
				warpPerspective(image_input_1, result, H_r, cv::Size(image_input_1.cols + image_input_2.cols, image_input_1.rows + image_input_1.rows));
				cv::Mat half(result, cv::Rect(0, 0, image_input_2.cols, image_input_2.rows));
				//	warpPerspective(image_input_1, image_output, H_r, cv::Size(3000, 3000));
				image_input_2.copyTo(half);
				imshow("Result", result);
				waitKey(0);
				imwrite("C:\\Users\\roast_000\\Desktop\\hw2_result\\result_DLT.jpg", result);





			    Mat t1 =Normalization_DLT(number, old_point);
				Mat t2 =Normalization_DLT(number, new_point);
				for (int i = 0; i < number; i++) {
					printf("Point 1 (%f, %f) \n", (double)old_point[i].x, (double)old_point[i].y);
					printf("Point 2 (%f, %f) \n", (double)new_point[i].x, (double)new_point[i].y);				
				}
				for (int i = 0; i < number; i++) {
					myfile << "(" << (double)old_point[i].x << "," << (double)old_point[i].y << ") \Rightarrow (" << (double)new_point[i].x << "," << (double)new_point[i].y << ")" << endl;
				}


				DLT(number, old_point, new_point, H);
				H_r = cvarrToMat(H);
				std::cout << "h_bar" << std::endl;
				std::cout << H_r << std::endl;
				myfile.open("C:\\Users\\roast_000\\Desktop\\hw2_result\\H_hat.txt");
				myfile << H_r << endl;
				myfile.close();
				
				
				std::cout << "t1" << std::endl;
				std::cout << t1 << std::endl;
				std::cout << "t2" << std::endl;
				std::cout << t2 << std::endl;
				H_r = t2.inv() * H_r * t1;
				std::cout << "H:" << std::endl;
				std::cout << H_r << std::endl;
				
				
				myfile.open("C:\\Users\\roast_000\\Desktop\\hw2_result\\Ts.txt");
				myfile << t1 << endl;
				myfile << t2 << endl;
				myfile.close();

				warpPerspective(image_input_1, result, H_r, cv::Size(image_input_1.cols + image_input_2.cols, image_input_1.rows + image_input_1.rows));
				imshow("Result", result);
				waitKey(0);
				cv::Mat half2(result, cv::Rect(0, 0, image_input_2.cols, image_input_2.rows));
				
				//	warpPerspective(image_input_1, image_output, H_r, cv::Size(3000, 3000));
				image_input_2.copyTo(half2);
				imshow("Result", result);

				waitKey(0);
				imwrite("C:\\Users\\roast_000\\Desktop\\hw2_result\\result_DLT_normal.jpg", result);

				myfile.open("C:\\Users\\roast_000\\Desktop\\hw2_result\\normal_points.txt");

				for (int i = 0; i < number; i++) {
					myfile << (double)old_point[i].x <<" "<< (double)old_point[i].y <<endl;
					myfile << (double)new_point[i].x <<" "<< (double)new_point[i].y <<endl;
				}
				myfile.close();


				myfile.open("C:\\Users\\roast_000\\Desktop\\hw2_result\\normal_H.txt");
				myfile << H_r << endl;
				myfile.close();


				waitKey(0);







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
