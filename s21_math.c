#include "s21_math.h"
#include <stdio.h>

int s21_abs(int x) {
    return x < 0 ? -x : x;
}

long double s21_acos(double x) {
    if (x == 1) return 0;
    if (x == -1) return S21_PI;
    return (x < -1 || x > 1)? S21_NAN : S21_PI / 2 - s21_asin(x);
}

long double s21_asin(double x) {
    if (x == 1) return 1.57079633;
    if (x == -1) return -1.57079633;
    long double result = x;
    long double temp = x;
    if (x < 1.0 && x > -1.0) {
        x *= x;
        for (int i = 1; s21_fabs(temp) > S21_EPS; i += 2) {
            temp *= x * i / (i + 1);
            result += temp / (i + 2);
        }
    } else {
        result = S21_NAN;
    }
    return result;
}

long double s21_atan(double x) {
    return s21_asin(x / (s21_sqrt(x * x + 1.0)));
}

long double s21_ceil(double x) {
    return x < 0 ? (int)x : (int)x == x ? (int)x : (int)x + 1;
}

long double s21_cos(double x) {
    int div = (int)(x / S21_PI);
    x -= div * S21_PI;
    char sign = 1;
    if (div % 2 != 0)
        sign = -1;
    double result = 1.0;
    double inter = 1.0;
    double num = x * x;
    for (int i = 1; i <= 10; i++) {
        double comp = 2.0 * i;
        double den = comp * (comp - 1.0);
        inter *= num / den;
        if (i % 2 == 0)
            result += inter;
        else
            result -= inter;
    }
    return sign * result;
}

long double s21_exp(double x) {
    if (x >= 710) return S21_INF;
    long double result = 1.0;
    long double temp = 1.0;
    int i = 0;
    while (i < 1000) {
        temp *= x / ++i;
        result += temp;
    }
    return result;
}

long double s21_fabs(double x) {
    return x < 0.0 ? -x : x;
}

long double s21_floor(double x) {
    return x > 0 ? (int)x : (int)x == x ? (int)x : (int)x - 1;
}

long double s21_fmod(double x, double y) {
    if (x == 0.0 && y == 0.0)
        return S21_NAN;
    if (x > 0.0 && y == 0.0)
        return S21_INF;
    if (x < 0.0 && y == 0.0)
        return -S21_INF;
    long double res = x;
    int sign = 0;
    y = s21_fabs(y);
    if (res < 0.0 || y < 0.0) {
        sign = 1;
        res = s21_fabs((double)res);
    }
    while (1) {
        if (res < y)
            break;
        res -= y;
    }
    return (sign == 1) ? (res *= -1.0) : res;
}

long double s21_log(double x) {
    long double result;
    if (x < 0) return S21_NAN;
    if (x == 0) return -S21_INF;
    long double dest = 0;
    int exp = 0;
    for (; x > 1; x /= S21_E, exp++) continue;
    dest = s21_logger(x);
    result = dest + exp;
    return result;
}

long double s21_logger(double x) {
  x -= 1;
  int sign = 1;
  int n = 1;
  double pow_x = x;
  double precision = x;
  double dest = 0;
  while (s21_fabs(precision) > S21_EPS / 100000) {
    dest += precision;
    n += 1;
    pow_x *= x;
    sign = sign * (-1);
    precision = sign * pow_x / n;
  }
  return dest;
}

long double s21_pow(double base, double exp) {
    long double result = 0.0;
    if (exp == 0.0) {
        result = 1.0;
    } else if (base == 0) {
        result = 0.0;
    } else if (exp < 0.0) {
        result = s21_pow(1 / base, -exp);
    } else {
        result = 1.0;
        for (int i = 0; i < (long long)exp; i++) {
            result *= base;
        }
        exp -= (long long)exp;
        result *= s21_exp(exp * s21_log(base));
    }
    return result;
}

long double s21_sin(double x) {
    return s21_cos(S21_PI / 2.0 - x);
}

long double s21_sqrt(double x) {
    return (x < 0) ? S21_NAN : s21_pow(x, 0.5);
}

long double s21_tan(double x) {
    return s21_sin(x) / s21_cos(x);
}
