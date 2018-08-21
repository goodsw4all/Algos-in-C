#include <criterion/criterion.h>

/*
 * n! = { n x (n-1)! if n>0, 1 if n = 0 }
 */
int factorial(int n)
{
    cr_log_info("Factorial(%d) called\n", n);
    if (n == 0) //Important : base condition
        return 1;

    return n * factorial(n-1);
}

/*  Test w/ criterion framework below */
TestSuite(Factorial, .description = "Factorial recursive function test");

Test(recursion, Factorial) {
    cr_log_info("Base Case Test");
    cr_expect_eq(factorial(0), 1, "if n == 0");
    cr_log_info("factorial(5) starts, check the calling sequence");
    cr_expect_eq(factorial(5), 120, "factorial(5) = 120");
}
