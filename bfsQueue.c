#include <stdio.h>

#define MAX 100

/* Queue implementation */
int queue[MAX];
int front = -1, rear = -1;

/* Enqueue operation */
void enqueue(int value) {
    if (rear == MAX - 1)
        return;   // Queue overflow (ignored for simplicity)

    if (front == -1)
        front = 0;

    queue[++rear] = value;
}

/* Dequeue operation */
int dequeue() {
    if (front == -1 || front > rear)
        return -1;

    return queue[front++];
}

/* Check if queue is empty */
int isEmpty() {
    return (front == -1 || front > rear);
}

/* BFS function */
void BFS(int adj[][MAX], int n, int start) {
    int visited[MAX] = {0};

    enqueue(start);
    visited[start] = 1;

    printf("BFS Traversal: ");

    while (!isEmpty()) {
        int node = dequeue();
        printf("%d ", node);

        for (int i = 0; i < n; i++) {
            if (adj[node][i] == 1 && visited[i] == 0) {
                enqueue(i);
                visited[i] = 1;
            }
        }
    }
    printf("\n");
}

int main() {
    int n, start;
    int adj[MAX][MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &adj[i][j]);
        }
    }

    printf("Enter starting vertex: ");
    scanf("%d", &start);

    BFS(adj, n, start);

    return 0;
}
