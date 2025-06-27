# 1 Bug fixing Bisection

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
2. Open the folder containing `bisection_fix.c` in VSCode.
3. In the integrated terminal, compile:
   ```bash
   gcc bisection_fix.c -o bisection_fix
   ```
4. Run the executable:
   ```bash
   bisection_fix.exe
   ```

## Expected Output

```
Element 5 found at index 2
```

## Complexity

- **Time Complexity:** O(log N)  
- **Space Complexity:** O(1)

