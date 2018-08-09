# Sorting Algorithms

## Build & Run
### Build
$ make
### Run
```
$ ./sort --verbose
[----] Criterion v2.3.1
[====] Running 2 tests from sort:
[RUN ] sort::Bubble
[----] setup() : Shuffle the Array
[RUN ] sort::Insertion
 Before   = { 15, 26, 50,  3, 48,  5, 27,  2, 19,  4 }
 After    = {  2,  3,  4,  5, 15, 19, 26, 27, 48, 50 }
[----] setup() : Shuffle the Array
[PASS] sort::Bubble: (0.00s)
 Before   = { 15, 50, 26,  3,  5, 27,  4, 19,  2, 48 }
 After    = {  2,  3,  4,  5, 15, 19, 26, 27, 48, 50 }
[----] teardown()
[PASS] sort::Insertion: (0.00s)
[----] teardown()
[====] Synthesis: Tested: 2 | Passing: 2 | Failing: 0 | Crashing: 0 
```

## Insertion Sort
### Code
```C++
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
```

### Complexity
* Time  : Best O(n) / Average O(n^2) / Worst O(n^2)
* Space : O(1)


## Bubble Sort
### Code
```C++
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
```

### Complexity
* Time  : Best O(n) / Average O(n^2) / Worst O(n^2)
* Space : O(1)

## Selection Sort
### Code
```C++
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
```

### Complexity
* Time  : Best O(n^2) / Average O(n^2) / Worst O(n^2)
* Space : O(1)

## Merge Sort
### Code
```C++
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
```
```C++
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
```

### Complexity
* Time  : Best O(n log(n)) / Average O(n log(n)) / Worst O(n log(n))
* Space : O(n)

## Quick Sort
### Code

```C++
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
```

```C++
void quickSort(int *array, int startIdx, int endIdx)
{
    if (startIdx < endIdx) {
        int pi = partition(array, startIdx, endIdx);
        quickSort(array, startIdx, pi-1);
        quickSort(array, pi+1, endIdx);
    }
}
```

### Complexity
* Time  : Best O(n log(n)) / Average O(n log(n)) / Worst O(n^2)
* Space : O(log(n))
