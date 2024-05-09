#include <stdio.h>

void generateFibonacci(int limit) {
    int first = 0, second = 1, next;

    printf("Fibonacci Series up to %d:\n", limit);
    printf("%d, %d, ", first, second);

    next = first + second;
    while (next <= limit) {
        printf("%d, ", next);
        first = second;
        second = next;
        next = first + second;
    }
    printf("\n");
}

int main() {
    int limit;
    printf("Enter the limit for Fibonacci series: ");
    while (scanf("%d", &limit) != 1 || limit < 0) {
        printf("Invalid input. Please enter a non-negative integer: ");
        while (getchar() != '\n');
    }

    generateFibonacci(limit);

    return 0;
}
