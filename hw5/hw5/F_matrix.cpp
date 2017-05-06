#include"F_matrix.h"


Mat Normalization_F(int n, CvPoint2D64f * p) {
	double S, tx, ty;
	double meanx, meany;
	double sum;
	int i;
	meanx = 0;
	meany = 0;
	for (int i = 0; i < n; i++) {
		meanx += p[i].x;
		meany += p[i].y;
	}
	meanx /= (double)n;
	meany /= (double)n;
	sum = 0;
	for (int i = 0; i < n; i++) {
		sum += sqrt(pow(p[i].x - meanx, 2.0) + pow(p[i].y - meany, 2.0));
	}
	sum /= (double)n;

	S = sqrt(2.0) / sum;
	tx = -S * meanx;
	ty = -S * meany;

	Mat H = Mat(3, 3, CV_64FC1);
	H.at<double>(0, 0) = S;
	H.at<double>(0, 1) = 0;
	H.at<double>(0, 2) = tx;
	H.at<double>(1, 0) = 0;
	H.at<double>(1, 1) = S;
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

Mat Find_F(CvPoint2D64f * p1, CvPoint2D64f * p2, int n) {
	int i;
	Mat A = Mat(n, 9, CV_64FC1);
	Mat Ftmp = Mat(3, 3, CV_64FC1);
	Mat T1 = Normalization_F(n, p1);
	Mat T2 = Normalization_F(n, p2);
	
	Mat D = Mat(n, 9, CV_64FC1);
	Mat U = Mat(n, n, CV_64FC1);
	Mat V = Mat(9, 9, CV_64FC1);

	Mat DD = Mat(3, 3, CV_64FC1);
	Mat DDD = Mat(3, 3, CV_64FC1);
	Mat UU = Mat(3, 3, CV_64FC1);
	Mat VV = Mat(3, 3, CV_64FC1);
	Mat SVG = Mat(3, 3, CV_64FC1);

	Mat F = Mat(3, 3, CV_64FC1);



	for (i = 0; i<n; i++)
	{
		A.at<double>(i, 0) = p2[i].x * p1[i].x;
		A.at<double>(i, 1) = p2[i].x * p1[i].y;
		A.at<double>(i, 2) = p2[i].x;
		A.at<double>(i, 3) = p2[i].y * p1[i].x;
		A.at<double>(i, 4) = p2[i].y * p1[i].y;
		A.at<double>(i, 5) = p2[i].y;
		A.at<double>(i, 6) = p1[i].x;
		A.at<double>(i, 7) = p1[i].y;
		A.at<double>(i, 8) = 1;
	}

	SVD::compute(A, D, U, V, SVD::FULL_UV);

	for (i = 0; i < 9; i++) {
		Ftmp.at<double>(i / 3, i % 3) = V.at<double>(8, i);
	}

	SVD::compute(Ftmp, SVG, UU, VV, SVD::FULL_UV);

	DD = Mat::diag(SVG);
	DD.at<double>(2, 2) = 0;

	Ftmp = UU*DD*VV.t();
	F = T2.t()*Ftmp*T1;
	std::cout << F << std::endl;

	F.at<double>(0, 0) = F.at<double>(0, 0) / F.at<double>(2, 2);
	F.at<double>(0, 1) = F.at<double>(0, 1) / F.at<double>(2, 2);
	F.at<double>(0, 2) = F.at<double>(0, 2) / F.at<double>(2, 2);
	F.at<double>(1, 0) = F.at<double>(1, 0) / F.at<double>(2, 2);
	F.at<double>(1, 1) = F.at<double>(1, 1) / F.at<double>(2, 2);
	F.at<double>(1, 2) = F.at<double>(1, 2) / F.at<double>(2, 2);
	F.at<double>(2, 0) = F.at<double>(2, 0) / F.at<double>(2, 2);
	F.at<double>(2, 1) = F.at<double>(2, 1) / F.at<double>(2, 2);
	F.at<double>(2, 2) = F.at<double>(2, 2) / F.at<double>(2, 2);
	
	return F;
}


void Find_E(Mat F, Mat & e, Mat & ep) {
	Mat D = Mat(3, 3, CV_64FC1);
	Mat U = Mat(3, 3, CV_64FC1);
	Mat V = Mat(3, 3, CV_64FC1);
	SVD::compute(F, D, U, V, SVD::FULL_UV);
	for (int i = 0; i < 3; i++) {
		e.at<double>(i, 0) = V.at<double>(2, i) / V.at<double>(2, 2);
		ep.at<double>(i, 0) = U.at<double>(2, i) / U.at<double>(2, 2);
	}
}


Mat find_p(Mat F, Mat ep) {
	Mat epx = Mat(3, 3, CV_64FC1);
	epx.at<double>(0, 0) = 0;
	epx.at<double>(0, 1) = -ep.at<double>(2, 0);
	epx.at<double>(0, 2) = ep.at<double>(1, 0);
	epx.at<double>(1, 0) = ep.at<double>(2, 0);
	epx.at<double>(1, 1) = 0;
	epx.at<double>(1, 2) = -ep.at<double>(0, 0);
	epx.at<double>(2, 0) = -ep.at<double>(1, 0);
	epx.at<double>(2, 1) = ep.at<double>(0, 0);
	epx.at<double>(2, 2) = 0;

	Mat tmp = Mat(3, 3, CV_64FC1);
	Mat Pp = Mat::zeros(3, 4, CV_64FC1);
	tmp = epx * F;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			Pp.at<double>(i,j) = tmp.at<double>(i, j);
		}
	}
	for (int i = 0; i < 3; i++) {
		Pp.at<double>(i, 3) = ep.at<double>(i, 0);
	}
	return Pp;
}


Mat Find_A(Mat P1, Mat P2, CvPoint2D64f x1, CvPoint2D64f x2) {
	Mat A = Mat(4, 4, CV_64FC1);
	Mat row1, row2, row3, row4;
	row1 = x1.x * P1.row(2) - P1.row(0);
	row2 = x1.y * P1.row(2) - P1.row(1);
	row3 = x2.x * P2.row(2) - P2.row(0);
	row4 = x2.x * P2.row(2) - P2.row(1);
	row1.copyTo(A.row(0));
	row2.copyTo(A.row(1));
	row3.copyTo(A.row(2));
	row4.copyTo(A.row(3));
	return A;
}

Mat three_reconstruct(Mat P1, Mat P2, CvPoint2D64f* x1, CvPoint2D64f* x2, int n) {
	Mat result = Mat(n, 3, CV_64FC1);
	for (int i = 0; i < n; i++) {
		Mat A = Find_A(P1, P2, x1[i], x2[i]);
		Mat D, U, V;
		SVD::compute(A, D, U, V, SVD::FULL_UV);
		double x1 = V.at<double>(3, 0);
		double x2 = V.at<double>(3, 1);
		double x3 = V.at<double>(3, 2);
		double x4 = V.at<double>(3, 3);
		
		Mat X = V.row(3);
		result.at<double>(i, 0) = x1 / x4;
		result.at<double>(i, 1) = x2 / x4;
		result.at<double>(i, 2) = x3 / x4;

	}
	return result;
}