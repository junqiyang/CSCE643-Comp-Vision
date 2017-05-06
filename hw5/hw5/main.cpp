#include "F_matrix.h"
#include <iostream>
#include <fstream>
using namespace cv;
using namespace std;
const int number = 40;

CvPoint2D64f  p1[40] = {
	{172,500},{210,513},{263,530},{264,422},{264,412},{190,369},{191,345},{265,298},{265,288},{267,170},
	{333,143},{365,140},{447,151},{443,295},{442,309},{436,446},{436,459},{429,588},{524,386},{521,421},
	{527,621},{289,583},{317,619},{352,661},{319,714},{282,659},{245,625},{156,626},{54 ,636},{130,688},
	{233,755},{363,783},{441,735},{504,696},{122,579},{115,550},{8  ,702},{95 ,776},{449,646},{544,785}
};

CvPoint2D64f  p2[number] = { 
	{29 ,531},{123,502},{230,470},{223,338},{222,327},{74 ,310},{72 ,273},{217,187},{216,175},{211,29 },
	{299,17 },{335,22 },{405,50 },{406,169},{406,180},{407,295},{408,305},{408,414},{461,229},{461,254},
	{464,397},{345,478},{430,467},{513,456},{598,464},{516,477},{551,487},{466,528},{510,578},{600,527},
	{670,485},{673,452},{608,436},{549,421},{324,561},{208,579},{662,575},{733,523},{408,414},{645,419}
};

CvPoint2D64f  p3[40] = {
	{ 172,500 },{ 210,513 },{ 263,530 },{ 264,422 },{ 264,412 },{ 190,369 },{ 191,345 },{ 265,298 },{ 265,288 },{ 267,170 },
	{ 333,143 },{ 365,140 },{ 447,151 },{ 443,295 },{ 442,309 },{ 436,446 },{ 436,459 },{ 429,588 },{ 524,386 },{ 521,421 },
	{ 527,621 },{ 289,583 },{ 317,619 },{ 352,661 },{ 319,714 },{ 282,659 },{ 245,625 },{ 156,626 },{ 54 ,636 },{ 130,688 },
	{ 233,755 },{ 363,783 },{ 441,735 },{ 504,696 },{ 122,579 },{ 115,550 },{ 8  ,702 },{ 95 ,776 },{ 449,646 },{ 544,785 }
};

CvPoint2D64f  p4[number] = {
	{ 29 ,531 },{ 123,502 },{ 230,470 },{ 223,338 },{ 222,327 },{ 74 ,310 },{ 72 ,273 },{ 217,187 },{ 216,175 },{ 211,29 },
	{ 299,17 },{ 335,22 },{ 405,50 },{ 406,169 },{ 406,180 },{ 407,295 },{ 408,305 },{ 408,414 },{ 461,229 },{ 461,254 },
	{ 464,397 },{ 345,478 },{ 430,467 },{ 513,456 },{ 598,464 },{ 516,477 },{ 551,487 },{ 466,528 },{ 510,578 },{ 600,527 },
	{ 670,485 },{ 673,452 },{ 608,436 },{ 549,421 },{ 324,561 },{ 208,579 },{ 662,575 },{ 733,523 },{ 408,414 },{ 645,419 }
};


int main(int argc, char** argv) {
	Mat F = Find_F(p1, p2, 40);

	vector<Point2f> points1(40);
	vector<Point2f> points2(40);
	for (int i = 0; i < 40; i++) {
		points1[i].x = p3[i].x;
		points1[i].y = p3[i].y;
		points2[i].x = p4[i].x;
		points2[i].y = p4[i].y;
	
	}
	ofstream myfile;
	myfile.open("C://Users//roast_000//Desktop//example.txt");

	double errrr = 0 ;
	for (int i = 0; i < 40; i++) {
		Mat m1 = (Mat_<double>(3, 1) << p3[i].x, p3[i].y, 1);
		Mat m2 = (Mat_<double>(1, 3) << p4[i].x, p4[i].y, 1);
		Mat res = m2*F*m1;
		errrr = errrr + res.at<double>(0, 0);
	}
	myfile << "F: " << F << endl;
	myfile << errrr << endl;
	myfile << determinant(F) << endl;


	Mat e = Mat(3, 3, CV_64FC1);
	Mat ep = Mat(3, 3, CV_64FC1);
	Find_E(F, e, ep);
	Mat P1 = Mat(3, 4, CV_64FC1);

	myfile << "e1: " << e << endl;
	myfile << "e2:" << ep << endl;

	P1.at<double>(0, 0) = 1;
	P1.at<double>(0, 1) = 0;
	P1.at<double>(0, 2) = 0;
	P1.at<double>(0, 3) = 0;
	P1.at<double>(1, 0) = 0;
	P1.at<double>(1, 1) = 1;
	P1.at<double>(1, 2) = 0;
	P1.at<double>(1, 3) = 0;
	P1.at<double>(2, 0) = 0;
	P1.at<double>(2, 1) = 0;
	P1.at<double>(2, 2) = 1;
	P1.at<double>(2, 3) = 0;

	Mat P2 = find_p(F, ep);
	myfile << "P1: " << P1 << endl;
	myfile << "P2: " << P2 << endl;

	Mat result = three_reconstruct(P1,P2,p3,p4,40);
	myfile << endl;
	myfile << endl;
	cout << result << endl;
	Mat result2, result3;
	Mat result4 = Mat(40 ,3, CV_32FC1);
	triangulatePoints(P1, P2, points1, points2, result3);
	result2 = result3.t();
	cout << result2.size() << endl;
	for (int i = 0; i < 40; i++) {
		result4.at<float>(i, 0) = result2.at<float>(i, 0) / result2.at<float>(i, 3);
		result4.at<float>(i, 1) = result2.at<float>(i, 1) / result2.at<float>(i, 3);
		result4.at<float>(i, 2) = result2.at<float>(i, 2) / result2.at<float>(i, 3);
		result2.at<float>(i, 3) = result2.at<float>(i, 3) / result2.at<float>(i, 3);
	}







	myfile << result4;
	myfile.close();

	return 0;



}
