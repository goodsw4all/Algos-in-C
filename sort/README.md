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
```
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
```

### Complexity
* Time  : Best O(n) / Average O(n^2) / Worst O(n^2)
* Space : O(1)


## Bubble Sort
### Code
```
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
```

### Complexity
* Time  : Best O(n) / Average O(n^2) / Worst O(n^2)
* Space : O(1)
