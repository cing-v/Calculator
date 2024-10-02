#include <check.h>

#include "s21_calculate.h"

START_TEST(calc_test_1) {
  char* sample = "2+2*2";
  double success = 6;
  double res = calc(sample);
  ck_assert_double_eq(res, success);
}
END_TEST

START_TEST(calc_test_2) {
  char* sample = "sin(12)";
  double success = sin(12);
  double res = calc(sample);
  ck_assert_double_eq(res, success);
}
END_TEST

START_TEST(calc_test_3) {
  char* sample = "cos(12)";
  double success = cos(12);
  double res = calc(sample);
  ck_assert_double_eq(res, success);
}
END_TEST

START_TEST(calc_test_4) {
  char* sample = "ln(12)";
  double success = log(12);
  double res = calc(sample);
  ck_assert_double_eq(res, success);
}
END_TEST
START_TEST(calc_test_5) {
  char* sample = "log(12)";
  double success = log10(12);
  double res = calc(sample);
  ck_assert_double_eq(res, success);
}
END_TEST
START_TEST(calc_test_6) {
  char* sample = "tan(12)";
  double success = tan(12);
  double res = calc(sample);
  ck_assert_double_eq(res, success);
}
END_TEST
START_TEST(calc_test_7) {
  char* sample = "asin(1)";
  double success = asin(1);
  double res = calc(sample);
  ck_assert_double_eq(res, success);
}
END_TEST
START_TEST(calc_test_8) {
  char* sample = "acos(1)";
  double success = acos(1);
  double res = calc(sample);
  ck_assert_double_eq(res, success);
}
END_TEST
START_TEST(calc_test_9) {
  char* sample = "atan(12)";
  double success = atan(12);
  double res = calc(sample);
  ck_assert_double_eq(res, success);
}
END_TEST

START_TEST(calc_test_10) {
  char* sample = "sqrt(12)";
  double success = sqrt(12);
  double res = calc(sample);
  ck_assert_double_eq(res, success);
}
END_TEST
START_TEST(calc_test_11) {
  char* sample = "12^12";
  double success = pow(12, 12);
  double res = calc(sample);
  ck_assert_double_eq(res, success);
}
END_TEST
START_TEST(calc_test_12) {
  char* sample = "123 % 3";
  double success = 123 % 3;
  double res = calc(sample);
  ck_assert_double_eq(res, success);
}
END_TEST
START_TEST(calc_test_13) {
  char* sample = "123 / 4 * 3 + 1";
  double success = 93.25;
  double res = calc(sample);
  ck_assert_double_eq(res, success);
}
END_TEST

START_TEST(calc_test_14) {
  char* sample = "123.1234 / 4.234 * 3 + 1";
  double success = 123.1234 / 4.234 * 3 + 1;
  double res = calc(sample);
  ck_assert_double_eq(res, success);
}
END_TEST

START_TEST(calc_test_15) {
  char* sample = "123 / 4 * sin(1)";
  double success = 25.875233;
  double res = calc(sample);
  ck_assert_double_eq(round(res), round(success));
}
END_TEST
START_TEST(calc_test_16) {
  char* sample = "123 / (cos(1) ^ 2) + log(10)";
  double success = 422.3388149604333596;
  double res = calc(sample);
  ck_assert_double_eq(round(res), round(success));
}
END_TEST
START_TEST(calc_test_17) {
  char* sample = "59 * 1234.12344 + 12398234.1239 / 3";
  double success = 59 * 1234.12344 + 12398234.1239 / 3;
  double res = calc(sample);
  ck_assert_double_eq(res, success);
}
START_TEST(calc_test_18) {
  char* sample = "-123 + 23 + (-100)";
  double success = -200;
  double res = calc(sample);
  ck_assert_double_eq(res, success);
}
END_TEST
START_TEST(calc_test_19) {
  char* sample = "-123 * 23 / (+2)";
  double success = -1414.5;
  double res = calc(sample);
  ck_assert_double_eq(res, success);
}
int main() {
  Suite* s1 = suite_create("Core");
  TCase* s21_test = tcase_create("Test");
  SRunner* sr = srunner_create(s1);
  suite_add_tcase(s1, s21_test);

  tcase_add_test(s21_test, calc_test_1);
  tcase_add_test(s21_test, calc_test_2);
  tcase_add_test(s21_test, calc_test_3);
  tcase_add_test(s21_test, calc_test_4);
  tcase_add_test(s21_test, calc_test_5);
  tcase_add_test(s21_test, calc_test_6);
  tcase_add_test(s21_test, calc_test_7);
  tcase_add_test(s21_test, calc_test_8);
  tcase_add_test(s21_test, calc_test_9);
  tcase_add_test(s21_test, calc_test_10);
  tcase_add_test(s21_test, calc_test_11);
  tcase_add_test(s21_test, calc_test_12);
  tcase_add_test(s21_test, calc_test_13);
  tcase_add_test(s21_test, calc_test_14);
  tcase_add_test(s21_test, calc_test_15);
  tcase_add_test(s21_test, calc_test_16);
  tcase_add_test(s21_test, calc_test_17);
  tcase_add_test(s21_test, calc_test_18);
  tcase_add_test(s21_test, calc_test_19);

  srunner_run_all(sr, CK_VERBOSE);
  srunner_free(sr);

  return 0;
}