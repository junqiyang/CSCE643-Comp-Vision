#include "image_wrap.h"

void inter(IplImage * img, CvPoint2D32f coor, unsigned char * value);

void visual_matrix(CvMat* A, int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%lf  ", cvmGet(A, i, j));
		}
		printf("\n");
	}
}



