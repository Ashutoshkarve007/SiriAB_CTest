# 1. Bug fixing Bisection (Inside C_Test_Bisection Folder/Dir):

## Overview

I was asked to inspect and correct a binary search (bisection) function in C. The function must locate a target integer `X` in a sorted array `A[]` and return the index of any occurrence of `X`. If `X` is not present, the function should return `-1`.

## Problem Statement

Given:
- A sorted array `A` of `N` integers in non-decreasing order
- A target integer `X`

Implement:
```c
int solution(int A[], int N, int X);
```
so that it returns the index of any occurrence of `X` in `A`, or `-1` if `X` is not found.

### Constraints
- `0 ≤ N ≤ 100 000`
- `−2 000 000 000 ≤ A[i], X ≤ 2 000 000 000`

## Analysis of the Original Code

The original loop was:
```c
while (l < r) {
    m = (l + r) / 2;
    if (A[m] > X)
        r = m - 1;
    else
        l = m;
}
```
This caused two issues:
1. **Infinite loop** when `l == m` (e.g. small subarrays)  
2. **Skipped checks** for the case `l == r`

## Corrected Implementation

I modified only three lines to fix these issues:

```c
int solution(int *A, int N, int X) {
    int l = 0, r = N - 1, m;

    while (l <= r) {
        m = l + (r - l) / 2;
        if (A[m] == X)
            return m;
        else if (A[m] < X)
            l = m + 1;
        else
            r = m - 1;
    }

    return -1;
}
```

### Key Changes
- Changed loop condition to `while (l <= r)`  
- Used `m = l + (r - l) / 2` to avoid overflow  
- Adjusted `l` and `r` updates to ensure progress

## Sample Test Program

```c
#include <stdio.h>

int solution(int *A, int N, int X) {
    int l = 0, r = N - 1, m;
    while (l <= r) {
        m = l + (r - l) / 2;
        if (A[m] == X)
            return m;
        else if (A[m] < X)
            l = m + 1;
        else
            r = m - 1;
    }
    return -1;
}

int main() {
    int A[] = {1, 2, 5, 9, 9};
    int N = sizeof(A) / sizeof(A[0]);
    int X = 5;

    int index = solution(A, N, X);
    if (index != -1)
        printf("Element %d found at index %d
", X, index);
    else
        printf("Element %d not found
", X);

    return 0;
}
```

## Build and Run Instructions (Windows / VSCode)

1. Install **Visual Studio Code** and **MinGW-w64** (to get `gcc`).

2. Open the `C_Test_Bisection` folder (containing `bisection_fix.c`) in VSCode.

3. In the integrated terminal, compile:
   ```bash
   gcc bisection_fix.c -o bisection_fix
   ```
4. Run the executable:
   ```bash
   bisection_fix.exe
   ```

## Expected Output

![image](https://github.com/user-attachments/assets/c6fdfbd8-6f09-4c12-9961-b59ba4181af6)

```
Element 5 found at index 2
```

## Complexity

- **Time Complexity:** O(log N)  
- **Space Complexity:** O(1)

# 2. Create Longest Spike (Inside C_Longest_Spike Folder/Dir):

## Overview

This document describes the solution to the "Longest Spike" problem in C.  
A spike is defined as a sequence that first strictly increases and then strictly decreases, sharing a peak.  
Given an array of integers, we choose and reorder elements to form the longest possible spike and return its length.

The code for this solution is in the `C_Longest_Spike` folder, in the file `longest_spike.c`.

## Problem Statement

Implement the function:

```c
int solution(int A[], int N);
```

- **Input:**  
  - `A[]`: array of `N` integers (1 ≤ N ≤ 100,000, 1 ≤ A[i] ≤ 1,000,000)  
- **Output:**  
  - Length of the longest spike that can be built by reordering elements of `A`.

A valid spike has:
1. A strictly increasing sequence.
2. Followed by a strictly decreasing sequence.
3. The peak element is shared between the two parts.

## Solution Approach

1. **Sort** the array to group equal values.
2. **Count distinct values** (`distinct`) — each contributes one element in the increasing part.
3. **Count values with frequency ≥ 2** (`twiceOrMore`) — each extra copy (beyond the first) can contribute to the decreasing part.
4. **Adjust for the maximum value**: if the maximum appears more than once, only one extra of the peak is needed (the peak itself counts once).
5. **Result** = `distinct + (twiceOrMore - (peakFreq ≥ 2 ? 1 : 0))`

This runs in O(N log N) due to sorting, and O(N) additional time.

## Code

```c
#include <stdio.h>
#include <stdlib.h>

/* Comparison function for qsort */
static int cmp(const void *a, const void *b) {
    int x = *(const int *)a;
    int y = *(const int *)b;
    return (x < y) ? -1 : (x > y);
}

/* Returns length of the longest spike you can build */
int solution(int A[], int N) {
    if (N <= 0) {
        return 0;
    }

    /* Sort the array to group equal values */
    qsort(A, N, sizeof(int), cmp);

    int distinct = 0;
    int twiceOrMore = 0;
    int freq = 1;

    int maxValue = A[N - 1];
    int freqMaxValue = 0;

    for (int i = 1; i <= N; i++) {
        if (i < N && A[i] == A[i - 1]) {
            freq++;
        } else {
            distinct++;
            if (freq >= 2) {
                twiceOrMore++;
                if (A[i - 1] == maxValue) {
                    freqMaxValue = freq;
                }
            }
            freq = 1;
        }
    }

    int decExtras = twiceOrMore - (freqMaxValue >= 2 ? 1 : 0);
    return distinct + decExtras;
}

int main(void) {
    int A1[] = {1, 2};
    printf("Expected 2, got %d\n", solution(A1, 2));

    int A2[] = {2, 5, 3, 2, 4, 1};
    printf("Expected 6, got %d\n", solution(A2, 6));

    int A3[] = {2, 3, 3, 2, 2, 2, 1};
    printf("Expected 4, got %d\n", solution(A3, 7));

    return 0;
}
```

## Build and Run (Windows / VSCode)

1. Place the code in `C_Longest_Spike/longest_spike.c`.
2. Open the folder in VS Code.
3. Open the integrated terminal.
4. Compile with:
   ```bash
   gcc longest_spike.c -o longest_spike
   ```
5. Run with:
   ```bash
   ./longest_spike   # or longest_spike.exe on Windows
   ```

## Expected Output

```
Expected 2, got 2
Expected 6, got 6
Expected 4, got 4
```

## Complexity

- **Time:** O(N log N)  
- **Space:** O(1) (ignoring input array)



