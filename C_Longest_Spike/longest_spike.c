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

    int distinct = 0;    /* Count of distinct values */
    int twiceOrMore = 0; /* Count of values with freq >= 2 */
    int freq = 1;        /* Frequency counter */

    /* The maximum (last) value in the sorted array */
    int maxValue = A[N - 1];
    int freqMaxValue = 0;

    /* Walk through sorted A, tally distinct and freq >= 2 */
    for (int i = 1; i <= N; i++) {
        if (i < N && A[i] == A[i - 1]) {
            freq++;
        } else {
            /* End of a run of equal values */
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

    /* If the maximum value itself appears twice or more, we must
       subtract one from the “twiceOrMore” count when forming the
       descending part (because the peak only needs one copy). */
    int decExtras = twiceOrMore - (freqMaxValue >= 2 ? 1 : 0);

    /* Total spike length = (all distinct values in ascending)
                         + (one copy of peak + all other duplicates)
                         = distinct + decExtras */
    return distinct + decExtras;
}

int main(void) {
    /* Example tests */
    int A1[] = {1, 2};
    printf("Expected 2, got %d\n", solution(A1, 2));

    int A2[] = {2, 5, 3, 2, 4, 1};
    printf("Expected 6, got %d\n", solution(A2, 6));

    int A3[] = {2, 3, 3, 2, 2, 2, 1};
    printf("Expected 4, got %d\n", solution(A3, 7));

    return 0;
}
