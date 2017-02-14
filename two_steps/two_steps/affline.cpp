#include "affline.h"

Mat Affline_H(Point3d point_input[4], Mat H) {
	Point3d l1 = point_input[0].cross(point_input[1]);
	Point3d l2 = point_input[0].cross(point_input[2]);
	Point3d m1 = point_input[3].cross(point_input[1]);
	Point3d m2 = point_input[3].cross(point_input[2]);

	Mat L1 = H * Mat(l1, true);
	Mat L2 = H * Mat(l2, true);
	Mat M1 = H * Mat(m1, true);
	Mat M2 = H * Mat(m2, true);

	l1 = Point3d(L1.at<double>(0), L1.at<double>(1), L1.at<double>(2));
	l2 = Point3d(L2.at<double>(0), L2.at<double>(1), L2.at<double>(2));
	m1 = Point3d(M1.at<double>(0), M1.at<double>(1), M1.at<double>(2));
	m2 = Point3d(M2.at<double>(0), M2.at<double>(1), M2.at<double>(2));

	Mat left = Mat(2, 2, CV_64FC1);
	Mat Right = Mat(2, 1, CV_64FC1);

	left.at<double>(0, 0) = l1.x * l2.x;
	left.at<double>(0, 1) = l1.x * l2.y + l1.y * l2.x;
	left.at<double>(1, 0) = m1.x * m2.x;
	left.at<double>(1, 1) = m1.x * m2.y + m1.y * m2.x;

	Right.at<double>(0, 0) = -l1.y * l2.y;
	Right.at<double>(0, 0) = -m1.y * m2.y;

	Mat s = left.inv() * Right;
	Mat S = Mat(2, 2, CV_64FC1);
	S.at<double>(0, 0) = s.at<double>(0);
	S.at<double>(0, 1) = s.at<double>(1);
	S.at<double>(1, 0) = s.at<double>(1);
	S.at<double>(1, 1) = 1;

	Mat U, D2, D, Ut;
	SVD::compute(S, D2, U, Ut, 0);
	pow(D2, 0.5, D);
	D = Mat::diag(D);
	Mat K = U * D * U.inv();

	Mat H_result = Mat(3, 3, CV_64FC1);
	H_result.at<double>(0, 0) = K.at<double>(0, 0);
	H_result.at<double>(0, 1) = K.at<double>(0, 1);
	H_result.at<double>(1, 0) = K.at<double>(1, 0);
	H_result.at<double>(1, 1) = K.at<double>(1, 1);

	H_result.at<double>(0, 2) = 0;
	H_result.at<double>(1, 2) = 0;
	H_result.at<double>(2, 0) = 0;
	H_result.at<double>(2, 1) = 0;
	H_result.at<double>(2, 2) = 1;

	printf("Ha: \n");
	visual_matrix(H_result, 3, 3);

	return H_result;
}