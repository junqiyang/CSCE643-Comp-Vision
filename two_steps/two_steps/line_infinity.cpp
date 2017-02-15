#include "Line_infinity.h"

Mat line_infinity(Point3d point_input[8]) {
	Point3d l1 = point_input[0].cross(point_input[1]);
	Point3d l2 = point_input[2].cross(point_input[3]);
	Point3d l3 = point_input[0].cross(point_input[2]);
	Point3d l4 = point_input[1].cross(point_input[3]);
	Point3d P1 = l1.cross(l2);
	Point3d P2 = l3.cross(l4);
	Point3d VL = P1.cross(P2);

	VL.x = VL.x / VL.z;
	VL.y = VL.y / VL.z;
	VL.z = 1;

	Mat H = Mat::eye(3, 3, CV_64FC1);
	H.at<double>(2, 0) = VL.x;
	H.at<double>(2, 1) = VL.y;
	H.at<double>(2, 2) = VL.z;

	printf("Hp: \n");
	visual_matrix(H, 3, 3);
	return H;
}