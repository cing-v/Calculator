#ifndef SRC_S21_DEPOSIT_H_
#define SRC_S21_DEPOSIT_H_

#include <math.h>

double deposit(double amount, double term, double rate, double replenish,
               int interest, int interest_term);
#endif