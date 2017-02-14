#include "visual.h"

void visual_matrix(Mat A, int row, int col) {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			printf("%lf  ", A.at<double>(i, j));
		}
		printf("\n");
	}
}