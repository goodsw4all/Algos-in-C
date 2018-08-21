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

/*
 *   Insertion Sort
 *   카드놀이를 생각해보자 !
 *   뒤짚어 놓은 카드 뭉치가 있고, 한번에 한 장씩 꺼내어 뒤집어 바닥에 내려 놓는다.
 *   단, 숫자가 작은 카드부터 놓기 위해 (오름차순) 이미 뒤집어 놓은 카드 중에
 *   알맞은 자리를 찾아 넣는다. -> 이 부분이 insertion 을 의미
 *
 *   Code
 *   1. 첫번째로 꺼낸 카드는 비교할 카드가 없으므로 제일 첫번째에 놓으면 된다
 *      따라서, insertion 할 자리를 찾고 insertion 하는 것은 두번째 카드부터 시작
 *   2. j 초기값 1은 두번째로 뒤집은 카드를 의미한다.
 *   3. 새로 꺼낸 카드를 insertion 할 자리를 찾기 위해 바로 전 위치의 카드(가장 오른쪽에 있는 카드)부터
 *      비교하고 새로 꺼낸 카드보다 크면 원래 있던 자리에서 한칸 오른쪽으로 이동.
 *      (이렇게 되면, 원래 있던 자리는 값은 남아 있지만, 비어 있는 셈)
 *   4. 제일 왼쪽에 있는 카드까지 비교를 하면서 3을 반복한다.
 *   5. 이렇게 하면 뒤집은 카드들은 계속 정렬 상태를 유지할 수 있다.
 *
 *   Time Complexity          Space Complexity
 *   Best   Average   Worst   Worst
 *   Ω(n)	Θ(n^2)	  O(n^2)  O(1)
 *
 */
void insertionSort(int *array, int n)
{
    for (int j=1; j<n; j++) {
        int newNum = array[j];
        int i = j - 1;             // 정렬된 카드 중에 가장 마지막(오른쪽) 위치
        while (i>=0 && array[i] > newNum) {
            array[i+1] = array[i]; // 삽입할 위치 후보 i 를 찾아 원래 있던 데이터를 오른쪽으로 옮김
            i--;
        }
        array[i+1] = newNum;       // 삽입할 위치에 새로운 요소를 삽입
    }
}

/*
 *   Bubble Sort
 *   wikipedia : named for the way smaller or larger elements "bubble" to the top of the list.
 *   오름차순이라 가정하면, 상대적으로 더 큰 요소들이 거품방울처럼 Top 으로 떠오르는 모양이라는데... 글쎄... 상상이 안됨
 *   가장 첫 요소부터 바로 오른쪽 이웃과 비교하여 외쪽이 더 크면 오른쪽과 SWAP,
 *   이것을 반복하면 최대값이 가장 오른쪽(TOP)으로 이동, 그렇게 되면 배열의 가장 오른쪽부터 정렬이 되어가는 모습
 *
 *   Code
 *   1. 가장 왼쪽의 값과 바로 오른쪽의 값을 비교하면, 왼쪽이 크면 SWAP
 *   2. 반복하다면 보면 가장 오른쪽에는 최대값이 있게 됨
 *   3. 첫번째 요소부터 최대값이 있는 위치 전까지를 범위로 다음의 최대값을 찾아 오른쪽으로 이동(1번 반복)
 *   4. 범위는 n-i-1 에서 0으로 좁혀짐에 따라 범위의 바깥 오른쪽 부분은 정렬이 된 상태가 된다.
 *
 *   Time Complexity          Space Complexity
 *   Best  Average   Worst    Worst
 *   Ω(n)   Θ(n^2)	 O(n^2)   O(1)
 */
void bubbleSort(int *array, int n)
{
    for (int i=0; i<n-1; i++) {
        for (int j=0; j<n-i-1; j++) {
            if (array[j] > array[j+1]) {
                swap(&array[j], &array[j+1]); // 왼쪽이 오른쪽보다 크다면 SWAP
            }
        }
    }
}

/*
 *   Selection Sort
 *   최소값을 찾아 배열의 첫 요소로 옮기면서 왼쪽 부터 정렬한다.
 *   그래서 범위는 Bubble Sort 와 반대로 시작위치가 이동하고 마지막 위치는 고정된 모습이다
 *
 *   Code
 *   1. 첫번째 요소를 일단 최소값이라 가정하고 최소값 index에 저장해 둔다.
 *   2. 오른쪽에 있는 모든 요소와 비교하여 더 작은 값이 있으면 최소값 index 를 그 값으로 바꾸어 저장한다.
 *   3. 비교 과정이 끝나면 최소값과 배열의 첫번째 요소와 SWAP
 *   4. 범위를 오른쪽으로 좁혀가면서 1/2/3 반복
 *
 *   Time Complexity          Space Complexity
 *   Best   Average   Worst   Worst
 *   Ω(n^2)	Θ(n^2)	  O(n^2)  O(1)
 */
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
/*
 *   Merge
 *   두 개의 정렬된 배열을 정렬된 순서에 맞추어 병합한다.
 *
 *   Code
 *   1. 배열의 복사본을 만든다.
 *   2. 왼쪽과 오른쪽으로 나누어 병합 시작
 *   3. 한쪽이 다 소진되면, 남은 쪽으로 채운다.
 *
 */
void merge(int leftLen, int rightLen, int *array)
{
    int len = leftLen + rightLen;
    int temp[len];
    int leftIdx = 0, rightIdx = 0, mergeIdx = 0;

    memcpy(temp, array, sizeof(int) * len);

    int *left = temp;
    int *right = temp + leftLen;

    while (mergeIdx < len) {

        if (leftIdx >= leftLen) { // left 를 다 소진
            array[mergeIdx] = right[rightIdx];
            mergeIdx++;
            rightIdx++;
            continue;
        }

        if (rightIdx >= rightLen) { // right 를 다 소진
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

/*
 *   Merge Sort
 *   재귀적인 접근으로, 정렬이 되어 있는 두 배열을 각 요소의 순서의 크기에 따라 합치면
 *   전체적으로 정렬이 된다.
 *   하나가 남을 때까지 배열을 나누고, 다시 merge 하면 정렬이 완성된다
 *
 *   Code
 *   중간값을 기준으로 왼쪽과 오른쪽으로 나누어 재귀호출한다.
 *   1개가 되면 return 하고 merge 를 시작
 *   merge 가 진행됨에 따라 왼쪽, 오른쪽 배열이 정렬이 된다
 *
 *   Time Complexity                         Space Complexity
 *   Best          Average      Worst        Worst
 *   Ω(n log(n))   Θ(n log(n))  Θ(n log(n))  O(log(n))
 */
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

/*
 *   partition
 *   어느 값을 기준으로 (여기서는 마지막값) 기준값보다 작은 요소를 왼쪽으로, 큰 요소를 오른쪽으로
 *
 *   code
 *   1. pivot 을 마지막 요소로 정한다.
 *   2. partition index 를 start 로 초기화 (pi의 위치를 파티셔닝하면서 찾을 것임)
 *   3. pivot 보다 큰 값을 만나면, pi 위치 에 있는 값과 swap 해주고 pi++
 *   4. pi는 언제나 pivot 보다 큰 값의 첫 index 가 된다.
 *
 */
int partition(int *array, int startIdx, int endIdx)
{
    int pivot = array[endIdx]; // 마지막 값을 Pivot 으로 (여러가지 방법이 있을 수 있음)
    int pi = startIdx;

    for (int i=startIdx; i<endIdx; i++) { // 마지막 요소가 Pivot 이기 때문에 그 전까지 비교
        if (array[i] < pivot) {
            swap(&array[i], &array[pi]); // pi는 pivot 보다 큰 첫번째 index 를 가르킴
            pi++;
        }
    }

    swap(&array[endIdx], &array[pi]); // pivot은 제일 마지막에 있으니 Parition Index와 SWAP
    return pi;
}

int partition2(int *array, int startIdx, int endIdx)
{
    int pivot = array[(startIdx+endIdx)/2];
    while (startIdx <= endIdx) {
        while (array[startIdx] < pivot) startIdx++;
        while (array[endIdx] >  pivot) endIdx--;

        if (startIdx <= endIdx) {
            swap(&array[startIdx], &array[endIdx]);
            startIdx++, endIdx--;
        }
    }

    return startIdx;
}

/*
 *   Quick Sort
 *   재귀적인 접근으로 "어느 한 기준값을 기준으로 왼쪽과 오른쪽을 정렬하면 전체적으로 정렬이 된다."
 *   Pivot(기준값) 기준으로 왼쪽 파티션과 오른쪽 파티션으로 나눈다.
 *   왼쪽 파티션은 기준값보다 작은 값들을 모으고 오른쪽은 기준값보다 큰 값들을 모은다.
 *   재귀적인 방식으로 하나가 될 때까지 파티션을 나눈다.
 *   낱개가 되면 정렬이 된 상태가 되고 리턴 하면 상위 재귀함수 또한 정렬이 되게 된다.
 *   Pivot 은 중간값에 가까울 수록 좋다.
 *
 *   Code
 *   1. start index 와 end index 를 범위로 해서 파티셔닝 한다.
 *   2. 나눠진 파티션들(왼쪽, 오른쪽)에 대해 재귀호출한다. 하나가 될 때까지~
 *
 *   Time Complexity                      Space Complexity
 *   Best          Average      Worst     Worst
 *   Ω(n log(n))   Θ(n log(n))  O(n^2)    O(log(n))
 */
void quickSort(int *array, int startIdx, int endIdx)
{
    if (startIdx < endIdx) {
        int pi = partition(array, startIdx, endIdx);
        quickSort(array, startIdx, pi-1);  // smaller
        quickSort(array, pi+1, endIdx);    // bigger
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