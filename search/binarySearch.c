#include <criterion/criterion.h>
/*
 *   Binary Search
 *   Linear Search O(N) 을 O(logN)으로 개선하는 알고리즘
 *   전제 조건 : 배열 내 요소들이 정렬이 되어 있어야 한다.
 *   중간값과 비교하고 같지 않으면 n/2 로 배열을 줄여 중간값 비교 반복
 *   1개의 요소가 남을 때까지 반복
 *
 *   Code
 *   1. start와 end 가 같아질 때까지 loop
 *   2. 중간값(mid) 계산 후 찾으려는 key 비교 같으면 return
 *   3. 중간값이 key 보다 작으면 중간값의 오른쪽을 새로운 범위의 배열로
 *   4. 반대인 경우는 왼쪽을 새로운 범위로 (n/2)
 *
 *   Time Complexity
 *   O(log n)
 */
int binarySearch(int *array, int n, int key)
{
    int start = 0;
    int end   = n-1;

    while (start <= end) {
        int mid = (start+end) / 2;
        if (array[mid] == key)
            return mid;

        if (array[mid] < key)
            start = mid+1;
        else
            end = mid-1;
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
        int next = (mid+1) % n;

        // instead of if (array[mid] == key)
        if (array[prev] > array[mid] && array[mid] > array[next]) {
            return mid;
        }

        if (array[mid] > array[end]) {
            start = mid+1;
        } else {
            end = mid-1;
        }
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

TestSuite(BinarySearch, .init = setup, .fini = teardown);

int sorted[15]         = { 2,  3,  4,  5,  15, 19, 26, 27, 36, 38, 44, 46, 47, 48, 50 };
int rotated_sorted[15] = { 46, 47, 48, 50, 2,  3,  4,  5,  15, 19, 26, 27, 36, 38, 44 };
int sorted_dup[15]     = { 2,  3,  4,  15, 15, 15, 26, 27, 36, 38, 44, 46, 47, 48, 50 };

Test(BinarySearch, Normal) {
    cr_expect_eq(binarySearch(sorted, 15, 5), 3, "");
}

Test(BinarySearch, Recursive) {
    cr_expect_eq(binarySearchRecursive(sorted, 0, 15-1, 5), 3, "");
}

Test(BinarySearch, RotatedIndex) {
    cr_expect_eq(binarySearchRotatedIndex(sorted, 15), 0, "");
    cr_expect_eq(binarySearchRotatedIndex(rotated_sorted, 15), 4, "");
}

Test(BinarySearch, RotatedSearch) {
    cr_expect_eq(binarySearchRotated(sorted, 15, 48), 13, "");
    cr_expect_eq(binarySearchRotated(rotated_sorted, 15, 48), 2, "");
}