#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


struct product {
    char name[30];
    int weight;
    int profit;
};


struct order {
    char product_name[30];
    char rank[6];
    int order_perday;
};


struct activity {
    char name[20];
    float start;
    float end;
};


struct QueueNode {
    int data;
    struct QueueNode* next;
};


struct Queue {
    struct QueueNode *front, *rear;
};


struct QueueNode* newQueueNode(int data) {
    struct QueueNode* temp = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    temp->data = data;
    temp->next = NULL;
    return temp;
}


struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    return queue;
}


bool isEmpty(struct Queue* queue) {
    return queue->front == NULL;
}


void enqueue(struct Queue* queue, int data) {
    struct QueueNode* temp = newQueueNode(data);
    if (queue->rear == NULL) {
        queue->front = queue->rear = temp;
        return;
    }
    queue->rear->next = temp;
    queue->rear = temp;
}


int dequeue(struct Queue* queue) {
    if (isEmpty(queue))
        return -1;
    struct QueueNode* temp = queue->front;
    int data = temp->data;
    queue->front = queue->front->next;
    if (queue->front == NULL)
        queue->rear = NULL;
    free(temp);
    return data;
}


void quickSort(struct order arr[], int start, int end);
int partition(struct order arr[], int start, int end);
void assignRankStars(struct order arr[], int size);
void knapsack(struct product products[], int n, int capacity);
void selectActivities(struct activity activities[], int n, float openingTime, float closingTime);
void bfs(struct order orders[], int n);


void quickSort(struct order arr[], int start, int end) {
    if (start >= end)
        return;
    else {
        int pivotIndex = partition(arr, start, end);
        quickSort(arr, start, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, end);
    }
}

int partition(struct order arr[], int start, int end) {
    int pivot = arr[end].order_perday;
    int i = start - 1;
    int j, temp;

    for (j = start; j <= end; j++) {
        if (arr[j].order_perday > pivot) {
            i++;

            struct order tempOrder = arr[i];
            arr[i] = arr[j];
            arr[j] = tempOrder;
        }
    }


    struct order tempOrder = arr[i + 1];
    arr[i + 1] = arr[end];
    arr[end] = tempOrder;

    return i + 1;
}


void assignRankStars(struct order arr[], int size) {
    int i;
    for (i = 0; i < size; i++) {
        int stars = 5 - i;
        int j;
        for (j = 0; j < stars && j < sizeof(arr[i].rank) - 1; j++) {
            arr[i].rank[j] = '*';
        }
        arr[i].rank[j] = '\0';
    }
}


void knapsack(struct product products[], int n, int capacity) {
    int i, w;
    int K[n + 1][capacity + 1];


    for (i = 0; i <= n; i++) {
        for (w = 0; w <= capacity; w++) {
            if (i == 0 || w == 0)
                K[i][w] = 0;
            else if (products[i - 1].weight <= w)
                K[i][w] = (products[i - 1].profit + K[i - 1][w - products[i - 1].weight] > K[i - 1][w])
                              ? products[i - 1].profit + K[i - 1][w - products[i - 1].weight]
                              : K[i - 1][w];
            else
                K[i][w] = K[i - 1][w];
        }
    }


    int res = K[n][capacity];
    w = capacity;
    printf("Selected products to load the truck:\n");
    for (i = n; i > 0 && res > 0; i--) {
        if (res != K[i - 1][w]) {
            printf("%s\n", products[i - 1].name);
            res -= products[i - 1].profit;
            w -= products[i - 1].weight;
        }
    }
}


void selectActivities(struct activity activities[], int n, float openingTime, float closingTime) {

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (activities[j].end > activities[j + 1].end) {
                struct activity temp = activities[j];
                activities[j] = activities[j + 1];
                activities[j + 1] = temp;
            }
        }
    }


    printf("Work Schedule Within The Factory Open Hours:\n");
    printf("%-20s %-10s %-10s\n", "Activity Name", "Start Time", "End Time");
    float lastEndTime = openingTime;
    for (int i = 0; i < n; i++) {
        if (activities[i].start >= lastEndTime && activities[i].end <= closingTime) {
            printf("%-20s %-10.2f %-10.2f\n", activities[i].name, activities[i].start, activities[i].end);
            lastEndTime = activities[i].end;
        }
    }
}


void bfs(struct order orders[], int n) {

    struct Queue* q = createQueue();


    for (int i = 0; i < n; i++) {
        enqueue(q, i);
    }

    printf("Optimized delivery sequence:\n");


    while (!isEmpty(q)) {
        int idx = dequeue(q);
        printf("%s\n", orders[idx].product_name);
    }
}

int main() {
    int num_products, num_orders, num_activities;

    printf("Enter the number of products: ");
    scanf("%d", &num_products);
    struct product products[num_products];


    for (int i = 0; i < num_products; i++) {
        printf("Enter product name, weight, and profit for product %d: ", i + 1);
        scanf("%s %d %d", products[i].name, &products[i].weight, &products[i].profit);
    }

    printf("Enter the number of orders: ");
    scanf("%d", &num_orders);
    struct order orders[num_orders];


    for (int i = 0; i < num_orders; i++) {
        printf("Enter product name and order per day for order %d: ", i + 1);
        scanf("%s %d", orders[i].product_name, &orders[i].order_perday);
    }

    printf("Enter the number of activities: ");
    scanf("%d", &num_activities);
    struct activity activities[num_activities];


    for (int i = 0; i < num_activities; i++) {
        printf("Enter activity name, start time, and end time for activity %d: ", i + 1);
        scanf("%s %f %f", activities[i].name, &activities[i].start, &activities[i].end);
    }

    int choice, capacity;
    float openingTime, closingTime;
    do {
        printf("\nEnter your choice:\n");
        printf("1. Show product insight\n");
        printf("2. Show order insight\n");
        printf("3. List products to load truck\n");
        printf("4. Schedule tasks for the factory\n");
        printf("5. Optimize delivery sequence using BFS\n");
        printf("6. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1:

                printf("Products:\n");
                printf("%-15s %-10s %-10s\n", "Name", "Weight", "Profit");
                printf("------------------------------------------------\n");

                for (int i = 0; i < num_products; i++) {
                    printf("%-15s %-10d %-10d\n", products[i].name, products[i].weight, products[i].profit);
                }
                break;

            case 2:

                quickSort(orders, 0, num_orders - 1);


                assignRankStars(orders, num_orders);


                printf("Orders:\n");
                printf("%-15s %-10s %-15s\n", "Product Name", "Rank", "Order Per Day");
                printf("------------------------------------------------\n");

                for (int i = 0; i < num_orders; i++) {
                    printf("%-15s %-10s %-15d\n", orders[i].product_name, orders[i].rank, orders[i].order_perday);
                }
                break;

            case 3:

                printf("Enter the capacity of the truck: ");
                scanf("%d", &capacity);
                printf("\n");
                knapsack(products, num_products, capacity);
                break;

            case 4:

                printf("Enter the opening time: ");
                scanf("%f", &openingTime);
                printf("Enter the closing time: ");
                scanf("%f", &closingTime);
                printf("\n");
                selectActivities(activities, num_activities, openingTime, closingTime);
                break;

            case 5:
                printf("Optimize delivery sequence using BFS\n");
                bfs(orders, num_orders);
                break;

            case 6:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice.\n");
                break;
        }
    } while (choice != 6);

    return 0;
}
