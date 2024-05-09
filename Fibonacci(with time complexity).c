#include <stdio.h>

void generateFibonacci(int limit) {
    int first = 0, second = 1, next;  // O(1)

    printf("Fibonacci Series up to %d:\n", limit);  // O(1)
    printf("%d, %d, ", first, second);  // O(1)

    next = first + second;  // O(1)
    while (next <= limit) {  // O(log(n))
        printf("%d, ", next);  // O(1)
        first = second;  // O(1)
        second = next;  // O(1)
        next = first + second;  // O(1)
    }
    printf("\n");  // O(1)
}

int main() {
    int limit;  // O(1)
    printf("Enter the limit for Fibonacci series: ");  // O(1)
    while (scanf("%d", &limit) != 1 || limit < 0) {  // O(log(n))
        printf("Invalid input. Please enter a non-negative integer: ");  // O(1)
        while (getchar() != '\n');  // O(n)
    }

    generateFibonacci(limit);  // O(log(n))

    return 0;  // O(1)
}
