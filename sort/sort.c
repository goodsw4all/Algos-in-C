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
#include <time.h>

#include <criterion/criterion.h>
#include <criterion/logging.h>

#define ARR_LEN(x) (sizeof(x)/sizeof(x[0]))

void swap(int *x, int *y)
{
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int sorted[10]    = { 2,  3,  4,  5, 15, 19, 26, 27, 48, 50 };
int unsorted[10]  = { 0 };

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
    srand((unsigned int) time(NULL));
    memcpy(array, sorted, n*sizeof(int));

    for (int i=0; i<n; i++) {
        int j = rand() % n;
        if (i != j) {
            swap(&array[i], &array[j]);
        }
    }
}

/*
 * Insertion Sort
 * efficient algorithm for sorting a small number of elements.
 * Insertion sort works the way many people sort a hand of playing cards.
 * We start with an empty left hand and the cards face down on the table.
 * We then remove one card at a time from the table and insert it
 * into the correct position in the left hand.
 * To find the correct position for a card,
 * we compare it with each of the cards already in the hand, from right to left,
 * At all times, the cards held in the left hand are sorted,
 * and these cards were originally the top cards of the pile on the table.
 */
void insertion(int *array, int n)
{
    for (int j=1; j<n; j++) {
        int key = array[j]; // 정렬하려고 하는 숫자
        int i = j - 1;
        while (i>=0 && array[i] > key) {
            array[i+1] = array[i];
            i--;
        }
        array[i+1] = key;

        char step[32];
        sprintf(step, "STEP%d", j);
        printIntArray(array, n, step);
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

Test(sort, insertion) {
    int len = ARR_LEN(unsorted);
    printIntArray(unsorted, len, "Before");
    insertion(unsorted, len);
    printIntArray(unsorted, len, "After");
    cr_expect_arr_eq(unsorted, sorted, len);
}
