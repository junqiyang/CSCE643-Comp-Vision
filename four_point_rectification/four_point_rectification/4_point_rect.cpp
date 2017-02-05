#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"

using namespace cv;

void visual_matrix(CvMat* A, int row, int col);


int main(int argc, char** argv) {
	char* filename_input;
	char* filename_output;

	IplImage* image_input;
	IplImage* image_output;

	CvPoint2D32f four_pixel_point[4];

	CvMat *H_matrix1;

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

	double x[4];
	double y[4];
	double xx[4];
	double yy[4];
	for (int i = 0; i < 4; i++) {
		printf("input %d pair: \n");
		scanf("%lf, %lf", x + i, y + i);
		printf("targeted %d pair: \n");
		scanf("%lf, %lf", xx + i, yy + i);
		printf("\n");
	}







}

void input_coordinate() {



}



void visual_matrix(CvMat* A, int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%lf  ", cvmGet(A, i, j));
		}
		printf("\n");
	}
}