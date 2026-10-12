
#include <stdio.h>
#include <string.h>

#define MAX 100

int main() {
    int n, W, i, w;
    int weight[MAX], value[MAX];
    int dp[MAX + 1][MAX + 1];
    int selected[MAX];

    printf("Enter number of items and truck capacity: ");
    scanf("%d %d", &n, &W);

    if (n < 1 || n > MAX || W < 0 || W > MAX) {
        printf("Invalid input limits.\n");
        return 0;
    }

    printf("Enter weight and utility value of each item:\n");
    for (i = 0; i < n; i++) {
        scanf("%d %d", &weight[i], &value[i]);

        if (weight[i] < 0 || value[i] < 0) {
            printf("Weight and utility must be non-negative.\n");
            return 0;
        }
    }

    memset(dp, 0, sizeof(dp));
    memset(selected, 0, sizeof(selected));

    /* Build the DP table */
    for (i = 1; i <= n; i++) {
        for (w = 0; w <= W; w++) {
            if (weight[i - 1] <= w) {
                int include = value[i - 1] +
                              dp[i - 1][w - weight[i - 1]];
                int exclude = dp[i - 1][w];

                dp[i][w] = (include > exclude) ? include : exclude;
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    printf("\nMaximum utility: %d\n", dp[n][W]);

    /* Trace back to find selected items */
    w = W;
    printf("Selected items:\n");

    for (i = n; i >= 1; i--) {
        if (dp[i][w] != dp[i - 1][w]) {
            selected[i - 1] = 1;
            w -= weight[i - 1];
        }
    }

    for (i = 0; i < n; i++) {
        if (selected[i]) {
            printf("Item %d: Weight = %d kg, Utility = %d\n",
                   i + 1, weight[i], value[i]);
        }
    }

    return 0;
}
