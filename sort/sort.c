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


#define ARR_LEN(x) (sizeof(x)/sizeof(x[0]))

int sorted[]    = { 2,  3,  4,  5, 15, 19, 26, 27, 48 };
int unsorted[9]  = { 0 };

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

void insertionSort(int *array, int n)
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

void bubbleSort(int *array, int n)
{
    for (int i=0; i<n-1; i++) {
        for (int j=0; j<n-i-1; j++) {
            if (array[j] > array[j+1]) {
                swap(&array[j], &array[j+1]);
            }
        }
    }
}

void selectionSort(int *array, int n)
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

void merge(int leftLen, int rightLen, int *array)
{
    int len = leftLen + rightLen;
    int temp[len];
    int leftIdx = 0, rightIdx = 0, mergeIdx = 0;

    memcpy(temp, array, sizeof(int) * len);

    int *left = temp;
    int *right = temp + leftLen;

    while (mergeIdx < len) {

        if (leftIdx >= leftLen) {
            array[mergeIdx] = right[rightIdx];
            mergeIdx++;
            rightIdx++;
            continue;
        }

        if (rightIdx >= rightLen) {
            array[mergeIdx] = left[leftIdx];
            mergeIdx++;
            leftIdx++;
            continue;
        }

        if (left[leftIdx] <= right[rightIdx]) {
            array[mergeIdx] = left[leftIdx];
            mergeIdx++;
            leftIdx++;
        } else {
            array[mergeIdx] = right[rightIdx];
            mergeIdx++;
            rightIdx++;
        }

    }
}

void mergeSort(int *array, int n)
{
    if (n<2)
        return;

    int mid = n/2;
    int *left = array;
    int *right = array + mid;

    mergeSort(left, mid);
    mergeSort(right, n-mid);
    merge(mid, n-mid, array);
}

int partition(int *array, int startIdx, int endIdx)
{
    int pivot = array[endIdx];
    int pi = startIdx;

    for (int i=startIdx; i<endIdx; i++) {
        if (array[i] < pivot) {
            swap(&array[i], &array[pi]);
            pi++;
        }
    }

    swap(&array[endIdx], &array[pi]);
    return pi;
}

void quickSort(int *array, int startIdx, int endIdx)
{
    if (startIdx < endIdx) {
        int pi = partition(array, startIdx, endIdx);
        quickSort(array, startIdx, pi-1);
        quickSort(array, pi+1, endIdx);
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
    insertionSort(unsorted, len);
    printIntArray(unsorted, len, "After");
    cr_expect_arr_eq(unsorted, sorted, len);
}

Test(sort, Bubble, .disabled = true) {
    int len = ARR_LEN(unsorted);
    printIntArray(unsorted, len, "Before");
    bubbleSort(unsorted, len);
    printIntArray(unsorted, len, "After");
    cr_expect_arr_eq(unsorted, sorted, len);
}

Test(sort, Selection, .disabled = true) {
    int len = ARR_LEN(unsorted);
    printIntArray(unsorted, len, "Before");
    selectionSort(unsorted, len);
    printIntArray(unsorted, len, "After");
    cr_expect_arr_eq(unsorted, sorted, len);
}

Test(sort, Merge, .disabled = true) {
    int len = ARR_LEN(unsorted);
    printIntArray(unsorted, len, "Before");
    mergeSort(unsorted, len);
    printIntArray(unsorted, len, "After");
    cr_expect_arr_eq(unsorted, sorted, len);
}

Test(sort, Quick, .disabled = false) {
    int len = ARR_LEN(unsorted);
    printIntArray(unsorted, len, "Before");
    quickSort(unsorted, 0, len-1);
    printIntArray(unsorted, len, "After");
    cr_expect_arr_eq(unsorted, sorted, len);
}