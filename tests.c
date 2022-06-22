#include <check.h>
#include "smartcalc.h"

START_TEST(test_1) {
    double res = 0.0;
    char *str = "100*4+23-50/ 0.5+(123-112)";
    int result = main_c(str, 0.0, &res);

    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_2) {
    double res = 0.0;
    char *str = "sin(cos(111))+tan(sqrt(222))-acos(asin(333))*atan(444)/ln(log(555))";
    int result = main_c(str, 0.0, &res);

    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_3) {
    double res = 0.0;
    char *str = "2/1+2+3+4*5*6^7-727mod728+((1000+500*2)*201)+sin(1)";
    int result = main_c(str, 0.0, &res);

    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_4) {
    double res = 0.0;
    char *str = "x+2/1+2+3+4*5*6^7-727";
    int result = main_c(str, 0.0, &res);

    ck_assert_int_eq(result, 0);
}
END_TEST

START_TEST(test_5) {
    double res = 0.0;
    char *str = "x+2/1+2+3+x*x";
    int result = main_c(str, 5.0, &res);

    ck_assert_int_eq(result, 0);
}
END_TEST

int main() {
    Suite *s1 = suite_create("SmartCalc: ");
    TCase *tc1_1 = tcase_create("SmartCalc: ");
    SRunner *sr = srunner_create(s1);
    int result;
    suite_add_tcase(s1, tc1_1);

    tcase_add_test(tc1_1, test_1);
    tcase_add_test(tc1_1, test_2);
    tcase_add_test(tc1_1, test_3);
    tcase_add_test(tc1_1, test_4);
    tcase_add_test(tc1_1, test_5);

    srunner_run_all(sr, CK_ENV);
    result = srunner_ntests_failed(sr);
    srunner_free(sr);
    return result == 0 ? 0 : 1;
}
