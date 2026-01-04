#include <stdio.h>
#define SIZE 4

int queue[SIZE];
int front = -1, rear = -1;

/* Enqueue operation */
void enqueue(int value) {
    /* Queue full condition */
    if ((front == 0 && rear == SIZE - 1) || (rear + 1) % SIZE == front) {
        printf("Queue is full. Cannot enqueue %d.\n", value);
    } 
    else {
        if (front == -1) {
            front = rear = 0;
        } else {
            rear = (rear + 1) % SIZE;
        }
        queue[rear] = value;
        printf("Inserted %d\n", value);
    }
}

/* Dequeue operation */
void dequeue() {
    if (front == -1) {
        printf("Queue is empty.\n");
    } 
    else {
        printf("Dequeued : %d\n", queue[front]);
        if (front == rear) {
            front = rear = -1;
        } else {
            front = (front + 1) % SIZE;
        }
    }
}

/* Display operation */
void display() {
    if (front == -1) {
        printf("Queue is empty.\n");
        return;
    }

    printf("Queue elements: ");
    int i = front;
    while (1) {
        printf("%d ", queue[i]);
        if (i == rear)
            break;
        i = (i + 1) % SIZE;
    }
    printf("\n");
}

int main() {
    int choice, value;

    while (1) {
        printf("\n---- Circular Queue Menu ----\n");
        printf("1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n");
        printf("Enter your choice : ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to enqueue : ");
                scanf("%d", &value);
                enqueue(value);
                break;

            case 2:
                dequeue();
                break;

            case 3:
                display();
                break;

            case 4:
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}