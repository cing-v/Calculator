#ifndef SRC_S21_CALCULATE_H_
#define SRC_S21_CALCULATE_H_

#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void get_number_from_infix_expr(const char* infix_expr, char* result, int* pos);
char get_func_from_infix_expr(const char* infix_expr, int* pos);
int operation_priority(char c);
char* push_in_postfix_expr(char* postfix_expr, char* stack, int* n_stack);
double calc(char* expr);

#endif
