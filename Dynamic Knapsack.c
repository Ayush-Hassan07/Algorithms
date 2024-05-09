#include <stdio.h>

#define MAX_CAPACITY 5  // Maximum weight capacity of the knapsack
#define MAX_ITEMS 4     // Maximum number of items

int knapSack(int capacity, int weights[], int values[], int num_items) {
    int i, w;
    int K[MAX_CAPACITY + 1][MAX_ITEMS + 1];

    // Build table K[][] in bottom up manner
    for (w = 0; w <= capacity; w++) {
        for (i = 0; i <= num_items; i++) {
            if (i == 0 || w == 0)
                K[w][i] = 0;
            else if (weights[i - 1] <= w)
                K[w][i] = fmax(values[i - 1] + K[w - weights[i - 1]][i - 1], K[w][i - 1]);
            else
                K[w][i] = K[w][i - 1];
        }
    }

    return K[capacity][num_items];
}

int main() {
    int values[] = {12, 10, 20, 15};
    int weights[] = {2, 1, 3, 2};
    int capacity = 5;
    int num_items = sizeof(values) / sizeof(values[0]);

    printf("Maximum value = %d\n", knapSack(capacity, weights, values, num_items));

    return 0;
}
