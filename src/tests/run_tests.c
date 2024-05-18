#include "run_tests.h"

#include <stdlib.h>

#include <check.h>



START_TEST(first_test) {

s21_size_t result = s21_strlen("");
ck_assert_int_eq(result, 0);

}
END_TEST

START_TEST(second_test) {

s21_size_t result = s21_strlen("posh");
ck_assert_int_eq(result, 4);

}
END_TEST


Suite* strlen_suite() {
    Suite* sui = suite_create("strlen");
    TCase *tc_core;

    tc_core = tcase_create("Core");
    tcase_add_test(tc_core, first_test);
    tcase_add_test(tc_core, second_test);

    suite_add_tcase(sui, tc_core);
    return sui;
}





 int main()
 {  
    int number_failed;
    Suite *sui;
    SRunner *suite_runner;


    sui = strlen_suite();
    suite_runner = srunner_create(sui);

    srunner_run_all(suite_runner, CK_NORMAL);

    number_failed = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);


    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
 }