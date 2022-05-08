#include <stdio.h>
#include <stdlib.h>

#include "../include/unit_test.h"

int main(int argc, const char  *argv[])
{
    int n = 0;
    SRunner *sr = NULL;
    sr = srunner_create(make_unit_suite());
    srunner_run_all(sr, CK_NORMAL);
    n = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (n == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

