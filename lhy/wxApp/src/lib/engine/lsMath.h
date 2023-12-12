#ifndef LS_MATH_H
#define LS_MATH_H

#include <limits>

#ifndef M_PI
#define M_PI        3.14159265358979323846264338327950288
#endif

#ifndef M_PI_2
#define M_PI_2      1.57079632679489661923132169163975144
#endif

#ifndef M_PI_4
#define M_PI_4      0.785398163397448309615660845819875721
#endif

#ifndef M_LN10
#define M_LN10      2.30258509299404568401799145468436421
#endif

#ifndef M_LN2
#define M_LN2       0.693147180559945309417232121458176568
#endif

#define MAX_REAL std::numeric_limits<double>::max()
#define MIN_REAL -std::numeric_limits<double>::max()

#define MAX_INT INT_MAX
#define MIN_INT INT_MIN

#ifndef NAN_REAL
#define NAN_REAL std::numeric_limits<double>::quiet_NaN()
#endif

#ifndef INF_REAL
#define INF_REAL std::numeric_limits<double>::infinity()
#endif

#endif // LS_MATH_H
