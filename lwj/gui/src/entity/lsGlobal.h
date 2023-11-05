#ifndef LS_GLOBAL_H
#define LS_GLOBAL_H

#define _CRT_SECURE_NO_WARNINGS

#include <float.h>
#include <math.h>

typedef double lsReal;

#define MAX_REAL    DBL_MAX
#define MIN_REAL    DBL_MIN

#define MIN(a, b) ((a) < (b)) ? (a) : (b)
#define MAX(a, b) ((a) < (b)) ? (b) : (a)

// Epsilon
#define EPS 1E-6

// Ô²ÖÜÂÊpi
#define PI 3.14159265358979f

#define CCW true
#define CW  false

#endif // LS_GLOBAL_H
