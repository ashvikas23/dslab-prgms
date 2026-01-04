#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int graph[MAX][MAX];   // Adjacency matrix
int visited[MAX];
int stack[MAX];
int top = -1;

/* Push into stack */
void push(int v) {
    stack[++top] = v;
}

/* DFS function */
void dfs(int v, int n) {
    visited[v] = 1;

    for (int i = 0; i < n; i++) {
        if (graph[v][i] && !visited[i]) {
            dfs(i, n);
        }
    }

    /* Push vertex after exploring all neighbors */
    push(v);
}

/* Topological Sort function */
void topologicalSort(int n) {
    for (int i = 0; i < n; i++) {
        if (!visited[i])
            dfs(i, n);
    }

    printf("Topological Sort Order:\n");
    while (top != -1) {
        printf("%d ", stack[top--]);
    }
    printf("\n");
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

    topologicalSort(n);
    return 0;
}
