#include "run_tests.h"




 int main()
 {  
    int number_failed;
    Suite* sui;
    SRunner* suite_runner;


    sui = make_strlen_suite();
    suite_runner = srunner_create(sui);

    srunner_run_all(suite_runner, CK_NORMAL);

    number_failed = srunner_ntests_failed(suite_runner);
    srunner_free(suite_runner);


    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
 }