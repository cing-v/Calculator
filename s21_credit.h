#ifndef SRC_S21_CREDIT_H_
#define SRC_S21_CREDIT_H_

#include <math.h>

double differentiated(double total_amount, double rate, double term,
                      double *month_payment);
double annuity(double total_amount, double rate, double term);

#endif
