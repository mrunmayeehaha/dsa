// CIRCULAR QUEUE
#include <stdio.h>
#define SIZE 5

int queue[SIZE];
int front = -1;
int rear = -1;

int isempty() {
    return (front == -1);
}

void enqueue(int x) {
    if ((rear + 1) % SIZE == front) {
        printf("Overflow");
        return;
    } 
    if (front == -1) {  
        front = 0;
    } 
    rear = (rear + 1) % SIZE;
    queue[rear] = x;
}

void dequeue() {
    if (front == -1) {
        printf("Empty\n");
        return;
    } 
    else if (front == rear) {  
        front = rear = -1;
    } 
    else {
        front = (front + 1) % SIZE;
    }
}


void display() {
    int i;
    if (isempty()) {
        printf("Underflow");
        return;
    }
    printf("Queue elements: ");
    i = front;
    while (1) {
        printf("%d ", queue[i]);
        if (i == rear)
            break;
        i = (i + 1) % SIZE;
    }
}

int main() {
    enqueue(4);
    enqueue(6);
    enqueue(8);
    dequeue();
    enqueue(10);
    display();
    return 0;
}
