#include <stdio.h>

#define MAX 30

/* Structure to represent an edge */
typedef struct {
    int u, v, w;   // u: source, v: destination, w: weight
} Edge;

int parent[MAX];

/* Find operation (Disjoint Set) */
int find(int i) {
    while (parent[i] != i)
        i = parent[i];
    return i;
}

/* Union operation */
void unionSet(int i, int j) {
    int a = find(i);
    int b = find(j);
    parent[a] = b;
}

int main() {
    int i, j, n, e;
    Edge edges[MAX], temp;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter edges (u v w):\n");
    for (i = 0; i < e; i++) {
        scanf("%d %d %d",
              &edges[i].u,
              &edges[i].v,
              &edges[i].w);
    }

    /* Initialize disjoint sets */
    for (i = 0; i < n; i++)
        parent[i] = i;

    /* Sort edges by weight (Bubble Sort) */
    for (i = 0; i < e - 1; i++) {
        for (j = 0; j < e - i - 1; j++) {
            if (edges[j].w > edges[j + 1].w) {
                temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }

    printf("\nEdges in MST using Kruskal's Algorithm:\n");

    int count = 0;
    int total = 0;

    for (i = 0; i < e; i++) {
        int u = edges[i].u;
        int v = edges[i].v;
        int w = edges[i].w;

        /* Include edge if it does not form a cycle */
        if (find(u) != find(v)) {
            unionSet(u, v);
            printf("%d -- %d  (weight %d)\n", u, v, w);
            total += w;
            count++;

            if (count == n - 1)
                break;
        }
    }

    printf("\nTotal weight of MST = %d\n", total);

    return 0;
}
