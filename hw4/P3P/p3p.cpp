#include "p3p.h"

using namespace std;

void p3p(
	double fx, double fy, double cx, double cy,
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
	double ab = a * b, a_2 = 2 * a, a_4 = 4 * a;


	double A4 = -2 * b + b2 + a2 + 1 + ab*(2 - r2) - a_2;
	double A3 = q*(-2 * (ab + a2 + 1 - b) + r2*ab + a_4) + pr*(b - b2 + ab);
	double A2 = q2 + b2*(r2 + p2 - 2) - b*(p2 + pqr) - ab*(r2 + pqr) + (a2 - a_2)*(2 + q2) + 2;
	double A1 = pr*(ab - b2 + b) + q*((p2 - 2)*b + 2 * (ab - a2) + a_4 - 2);
	double A0 = 1 + 2 * (b - a - ab) + b2 - b*p2 + a2;

	double real_roots[4];
	int n = solve_deg4(A4, A3, A2, A1, A0, real_roots[0], real_roots[1], real_roots[2], real_roots[3]);
	
	if (n == 0)
		return;

	double b0 = b * ((p2*(a - 1 + b) + r2*(a - 1 - b) + pqr - a*pqr)) * ((p2*(a - 1 + b) + r2*(a - 1 - b) + pqr - a*pqr));


	//double length[4][3];
	cout << n << endl;



	for (int i = 0; i < n; i++) {
		double x = real_roots[i];
		double x2 = x * x;
	
		if (x <= 0)
			continue;

		double b1 =
			((1 - a - b)*x2 + (q*a - q)*x + 1 - a + b) *
			(((r3*(a2 + ab*(2 - r2) - a_2 + b2 - 2 * b + 1)) * x +
			(r3q*(2 * (b - a2) + a_4 + ab*(r2 - 2) - 2) + pr2*(1 + a2 + 2 * (ab - a - b) + r2*(b - b2) + b2))) * x2 +
			(r3*(q2*(1 - 2 * a + a2) + r2*(b2 - ab) - a_4 + 2 * (a2 - b2) + 2) + r*p2*(b2 + 2 * (ab - b - a) + 1 + a2) + pr2*q*(a_4 + 2 * (b - ab - a2) - 2 - r2*b)) * x +
			2 * r3q*(a_2 - b - a2 + ab - 1) + pr2*(q2 - a_4 + 2 * (a2 - b2) + r2*b + q2*(a2 - a_2) + 2) +
			p2*(p*(2 * (ab - a - b) + a2 + b2 + 1) + 2 * q*r*(b + a_2 - a2 - ab - 1)));

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
		
		cv::Point3d AA(PA*ux, PA*uy, PA*uz);
		cv::Point3d BB(PB*vx, PB*vy, PB*vz);
		cv::Point3d CC(PC*wx, PC*wy, PC*wz);

		vector<cv::Point3d> CamerP; 
		CamerP.push_back(AA);
		CamerP.push_back(BB);
		CamerP.push_back(CC);

		vector<cv::Point3d> worldP;

		worldP.push_back(A);
		worldP.push_back(B);
		worldP.push_back(C);

		cv::Mat R, t;

		Find_R(worldP, CamerP, R, t);

	//	length[i][0] = PA;
	//	length[i][0] = PB;
	//	length[i][0] = PC;

	//	cout << "PA:"<<PA << ",PB:" << PB << ",PC:" << PC << " " << endl;


		cout << "AA: " << AA << "BB: " << BB << "CC: " << CC<<endl;
	}
}


bool Find_R(const std::vector<cv::Point3d>& WorldP, const std::vector<cv::Point3d>& CamerP, cv::Mat& R, cv::Mat& T)
{
		cv::Mat Camera_P(3, 3, CV_64F);
		cv::Mat World_P(3, 3, CV_64F);

		//make it as mat, so we can use mat mulipication
		for (int i = 0; i < 3; i++) {
			cv::Mat row1 = (cv::Mat_<double>(1, 3) << CamerP[i].x, CamerP[i].y, CamerP[i].z);
			cv::Mat row2 = (cv::Mat_<double>(1, 3) << WorldP[i].x, WorldP[i].y, WorldP[i].z);
			row1.copyTo(Camera_P.row(i));
			row2.copyTo(World_P.row(i));
		}

		// Centroids:
		cv::Mat C_W = (World_P.row(0) + World_P.row(1) + World_P.row(2)) / 3;
		cv::Mat C_C = (Camera_P.row(0) + Camera_P.row(1) + Camera_P.row(2)) / 3;


		// Covariance matrix A:
		cv::Mat A = cv::Mat::zeros(3, 3, CV_64F);
		cv::Mat C = cv::Mat::zeros(3, 3, CV_64F);
		cv::Mat P = cv::Mat::zeros(3, 3, CV_64F);
		for (int i = 0; i < 3; i++) {
			C_C.copyTo(C.row(i));
			C_W.copyTo(P.row(i));
		}
		//calculate covariance matrix A
		A = (World_P - P).t()*(Camera_P - C);

		//SVD decomposition
		cv::Mat U, D, V;
		cv::SVD::compute(A, D, U, V, cv::SVD::FULL_UV);
		R = V.t()*U.t();
	
		double s = cv::determinant(R);

		if (s < 0) {
			V.row(2) *= -1;
			R = V.t()*U.t();
		}

		T = -R*C_W.t() + C_C.t();
	
		std::cout << "R : " << R << std::endl;
		std::cout << "T : " << T << std::endl;

		return true;
}













