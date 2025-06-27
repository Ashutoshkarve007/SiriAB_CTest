#include <stdio.h>
#include <string.h>

/*
 * Compute how many distinct numbers divisible by 3 can be obtained
 * from S by changing at most one digit.
 */
int solution(char *S) {
    int N = strlen(S);
    int sum = 0;
    for (int i = 0; i < N; i++) {
        sum += S[i] - '0';
    }
    int orig_mod = sum % 3;

    int count = 0;
    // Include original number if already divisible by 3
    if (orig_mod == 0) {
        count++;
    }

    // Try changing each position to each other digit 0..9
    for (int i = 0; i < N; i++) {
        int d = S[i] - '0';
        // New sum without the old digit:
        int base = sum - d;
        for (int nd = 0; nd <= 9; nd++) {
            if (nd == d) continue;
            if ((base + nd) % 3 == 0) {
                count++;
            }
        }
    }

    return count;
}

int main(void) {
    // Example 1
    char S1[] = "23";
    printf("Expected 7, got %d\n", solution(S1));

    // Example 2
    char S2[] = "0081";
    printf("Expected 11, got %d\n", solution(S2));

    // Example 3
    char S3[] = "022";
    printf("Expected 9, got %d\n", solution(S3));

    return 0;
}
