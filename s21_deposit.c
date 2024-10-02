#include "s21_deposit.h"

double deposit(double amount, double term, double rate, double replenish,
               int interest, int interest_term) {
  double period = (interest_term) ? 12.0 : 1.0;
  double repl_interest = 0.0;
  double total_payout = 0.0;
  rate /= 100.0;
  term /= 12.0;

  // leave interest on deposit
  if (interest) {
    total_payout = amount * pow(1.0 + rate / period, term * period);
    repl_interest = replenish * period / rate *
                    (pow(1.0 + rate / period, term * period) - 1.0);
    // pay interest to the investor
  } else {
    total_payout = amount * (1.0 + term * rate);
    repl_interest = replenish * period * term;
  }

  return total_payout + repl_interest;
}
