/*
 * =====================================================================================
 *
 *       Filename:  factorial.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  08/13/18 17:05:07
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  codeart@gmail.com,
 *   Organization:
 *
 * =====================================================================================
 */

#include <criterion/criterion.h>

/*
 * n! = { n x (n-1)! if n>0, 1 if n = 0 }
 */
int factorial(int n)
{
    cr_log_info("Factorial(%d) called\n", n);
    if (n == 0)
        return 1;

    return n * factorial(n-1);
}

/*  Test w/ criterion framework below */
TestSuite(Factorial, .description = "Factorial recursive function test");

Test(recursion, factorial) {
    cr_log_info("Base Case Test");
    cr_expect_eq(factorial(0), 1, "if n == 0");
    cr_log_info("factorial(5) starts, check the calling sequence");
    cr_expect_eq(factorial(5), 120, "factorial(5) = 120");
}
