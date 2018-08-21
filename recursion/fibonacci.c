#include <criterion/criterion.h>

/*
 * fibonacci f(n) = { f(n-1) + f(n-2) if n > 1, n if n = 0, 1 }
 */

int fiboRecursive(int n)
{
    int ret = 0;
    if (n == 0 || n == 1) {
        ret = n;
        cr_log_info("f(%d) = %d\n", n, ret);
        return ret;
    }

    ret = fiboRecursive(n-1) + fiboRecursive(n-2);
    cr_log_info("f(%d) = fiboRecursive(%d) + fiboRecursive(%d) = %d\n", n, n-1, n-2, ret);
    return ret;
}

int fiboIterative(int n) {
    int ret = 0;
    int n_1 = 1, n_2 = 0;

    if (n == 0 || n == 1)
        return n;

    for (int i=2; i<=n; i++) {
        ret = n_1 + n_2;
        n_2 = n_1;
        n_1 = ret;
    }

    cr_log_info("f(%d) = fiboIterative(%d) + fiboIterative(%d) = %d\n", n, n-1, n-2, ret);
    return ret;
}

static int memo[10]; // 반복되는 계산이 발생하는 경우에 메모리를 사용해서 저장해서 사용 trade off
int fiboMemoization(int n)
{
    int ret = 0;
    if (n == 0 || n == 1)
        return n;

    if (memo[n])
        return memo[n];

    ret = fiboMemoization(n-1) + fiboMemoization(n-2);
    memo[n] = ret;

    return ret;

}

/* Test w/ criterion framework below */
TestSuite(Fibonacci, .description="Fibonacci Recursive");

Test(Fibonacci, finonacci) {
    int a = fiboRecursive(3), b = fiboIterative(3);
    cr_expect_eq(fiboIterative(0), fiboRecursive(0), "");
    cr_expect_eq(fiboIterative(1), fiboRecursive(1), "");
    cr_expect_eq(fiboIterative(5), fiboRecursive(5), "");
    cr_expect_eq(fiboIterative(10), fiboRecursive(10), "");

    printf("fibonacci Memoization 10 -> %d\n", fiboMemoization(10));
}