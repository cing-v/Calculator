#include "s21_calculate.h"

void get_number_from_infix_expr(const char* infix_expr, char* result,
                                int* pos) {
  int i = 0;
  while (isdigit(infix_expr[*pos]) || infix_expr[*pos] == '.') {
    result[i++] = infix_expr[(*pos)++];
    result[i] = '\0';
  }
  (*pos)--;
  result[i] = '\0';
}

char get_func_from_infix_expr(const char* infix_expr, int* pos) {
  int i = 0;
  char c = 0;
  char func[5] = {0};
  while (infix_expr[*pos] >= 'a' && infix_expr[*pos] <= 'z')
    func[i++] = infix_expr[(*pos)++];
  (*pos)--;
  if (strcmp(func, "sin") == 0)
    c = 's';
  else if (strcmp(func, "cos") == 0)
    c = 'c';
  else if (strcmp(func, "tan") == 0)
    c = 't';
  else if (strcmp(func, "asin") == 0)
    c = 'i';
  else if (strcmp(func, "acos") == 0)
    c = 'o';
  else if (strcmp(func, "atan") == 0)
    c = 'a';
  else if (strcmp(func, "log") == 0)
    c = 'g';
  else if (strcmp(func, "ln") == 0)
    c = 'l';
  else if (strcmp(func, "sqrt") == 0)
    c = 'q';
  return c;
}

int operation_priority(char c) {
  int res = 0;
  if (c == '+' || c == '-')
    res = 1;
  else if (c == '*' || c == '/' || c == '%' || c == '^')
    res = 2;
  else if (c == '~' || c == '#')
    res = 3;

  return res;
}

char* push_in_postfix_expr(char* postfix_expr, char* stack, int* n_stack) {
  int len = (int)strlen(postfix_expr);
  postfix_expr[len++] = stack[*n_stack - 1];
  postfix_expr[len++] = ' ';
  postfix_expr[len] = '\0';
  stack[*n_stack - 1] = '\0';
  (*n_stack)--;
  return postfix_expr;
}
char* to_postfix(char* infix_expr) {
  int n_stack = 1, length_infix_expr = (int)strlen(infix_expr);
  char* stack = malloc(4095 * sizeof(char));
  char* postfix_expr = malloc(4096 * sizeof(char));
  char* number_expr = malloc(256 * sizeof(char));
  stack[0] = '\0';
  postfix_expr[0] = '\0';
  number_expr[0] = '\0';
  for (int i = 0; i < length_infix_expr; i++) {
    if (isdigit(infix_expr[i])) {
      get_number_from_infix_expr(infix_expr, number_expr, &i);
      postfix_expr = strcat(postfix_expr, number_expr);
      postfix_expr = strcat(postfix_expr, " ");
    } else if (infix_expr[i] >= 'a' && infix_expr[i] <= 'z') {
      stack[n_stack++] = get_func_from_infix_expr(infix_expr, &i);
      stack[n_stack++] = '(';
      i++;
    } else if (infix_expr[i] == '(') {
      stack[n_stack++] = infix_expr[i];
    } else if (infix_expr[i] == '+' || infix_expr[i] == '-' ||
               infix_expr[i] == '*' || infix_expr[i] == '/' ||
               infix_expr[i] == '%' || infix_expr[i] == '^') {
      if (i == 0 && infix_expr[i] == '+')
        stack[n_stack++] = '#';
      else if (i == 0 && infix_expr[i] == '-')
        stack[n_stack++] = '~';
      else if (infix_expr[i - 1] == '(' && infix_expr[i] == '+')
        stack[n_stack++] = '#';
      else if (infix_expr[i - 1] == '(' && infix_expr[i] == '-')
        stack[n_stack++] = '~';
      else {
        if (operation_priority(stack[n_stack - 1]) >=
            operation_priority(infix_expr[i])) {
          while (operation_priority(stack[n_stack - 1]) >=
                 operation_priority(infix_expr[i]))
            postfix_expr = push_in_postfix_expr(postfix_expr, stack, &n_stack);
          stack[n_stack++] = infix_expr[i];
        } else
          stack[n_stack++] = infix_expr[i];
      }
    } else if (infix_expr[i] == ')') {
      if (stack[n_stack - 1] != '(')
        while (stack[n_stack - 1] != '(')
          postfix_expr = push_in_postfix_expr(postfix_expr, stack, &n_stack);
      stack[n_stack - 1] = '\0';
      n_stack--;
      if (stack[n_stack - 1] >= 'a' && stack[n_stack - 1] <= 'z')
        postfix_expr = push_in_postfix_expr(postfix_expr, stack, &n_stack);
    }
  }
  if (n_stack > 0)
    while (n_stack > 0)
      postfix_expr = push_in_postfix_expr(postfix_expr, stack, &n_stack);
  free(number_expr);
  free(stack);
  return postfix_expr;
}

double calc(char* expr) {
  char* postfix_expr = to_postfix(expr);
  int length_expr = (int)strlen(postfix_expr);
  double* stack = malloc(4094 * sizeof(char));
  int n_stack = 0;
  char* number_expr = malloc(4093 * sizeof(char));
  number_expr[0] = '\0';
  int count = 0;
  double temp = 0.0;
  for (int i = 0; i < length_expr; i++) {
    if (isdigit(postfix_expr[i])) {
      get_number_from_infix_expr(postfix_expr, number_expr, &i);
      temp = atof(number_expr);
      stack[n_stack++] = temp;
    } else if (postfix_expr[i] == '+' || postfix_expr[i] == '-' ||
               postfix_expr[i] == '*' || postfix_expr[i] == '/' ||
               postfix_expr[i] == '%' || postfix_expr[i] == '^') {
      count++;
      double second = n_stack >= 1 ? stack[n_stack - 1] : 0;
      stack[n_stack - 1] = 0.0;
      n_stack--;
      double first = n_stack >= 1 ? stack[n_stack - 1] : 0;
      stack[n_stack - 1] = 0.0;
      n_stack--;
      switch (postfix_expr[i]) {
        case '+':
          first = first + second;
          break;
        case '-':
          first = first - second;
          break;
        case '*':
          first = first * second;
          break;
        case '/':
          first = first / second;
          break;
        case '%':
          first = fmod(first, second);
          break;
        case '^':
          first = pow(first, second);
          break;
      }
      stack[n_stack++] = first;
    } else if ((postfix_expr[i] >= 'a' && postfix_expr[i] <= 'z') ||
               postfix_expr[i] == '#' || postfix_expr[i] == '~') {
      count++;
      double first = n_stack >= 1 ? stack[n_stack - 1] : 0;
      stack[n_stack - 1] = 0.0;
      n_stack--;
      switch (postfix_expr[i]) {
        case 's':
          first = sin(first);
          break;
        case 'c':
          first = cos(first);
          break;
        case 't':
          first = tan(first);
          break;
        case 'i':
          first = asin(first);
          break;
        case 'o':
          first = acos(first);
          break;
        case 'a':
          first = atan(first);
          break;
        case 'g':
          first = log10(first);
          break;
        case 'l':
          first = log(first);
          break;
        case 'q':
          first = sqrt(first);
          break;
        case '#':
          first = +first;
          break;
        case '~':
          first = -first;
          break;
      }
      stack[n_stack++] = first;
    }
  }
  temp = stack[n_stack - 1];
  free(postfix_expr);
  free(number_expr);
  free(stack);
  return temp;
}
