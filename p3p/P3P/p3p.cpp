#include "p3p.h"

using namespace std;

void p3p(
	double fx, double fy, double cx, double cy,
	double R[4][3][3], double t[4][3],
	cv::Point2d u, cv::Point2d v, cv::Point2d w,
	cv::Point3d A, cv::Point3d B, cv::Point3d C)
{
	double ux = u.x, uy = u.y, uz = 1;
	double vx = v.x, vy = v.y, vz = 1;
	double wx = w.x, wy = w.y, wz = 1;

	double Ax = A.x, Ay = A.y, Az = A.z;
	double Bx = B.x, By = B.y, Bz = B.z;
	double Cx = C.x, Cy = C.y, Cz = C.z;


	double inv_fx = 1. / fx;
	double inv_fy = 1. / fy;
	double cx_fx = cx / fx;
	double cy_fy = cy / fy;
	double norm;

	ux = inv_fx * ux - cx_fx;
	uy = inv_fy * uy - cy_fy;
	norm = sqrt(ux*ux + uy*uy + uz*uz);
	ux = ux / norm;
	uy = uy / norm;
	uz = uz / norm;

	vx = inv_fx * vx - cx_fx;
	vy = inv_fy * vy - cy_fy;
	norm = sqrt(vx*vx + vy*vy + vz*vz);
	vx = vx / norm;
	vy = vy / norm;
	vz = vz / norm;

	wx = inv_fx * wx - cx_fx;
	wy = inv_fy * wy - cy_fy;
	norm = sqrt(wx*wx + wy*wy + wz*wz);
	wx = wx / norm;
	wy = wy / norm;
	wz = wz / norm;

	double AB = sqrt((Ax - Bx) * (Ax - Bx) + (Ay - By) * (Ay - By) + (Az - Bz) * (Az - Bz));
	double AC = sqrt((Ax - Cx) * (Ax - Cx) + (Ay - Cy) * (Ay - Cy) + (Az - Cz) * (Az - Cz));
	double BC = sqrt((Bx - Cx) * (Bx - Cx) + (By - Cy) * (By - Cy) + (Bz - Cz) * (Bz - Cz));

	double auv = ux * vx + uy * vy + uz * vz;
	double auw = ux * wx + uy * wy + uz * wz;
	double avw = vx * wx + vy * wy + vz * wz;

	double p = avw * 2;
	double q = auw * 2;
	double r = auv * 2;

	double a = (BC*BC) / (AB*AB);
	double b = (AC*AC) / (AB*AB);

	double a2 = a * a, b2 = b * b, p2 = p * p, q2 = q * q, r2 = r * r;
	double r3 = r2*r, pr2 = p*r2, r3q = r3 * q;
	double pr = p * r, pqr = q * pr;	
	double ab = a * b;


	double A4 = a2 + b2 - 2*a - 2*b + ab*(2 - r2)+ 1 ;
	double A3 = q*(-2 * (ab + a2 + 1 - b) + r2*ab + 4*a) + pr*(b - b2 + ab);
	double A2 = q2 + b2*(r2 + p2 - 2) - b*(p2 + pqr) - ab*(r2 + pqr) + (a2 - 2*a)*(2 + q2) + 2;
	double A1 = pr*(ab - b2 + b) + q*((p2 - 2)*b + 2 * (ab - a2) + 4*a - 2);
	double A0 = 1 + 2 * (b - a - ab) + b2 - b*p2 + a2;

	double real_roots[4];
	int n = solve_deg4(A4, A3, A2, A1, A0, real_roots[0], real_roots[1], real_roots[2], real_roots[3]);
	
	if (n == 0)
		return;

	double b0 = b * (p2*(a - 1 + b) + r2*(a - 1 - b) + pqr - a*pqr) * (p2*(a - 1 + b) + r2*(a - 1 - b) + pqr - a*pqr);


	double length[4][3];

	for (int i = 0; i < n; i++) {
		double x = real_roots[i];
		double x2 = x * x;
	
		if (x <= 0)
			continue;

		double b1 =
			((1 - a - b)*x2 + (q*a - q)*x + 1 - a + b) *
			(((r3*(a2 + ab*(2 - r2) - 2*a + b2 - 2 * b + 1)) * x +
			(r3q*(2 * (b - a2) + 4*a + ab*(r2 - 2) - 2) + pr2*(1 + a2 + 2 * (ab - a - b) + r2*(b - b2) + b2))) * x2 +
				(r3*(q2*(1 - 2 * a + a2) + r2*(b2 - ab) - 4*a + 2 * (a2 - b2) + 2) + r*p2*(b2 + 2 * (ab - b - a) + 1 + a2) + pr2*q*(4*a + 2 * (b - ab - a2) - 2 - r2*b)) * x +
				2 * r3q*(2*a - b - a2 + ab - 1) + pr2*(q2 - 4*a + 2 * (a2 - b2) + r2*b + q2*(a2 - 2*a) + 2) +
				p2*(p*(2 * (ab - a - b) + a2 + b2 + 1) + 2 * q*r*(b + a*2 - a2 - ab - 1)));

		if (b1 <= 0)
			continue;

		double inv_b0 = 1. / b0;
		double y = inv_b0 * b1;
		double v = x2 + y*y - x*y*r;
	
		if (v <= 0)
			continue;

		double PC = AB / sqrt(v);
		double PA = x * PC;
		double PB = y * PC;

		length[i][0] = PA;
		length[i][0] = PB;
		length[i][0] = PC;

	}

	cv::Point3d oA, oB, oC;
	std::vector<cv::Point3d> first, second;
	for (int i = 0; i < n; i++) {
		oA.x = length[i][0] * ux;
		oA.y = length[i][0] * uy;
		oA.z = length[i][0] * uz;
		first.push_back(oA);
		oB.x = length[i][1] * vx;
		oB.y = length[i][1] * vy;
		oB.z = length[i][1] * vz;
		first.push_back(oB);
		oC.x = length[i][2] * wx;
		oC.y = length[i][2] * wy;
		oC.z = length[i][2] * wz;
		first.push_back(oC);
		second.push_back(A);
		second.push_back(B);
		second.push_back(C);

		std::vector<uchar> inliers;
		cv::Mat aff(3, 4, CV_64F);
		int ret = cv::estimateAffine3D(first, second, aff, inliers);
		std::cout << aff << std::endl;
	}
	



}










