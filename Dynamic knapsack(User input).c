#include <stdio.h>
#include <math.h>

#define MAX_CAPACITY 100  // Maximum weight capacity of the knapsack
#define MAX_ITEMS 100     // Maximum number of items

int knapsack(int capacity, int weights[], int values[], int num_items) {
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
    int values[MAX_ITEMS], weights[MAX_ITEMS];
    int max_capacity, num_items;

    printf("Enter the number of items: ");
    scanf("%d", &num_items);

    printf("Enter the values and weights of each item:\n");
    for (int i = 0; i < num_items; i++) {
        printf("Weight of item %d: ", i + 1);
        scanf("%d", &weights[i]);
        printf("Value of item %d: ", i + 1);
        scanf("%d", &values[i]);

    }

    printf("Enter the maximum weight capacity of the knapsack: ");
    scanf("%d", &max_capacity);

    printf("Maximum value = %d\n", knapsack(max_capacity, weights, values, num_items));

    return 0;
}
