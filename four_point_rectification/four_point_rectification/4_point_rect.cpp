
#include "4_point_rect.h"


void four_point_H(CvMat *H, Point2f opp[4], Point2f npp[4]) {
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
	visual_matrix(h_mat, 8, 1);
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





