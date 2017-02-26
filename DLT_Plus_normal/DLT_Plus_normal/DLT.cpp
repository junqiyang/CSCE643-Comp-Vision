#include "DLT.h"

void DLT(int n, CvPoint2D64f *p1, CvPoint2D64f *p2, CvMat *H) {
	int i;
	CvMat *A = cvCreateMat(2 * n, 9, CV_64FC1);
	CvMat *U = cvCreateMat(2 * n, 2 * n, CV_64FC1);
	CvMat *D = cvCreateMat(2 * n, 9, CV_64FC1);
	CvMat *V = cvCreateMat(9, 9, CV_64FC1);
	cvZero(A);
	for (i = 0; i<n; i++) {
		cvmSet(A, 2 * i, 3, -p1[i].x);
		cvmSet(A, 2 * i, 4, -p1[i].y);
		cvmSet(A, 2 * i, 5, -1);
		cvmSet(A, 2 * i, 6, p2[i].y*p1[i].x);
		cvmSet(A, 2 * i, 7, p2[i].y*p1[i].y);
		cvmSet(A, 2 * i, 8, p2[i].y);
		cvmSet(A, 2 * i + 1, 0, p1[i].x);
		cvmSet(A, 2 * i + 1, 1, p1[i].y);
		cvmSet(A, 2 * i + 1, 2, 1);
		cvmSet(A, 2 * i + 1, 6, -p2[i].x*p1[i].x);
		cvmSet(A, 2 * i + 1, 7, -p2[i].x*p1[i].y);
		cvmSet(A, 2 * i + 1, 8, -p2[i].x);
	}
	cvSVD(A, D, U, V, CV_SVD_U_T | CV_SVD_V_T);
	for (i = 0; i<9; i++)
		cvmSet(H, i / 3, i % 3, cvmGet(V, 8, i)/cvmGet(V, 8, 8));
}


Mat Normalization_DLT(int n, CvPoint2D64f * p) {
	double scale, tx, ty;
	double meanx, meany;
	double value;
	int i;
	
	meanx = 0;
	meany = 0;
	for (int i = 0; i < n; i++) {
		meanx += p[i].x;
		meany += p[i].y;
	}
	meanx /= (double)n;
	meany /= (double)n;

	value = 0;
	for (int i = 0; i < n; i++) {
		value += sqrt(pow(p[i].x - meanx, 2.0) + pow(p[i].y - meany, 2.0));
	}
	value /= (double)n;

	scale = sqrt(2.0) / value;
	tx = -scale * meanx;
	ty = -scale * meany;

	Mat H = Mat(3, 3, CV_64FC1);
	H.at<double>(0, 0) = scale;
	H.at<double>(0, 1) = 0;
	H.at<double>(0, 2) = tx;
	H.at<double>(1, 0) = 0;
	H.at<double>(1, 1) = scale;
	H.at<double>(1, 2) = ty;
	H.at<double>(2, 0) = 0;
	H.at<double>(2, 1) = 0;
	H.at<double>(2, 2) = 1.0;


	Mat x = Mat(3, 1, CV_64FC1);
	Mat xp = Mat(3, 1, CV_64FC1);
	for (int i = 0; i < n; i++) {
		x.at<double>(0, 0) = p[i].x;
		x.at<double>(1, 0) = p[i].y;
		x.at<double>(2, 0) = 1.0;
		xp = H * x;
		p[i].x = xp.at<double>(0, 0) / xp.at<double>(2, 0);
		p[i].y = xp.at<double>(1, 0) / xp.at<double>(2, 0);	
	}
	return H;
}