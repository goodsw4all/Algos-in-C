#include <criterion/criterion.h>

/* Test w/ criterion framework below */
void setup(void)
{
    cr_log_info("%s()\n", __FUNCTION__);

}

void teardown(void)
{
    cr_log_info("%s()\n", __FUNCTION__);

}

TestSuite(SuiteName, .init = setup, .fini = teardown);
Test(SuiteName, TestName, .disabled = false) {
    //cr_expect_arr_eq(unsorted, sorted, len);
}
