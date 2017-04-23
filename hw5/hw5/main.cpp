#include "F_matrix.h"
#include <iostream>
#include <fstream>
using namespace cv;
using namespace std;
const int number = 20;

CvPoint2D64f  p1[number] = { {178,369},{190,347},{263,411},{256,287},{266.171},{331,143},{446,152},{443,295},{524,386},{542,408},{381,558},{315,557},{232,536},{154,564},{157,626},{316,645},{450,615},{530,678},{278,733},{404,759}};
CvPoint2D64f  p2[number] = { {51,311}, {71,273}, {263,411},{215,175},{210,30}, {303,16}, {405,49}, {405,168},{461,230},{473,255},{286,440},{263,469},{167,510},{294,544},{464,529},{488,466},{418,429},{523,414},{634,475},{640,445}};

int main(int argc, char** argv) {
	Mat F = Find_F(p1, p2, 20);
	cout << "F: " << F << endl;
	Mat e = Mat(3, 3, CV_64FC1);
	Mat ep = Mat(3, 3, CV_64FC1);
	Find_E(F, e, ep);
	Mat P = find_p(F, ep);
	cout << "P: " << P << endl;
	return 0;



}
