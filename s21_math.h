#ifndef SRC_S21_MATH_H_
#define SRC_S21_MATH_H_

#define S21_PI 3.14159265359
#define S21_E 2.71828182845904523536
#define S21_EPS 1e-15
#define S21_NAN 0.0 / 0.0
#define S21_INF 1.0 / 0.0

int s21_abs(int x);
long double s21_acos(double x);
long double s21_asin(double x);
long double s21_atan(double x);
long double s21_ceil(double x);
long double s21_cos(double x);
long double s21_exp(double x);
long double s21_fabs(double x);
long double s21_floor(double x);
long double s21_fmod(double x, double y);
long double s21_log(double x);
long double s21_pow(double base, double exp);
long double s21_sin(double x);
long double s21_sqrt(double x);
long double s21_tan(double x);

long double s21_logger(double x);

#endif  // SRC_S21_MATH_H_
