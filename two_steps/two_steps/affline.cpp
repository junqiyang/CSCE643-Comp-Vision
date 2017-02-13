#include "affline.h"


Mat Affline(Point3f point_input[8]) {
	Point3f l1 = point_input[0].cross(point_input[1]);
	Point3f l2 = point_input[0].cross(point_input[2]);
	Point3f m1 = point_input[3].cross(point_input[1]);
	Point3f m2 = point_input[3].cross(point_input[2]);






}