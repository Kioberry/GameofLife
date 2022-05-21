#include <stdio.h>
#include <stdlib.h>

#include "../include/unit_test.h"

int main(int argc, const char  *argv[])
{
    int n = 0, m=0;
    SRunner *sr = NULL;
    SRunner *sr2 = NULL;
    sr = srunner_create(make_unit_suite1());
    sr2 = srunner_create(make_unit_suite2());
    srunner_run_all(sr, CK_NORMAL);
    printf("\n");
    srunner_run_all(sr2, CK_NORMAL);
    n = srunner_ntests_failed(sr);
    m = srunner_ntests_failed(sr2);
    srunner_free(sr);
    srunner_free(sr2);
    return (n == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}

