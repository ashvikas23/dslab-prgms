#include <stdio.h>
#define MAX 50

int parent[MAX];
int n;

/* Initialize sets */
void makeSet() {
    for (int i = 0; i < n; i++)
        parent[i] = i;
}

/* Find representative */
int findSet(int x) {
    while (parent[x] != x)
        x = parent[x];
    return x;
}

/* Union of two sets */
void unionSet(int a, int b) {
    int rootA = findSet(a);
    int rootB = findSet(b);

    if (rootA != rootB)
        parent[rootB] = rootA;
    else
        printf("Both elements are in the same set\n");
}

/* Display sets */
void display() {
    printf("Element : Parent\n");
    for (int i = 0; i < n; i++)
        printf("%d : %d\n", i, parent[i]);
}

/* Main menu */
int main() {
    int choice, x, y;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    makeSet();

    while (1) {
        printf("\n--- Disjoint Set Menu ---\n");
        printf("1. Union of two sets\n");
        printf("2. Find representative\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            printf("Enter two elements: ");
            scanf("%d %d", &x, &y);
            unionSet(x, y);
            break;

        case 2:
            printf("Enter element: ");
            scanf("%d", &x);
            printf("Representative: %d\n", findSet(x));
            break;

        case 3:
            display();
            break;

        case 4:
            printf("Exiting...\n");
            return 0;   // exits program directly

        default:
            printf("Invalid choice\n");
        }
    }
}