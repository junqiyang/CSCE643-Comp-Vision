#include "Line_infinity.h"

CvMat * line_infinity(Point3f point_input[4]) {
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
	
	CvMat * H = cvCreateMat(3, 3, CV_64FC1);
	cvmSet(H, 0, 0, 1);
	cvmSet(H, 0, 1, 0);
	cvmSet(H, 0, 2, 0);
	cvmSet(H, 1, 0, 0);
	cvmSet(H, 1, 1, 1);
	cvmSet(H, 1, 2, 0);
	cvmSet(H, 2, 0, VL.x);
	cvmSet(H, 2, 1, VL.y);
	cvmSet(H, 2, 2, VL.z);

	visual_matrix(H, 3, 3);
	return H;
}