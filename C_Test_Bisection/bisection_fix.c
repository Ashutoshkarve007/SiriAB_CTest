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
        printf("Element %d found at index %d\n", X, index);
    else
        printf("Element %d not found\n", X);

    return 0;
}
