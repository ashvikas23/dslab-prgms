#include <stdio.h>

#define INF 9999
#define MAX 20

int main() {
    int G[MAX][MAX], visited[MAX];
    int i, j, n;
    int edges = 0;
    int x = 0, y = 0;
    int min, total = 0;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter adjacency matrix (enter 0 for no edge):\n");
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            scanf("%d", &G[i][j]);
            if (G[i][j] == 0)
                G[i][j] = INF;   // Treat 0 as no edge
        }
    }

    /* Mark all vertices as unvisited */
    for (i = 0; i < n; i++)
        visited[i] = 0;

    /* Start from vertex 0 */
    visited[0] = 1;

    printf("\nEdges in MST using Prim's Algorithm:\n");

    /* MST contains (n - 1) edges */
    while (edges < n - 1) {
        min = INF;

        /* Find minimum weight edge */
        for (i = 0; i < n; i++) {
            if (visited[i]) {
                for (j = 0; j < n; j++) {
                    if (!visited[j] && G[i][j] < min) {
                        min = G[i][j];
                        x = i;
                        y = j;
                    }
                }
            }
        }

        printf("%d -- %d  (weight %d)\n", x, y, min);
        total += min;
        visited[y] = 1;
        edges++;
    }

    printf("\nTotal weight of MST = %d\n", total);

    return 0;
}
