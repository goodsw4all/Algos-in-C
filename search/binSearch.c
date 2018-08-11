/*
 * =====================================================================================
 *
 *       Filename:  binSearch.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  08/10/18 02:51:27
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  codeart@gmail.com
 *   Organization:
 *
 * =====================================================================================
 */

#include <criterion/criterion.h>

int binarySearch(int *array, int n, int key)
{
    int start = 0;
    int end   = n-1;

    while (start <= end) {
        int mid = (start+end) / 2;
        if (array[mid] == key) {
            return mid;
        }

        if (array[mid] < key) {
            start = mid+1;
        } else {
            end = mid-1;
        }
    }

    return -1;
}

int binarySearchRecursive(int *array, int start, int end, int key)
{

    int mid = (start+end)/2;

    if (start>end) {
        return -1;
    }

    if (array[mid] == key)
        return mid;

    if (array[mid] < key) {
        return binarySearchRecursive(array, mid+1, end, key);
    } else {
        return binarySearchRecursive(array, start, mid-1, key);
    }
}

int binarySearchRotatedIndex(int *array, int n)
{
    int start = 0;
    int end   = n-1;

    while(start<=end) {
        // segment is sorted
        if (array[start] < array[end]) {
            return start;
        }

        int mid  = (start+end) / 2;
        int prev = (mid+n-1) % n;
        int next = (mid+1) %n;

        if (array[mid] < array[prev] && array[mid] > array[next]) {
            return mid;
        }

        if (array[mid] > array[end]) {
            start = mid+1;
        } else {
            end = mid-1;
        }

        // when break??
    }

    return -1;
}

int binarySearchRotated(int *array, int n, int key)
{
    int start = 0;
    int end   = n-1;

    while (start <= end) {
        int mid = (start + end) /2;

        if (array[mid] == key) {
            return mid;
        }

        // left is sorted
        if (array[start] < array[mid]) {
            if (key < array[mid] && key >= array[start]) {
                end = mid-1;
            } else {
                start = mid+1;
            }
        } else if (array[mid] < array[end]) {
            if (key > array[mid] && key <= array[end]) {
                start = mid+1;
            } else {
                end = mid-1;
            }
        }

    }

    return 0;
}

/* Test w/ criterion framework below */
void setup()
{

}

void teardown()
{

}

TestSuite(search, .init = setup, .fini = teardown);

int sorted[15] = { 2,  3,  4,  5, 15, 19, 26, 27, 36, 38, 44, 46, 47, 48, 50 };
int rotated_sorted[15] = { 46, 47, 48, 50, 2,  3,  4,  5, 15, 19, 26, 27, 36, 38, 44 };
int sorted_dup[15] = { 2,  3,  4, 15, 15, 15, 26, 27, 36, 38, 44, 46, 47, 48, 50 };

Test(binarySearch, UnitTest) {
    cr_expect_eq(binarySearch(sorted, 15, 5), 3, "");
}

Test(binarySearchRecursive, UnitTest) {
    cr_expect_eq(binarySearchRecursive(sorted, 0, 15-1, 5), 3, "");
}

Test(binarySearchRotatedIndex, UnitTest) {
    cr_expect_eq(binarySearchRotatedIndex(sorted, 15), 0, "");
    cr_expect_eq(binarySearchRotatedIndex(rotated_sorted, 15), 4, "");
}

Test(binarySearchRotated, UnitTest) {
    cr_expect_eq(binarySearchRotated(sorted, 15, 48), 13, "");
    cr_expect_eq(binarySearchRotated(rotated_sorted, 15, 48), 2, "");
}