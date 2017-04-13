#ifndef POLYNOM_SOLVER_H
#define POLYNOM_SOLVER_H

#include "opencv2/imgproc.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include <math.h>
#include <iostream>

int solve_deg2(double a, double b, double c, double & x1, double & x2);

int solve_deg3(double a, double b, double c, double d,
	double & x0, double & x1, double & x2);

int solve_deg4(double a, double b, double c, double d, double e,
	double & x0, double & x1, double & x2, double & x3);

#endif // POLYNOM_SOLVER_H#pragma once
