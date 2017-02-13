#include "Line_infinity.h"

Mat line_infinity(Point3f point_input[4]) {
	Point3f l1 = point_input[0].cross(point_input[1]);
	Point3f l2 = point_input[2].cross(point_input[3]);
	Point3f l3 = point_input[0].cross(point_input[2]);
	Point3f l4 = point_input[1].cross(point_input[3]);
	Point3f P1 = l1.cross(l2);
	Point3f P2 = l3.cross(l4);
	Point3f VL = P1.cross(P2);

	VL.x = VL.x / VL.z;
	VL.y = VL.y / VL.z;
	VL.z = 1;

	Mat H = Mat::eye(3, 3, CV_64FC1);
	H.at<double>(2, 0) = VL.x;
	H.at<double>(2, 1) = VL.y;
	H.at<double>(2, 2) = VL.z;

//	visual_matrix(H, 3, 3);
/*
	CvMat * l = cvCreateMat(3, 1, CV_64FC1);
	cvmSet(l, 0, 0, VL.x);
	cvmSet(l, 1, 0, VL.y);
	cvmSet(l, 2, 0, VL.z);

	CvMat * test_l = cvCreateMat(3, 1, CV_64FC1);
	CvMat * H_t = cvCreateMat(3, 3, CV_64FC1);
	cvTranspose(H, H_t);
	cvInvert(H_t, H_t);
	cvMatMul(H_t, l, test_l);*/
//	visual_matrix(H_t, 3, 3);
//	visual_matrix(l, 3, 1);

	//visual_matrix(test_l, 3, 1);

	return H;
}