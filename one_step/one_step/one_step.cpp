#include "one_step.h"
using namespace std;


Mat one_step(Point3d point_input[20]) {
	Point3d l1 = point_input[0].cross(point_input[1]);
	Point3d m1 = point_input[2].cross(point_input[3]);
	Point3d l2 = point_input[4].cross(point_input[5]);
	Point3d m2 = point_input[6].cross(point_input[7]);
	Point3d l3 = point_input[8].cross(point_input[9]);
	Point3d m3 = point_input[10].cross(point_input[11]);
	Point3d l4 = point_input[12].cross(point_input[13]);
	Point3d m4 = point_input[14].cross(point_input[15]);
	Point3d l5 = point_input[16].cross(point_input[17]);
	Point3d m5 = point_input[18].cross(point_input[19]);

	cout << l1 << endl;
	cout << l2 << endl;
	cout << l3 << endl;
	cout << l4 << endl;
	cout << l5 << endl;
	cout << m1 << endl;
	cout << m2 << endl;
	cout << m3 << endl;
	cout << m4 << endl;
	cout << m5 << endl;


	double line[5][5] = {
		{ l1.x * m1.x, (l1.x * m1.y + l1.y * m1.x) / 2,  l1.y*m1.y,   (l1.x * m1.z + l1.z *m1.x) / 2, (l1.y * m1.z + l1.z * m1.y) / 2},
		{ l2.x * m2.x, (l2.x * m2.y + l2.y * m2.x) / 2,  l2.y*m2.y,   (l2.x * m2.z + l2.z *m2.x) / 2, (l2.y * m2.z + l2.z * m2.y) / 2 },
		{ l3.x * m3.x, (l3.x * m3.y + l3.y * m3.x) / 2,  l3.y*m3.y,   (l3.x * m3.z + l3.z *m3.x) / 2, (l3.y * m3.z + l3.z * m3.y) / 2 },
		{ l4.x * m4.x, (l4.x * m4.y + l4.y * m4.x) / 2,  l4.y*m4.y,   (l4.x * m4.z + l4.z *m4.x) / 2, (l4.y * m4.z + l4.z * m4.y) / 2 },
		{ l5.x * m5.x, (l5.x * m5.y + l5.y * m5.x) / 2,  l5.y*m5.y,   (l5.x * m5.z + l5.z *m5.x) / 2, (l5.y * m5.z + l5.z * m5.y) / 2 },
	};
	double line_2[5][1] = { { -l1.z* m1.z },{ -l2.z* m2.z },{ -l3.z* m3.z },{ -l4.z* m4.z },{ -l5.z* m5.z }, };

	Mat LL1 = Mat(5, 5, CV_64FC1, line);
	cout << LL1 << endl;
	Mat LL2 = Mat(5, 1, CV_64FC1, line_2);
	cout << LL2 << endl;
	Mat A = Mat(5, 1, CV_64FC1);
	solve(LL1, LL2, A);
	std::cout << "A: " << A << std::endl;
	
	Mat C = Mat(3, 3, CV_64FC1);
	C.at<double>(0, 0) = A.at<double>(0);
	C.at<double>(0, 1) = A.at<double>(1) / 2;
	C.at<double>(0, 2) = A.at<double>(3) / 2;
	C.at<double>(1, 0) = A.at<double>(1) / 2;
	C.at<double>(1, 1) = A.at<double>(2);
	C.at<double>(1, 2) = A.at<double>(4) / 2;
	C.at<double>(2, 0) = A.at<double>(3) / 2;
	C.at<double>(2, 1) = A.at<double>(4) / 2;
	C.at<double>(2, 2) = 1;
	cout << "C:" << C << endl;
	
	Mat U, D, Ut;
	SVD::compute(C, D, U, Ut, 0);

	Mat KKt = C(Range(0, 2), Range(0, 2));
	cout << "KKt: " << KKt << endl;

	Mat D2;
	SVD::compute(KKt, D2, U, Ut, 0);
	
	
	pow(D2, 0.5, D);
	D = Mat::diag(D);

	Mat K = U * D * Ut;
	std::cout << "K: " << K << std::endl;
	
	Mat v;
	Mat sub(2, 1, CV_64FC1);
	sub.at<double>(0, 0) = C.at<double>(0, 2);
	sub.at<double>(1, 0) = C.at<double>(1, 2);

	solve(K, sub, v, CV_LU);
	std::cout <<"v: "<< v <<std::endl;
	Mat H;
	double data[2][1] = { { 0 },{ 0 } };
	Mat left = Mat(2, 1, CV_64FC1, data);
	hconcat(K, left, H);

	double data2[1][3] = { { v.at<double>(0), v.at<double>(1), 1 } };
	Mat bu = Mat(1, 3, CV_64FC1, data2);
	vconcat(H, bu, H);
	std::cout << H << std::endl;

	return H;
	

}