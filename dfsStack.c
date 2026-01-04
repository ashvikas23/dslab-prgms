#include <stdio.h>

#define MAX 100

int stack[MAX];
int top = -1;

/* Push operation */
void push(int x) {
    stack[++top] = x;
}

/* Pop operation */
int pop() {
    return stack[top--];
}

/* Check if stack is empty */
int isEmpty() {
    return top == -1;
}

/* DFS function using stack */
void DFS(int adj[][MAX], int n, int start) {
    int visited[MAX] = {0};

    push(start);
    printf("DFS Traversal: ");

    while (!isEmpty()) {
        int node = pop();

        if (!visited[node]) {
            printf("%d ", node);
            visited[node] = 1;

            /* Push adjacent vertices in reverse order */
            for (int i = n - 1; i >= 0; i--) {
                if (adj[node][i] == 1 && !visited[i]) {
                    push(i);
                }
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

    DFS(adj, n, start);

    return 0;
}
