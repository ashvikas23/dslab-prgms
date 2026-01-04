#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int graph[MAX][MAX];        // Original graph
int transpose[MAX][MAX];    // Transposed graph
int visited[MAX];
int stack[MAX];
int top = -1;

/* Stack operations */
void push(int v) {
    stack[++top] = v;
}

int pop() {
    return stack[top--];
}

/* DFS for original graph (fills stack by finish time) */
void dfs1(int v, int n) {
    visited[v] = 1;

    for (int i = 0; i < n; i++) {
        if (graph[v][i] && !visited[i])
            dfs1(i, n);
    }

    push(v);   // Push after visiting all neighbors
}

/* DFS for transposed graph */
void dfs2(int v, int n) {
    visited[v] = 1;
    printf("%d ", v);

    for (int i = 0; i < n; i++) {
        if (transpose[v][i] && !visited[i])
            dfs2(i, n);
    }
}

/* Function to find SCCs */
void findSCCs(int n) {

    /* Step 1: DFS on original graph */
    for (int i = 0; i < n; i++) {
        if (!visited[i])
            dfs1(i, n);
    }

    /* Step 2: Transpose the graph */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            transpose[i][j] = graph[j][i];
        }
    }

    /* Step 3: DFS on transposed graph using stack order */
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    printf("\nStrongly Connected Components:\n");

    while (top != -1) {
        int v = pop();
        if (!visited[v]) {
            dfs2(v, n);
            printf("\n");
        }
    }
}

/* MAIN FUNCTION */
int main() {
    int n, edges;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    /* Initialize graph */
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            graph[i][j] = 0;
        }
    }

    printf("Enter edges (u v) meaning u -> v:\n");
    for (int i = 0; i < edges; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
    }

    findSCCs(n);
    return 0;
}
