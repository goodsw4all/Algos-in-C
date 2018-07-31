/*
 * =====================================================================================
 *
 *       Filename:  sort.c
 *
 *    Description:  various sorting algorithms in C w/ Unit Test
 *
 *        Version:  0.0.1
 *        Created:  07/29/2018 00:15:28
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  codeart@gmail.com
 *   Organization:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <sys/time.h>

#include <criterion/criterion.h>
#include <criterion/logging.h>

#define ARR_LEN(x) (sizeof(x)/sizeof(x[0]))

int sorted[10]    = { 2,  3,  4,  5, 15, 19, 26, 27, 48, 50 };
int unsorted[10]  = { 0 };

void swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void printIntArray(int *array, int n, const char *name)
{
    printf(" %-8s = { ", name);
    for(int i=0; i<n; i++)
    {
        printf("%2d", array[i]);
        if(i != n-1)
            printf(", ");
    }
    printf(" }\n");
}

void shuffleArray(int *array, int n)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    srand((unsigned int) tv.tv_usec);

    memcpy(array, sorted, n*sizeof(int));

    for (int i=0; i<n; i++) {
        int j = rand() % n;
        if (i != j) {
            swap(&array[i], &array[j]);
        }
    }
}

void insertion(int *array, int n)
{
    for (int j=1; j<n; j++) {
        int key = array[j];
        int i = j - 1;
        while (i>=0 && array[i] > key) {
            array[i+1] = array[i];
            i--;
        }
        array[i+1] = key;
    }
}

void bubble(int *array, int n)
{
    for (int i=0; i<n-1; i++) {
        for (int j=0; j<n-i-1; j++) {
            if (array[j] > array[j+1]) {
                swap(&array[j], &array[j+1]);
            }
        }
    }
}

void selection(int *array, int n)
{
    for (int i=0; i<n-1; i++) {
        int minIdx = i;
        for (int j=i+1; j<n; j++) {
            if (array[minIdx] > array[j]) {
                minIdx = j;
            }
        }
        swap(&array[i], &array[minIdx]);
    }
}

/* Test w/ criterion framework below */
void setup(void)
{
    cr_log_info("%s() : Shuffle the Array\n", __FUNCTION__);

    int len = ARR_LEN(unsorted);
    shuffleArray(unsorted, len);

}

void teardown(void)
{
    cr_log_info("%s()\n", __FUNCTION__);
    memset(unsorted, 0, sizeof(int) * ARR_LEN(unsorted));

}

TestSuite(sort, .init = setup, .fini = teardown);

Test(sort, Insertion, .disabled = true) {
    int len = ARR_LEN(unsorted);
    printIntArray(unsorted, len, "Before");
    insertion(unsorted, len);
    printIntArray(unsorted, len, "After");
    cr_expect_arr_eq(unsorted, sorted, len);
}

Test(sort, Bubble, .disabled = true) {
    int len = ARR_LEN(unsorted);
    printIntArray(unsorted, len, "Before");
    bubble(unsorted, len);
    printIntArray(unsorted, len, "After");
    cr_expect_arr_eq(unsorted, sorted, len);
}

Test(sort, Selection, .disabled = false) {
    int len = ARR_LEN(unsorted);
    printIntArray(unsorted, len, "Before");
    selection(unsorted, len);
    printIntArray(unsorted, len, "After");
    cr_expect_arr_eq(unsorted, sorted, len);
}