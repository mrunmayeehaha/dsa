//LINEAR QUEUE
#include <stdio.h>
#include <stdlib.h>

#define size 5 

int queue[size];
int front = -1;
int rear = -1;

int isfull() {
    return (rear == size- 1);
}

int isempty() {
    return (front == -1 || front > rear);
}

void enqueue(int x) {
    if (isfull()) {
        printf("\nQueue Overflow");
        return;
    }
    if (front == -1) {  
        front = 0;     //front value incremented
    }
    rear++;
    queue[rear] = x;  //data enqueued
}

int dequeue() {
    int x;
    if (isempty()) {
        printf("\nQueue Underflow");
        return -1;
    }
    x = queue[front];
    front++; //data dequeued
}

void display() {
    if (isempty()) {
        printf("\nQueue is Empty.\n");
        return;
    }
    printf("\nQueue elements: ");
for (int i = front; i <= rear; i++){ //rear will be ahead of front
        printf("%d ", queue[i]);
    }
    printf("\n");
}

int main() {
    int choice, x;

    while (1) {
        printf("\n--- Linear Queue Menu ---\n");
        printf("1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the element to insert: ");
                scanf("%d", &x);
                enqueue(x);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}