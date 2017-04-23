#include "p3p.h"
using namespace std;



int main(int argc, char** argv) {

	
	cv::Point2d u(96,120), v(409,101), w(99,554), z(468,521);
	cv::Point3d A(0,0,0), B(210,0,0), C(0,-270,0), D(210,-270,0);

	p3p(681.93745630142, 680.4544899305517, 291.7473867898793, 371.1215194342687,u, v, w, A, B, C);
	vector<cv::Point2d> image_p = { u, v, w,z };
	
	std::vector<cv::Point3d> world_p = {A,B,C,D};

	cv::Mat R = cv::Mat(3, 3, CV_64F);
	cv::Mat t = cv::Mat(3, 1, CV_64F);
	
	cv::Mat cameraMatrix = cv::Mat(3, 3, CV_64F);
	cameraMatrix.at<double>(0, 0) = 681.93745630416;
	cameraMatrix.at<double>(0, 1) = 0;
	cameraMatrix.at<double>(0, 2) = 291.7473867898793;
	cameraMatrix.at<double>(1, 0) = 0;
	cameraMatrix.at<double>(1, 1) = 680.4544899305517;
	cameraMatrix.at<double>(1, 2) = 371.1215194342687;
	cameraMatrix.at<double>(2, 0) = 0;
	cameraMatrix.at<double>(2, 1) = 0;
	cameraMatrix.at<double>(2, 2) = 1;
	cout << "CCCC" << cameraMatrix << endl;
	cv::Mat distortionCoefficients = cv::Mat(1, 5, CV_64F);
	distortionCoefficients.at<double>(0, 0) = 0.3358418806175377;
	distortionCoefficients.at<double>(0, 1) = -2.263777666639354;
	distortionCoefficients.at<double>(0, 2) = 0.004275553513874104;
	distortionCoefficients.at<double>(0, 3) = -0.0003137584122629161;
	distortionCoefficients.at<double>(0, 4) = 4.291622220855106;
	
	cv::solvePnP(world_p, image_p, cameraMatrix, distortionCoefficients, R, t, 0, CV_P3P);
	cv::Mat r1;
	cv::Rodrigues(R, r1);
	cout << "R(P3P): " << r1 << endl;
	cout << "T(P3P): " << t << endl;
	cv::solvePnP(world_p, image_p, cameraMatrix, distortionCoefficients, R, t, 0, CV_ITERATIVE);
	cv::Mat r2;
	cv::Rodrigues(R, r2);
	cout << "R(PNP_ITERATIVE): " << r2 << endl;
	cout << "T(PNP_ITERATIVE): " << t << endl;
	cv::solvePnP(world_p, image_p, cameraMatrix, distortionCoefficients, R, t, 0, CV_EPNP);
	cv::Mat r3;
	cv::Rodrigues(R, r3);
	cout << "R(PNP_EPNP): " << r3 << endl;
	cout << "t(PNP_EPNP): " << t << endl;
	return 0;
}
