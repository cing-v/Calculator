#include "s21_credit.h"

double differentiated(double total_amount, double rate, double term,
                      double *month_payment) {
  double month_rate = rate / 1200.0;  // Ежемесячная процентная ставка    (R)
  double month_debt = total_amount / term;  // Ежемесячное тело кредита (K / n)

  double rest_amount = 0;  // Остаток кредита на дату рассчета (OctKi)
  double month_overpay = 0;  // Ежемесячная плата по процентам   (OctKi * R)
  double overpayment = 0;  // Общая переплата

  for (int i = 0; i < term; i++) {
    // OctKi = K - (K / n) * (month - 1)
    rest_amount = total_amount - month_debt * i;

    // DEPi = (K / n) + OctKi * R
    month_overpay = rest_amount * month_rate;
    month_payment[i] = month_debt + month_overpay;  // Ежемесячный платеж (DEPi)

    // calculate summ of overpayment
    overpayment += month_overpay;
  }

  return overpayment;
}

double annuity(double total_amount, double rate, double term) {
  double month_rate = rate / 1200.0;

  // calculate the additional count: (1 + М) ^ S
  double add_count = pow(month_rate + 1.0, term);

  // calculate the annuity coefficient (K = (М * (1 + М) ^ S) / ((1 + М) ^ S —
  // 1)
  double K = (month_rate * add_count) / (add_count - 1.0);

  return total_amount * K;
}
