#include <stdio.h>

#define SIZE 8   // universe size (0 to 7)

/* Display elements of the set */
void displayElements(int set[]) {
    printf("{ ");
    for (int i = 0; i < SIZE; i++) {
        if (set[i] == 1) {
            printf("%d ", i);
        }
    }
    printf("}");
}

/* Display bitstring representation */
void displayBitstring(int set[]) {
    printf(" [ ");
    for (int i = SIZE - 1; i >= 0; i--) {
        printf("%d", set[i]);
    }
    printf(" ]");
}

/* Union operation */
void setUnion(int set1[], int set2[], int result[]) {
    for (int i = 0; i < SIZE; i++) {
        result[i] = set1[i] | set2[i];
    }
}

/* Intersection operation */
void setIntersection(int set1[], int set2[], int result[]) {
    for (int i = 0; i < SIZE; i++) {
        result[i] = set1[i] & set2[i];
    }
}

/* Difference operation (A - B) */
void setDifference(int set1[], int set2[], int result[]) {
    for (int i = 0; i < SIZE; i++) {
        result[i] = set1[i] & (!set2[i]);
    }
}

/* Display set with elements and bitstring */
void displaySet(int set[]) {
    displayElements(set);
    displayBitstring(set);
    printf("\n");
}

int main() {
    int setA[SIZE] = {0};
    int setB[SIZE] = {0};
    int result[SIZE] = {0};
    int n, elem;

    /* Input Set A */
    printf("Enter number of elements in Set A: ");
    scanf("%d", &n);
    printf("Enter elements (0-%d) for Set A:\n", SIZE - 1);
    for (int i = 0; i < n; i++) {
        scanf("%d", &elem);
        if (elem >= 0 && elem < SIZE)
            setA[elem] = 1;
    }

    /* Input Set B */
    printf("Enter number of elements in Set B: ");
    scanf("%d", &n);
    printf("Enter elements (0-%d) for Set B:\n", SIZE - 1);
    for (int i = 0; i < n; i++) {
        scanf("%d", &elem);
        if (elem >= 0 && elem < SIZE)
            setB[elem] = 1;
    }

    printf("\nSet A = ");
    displaySet(setA);

    printf("Set B = ");
    displaySet(setB);

    setUnion(setA, setB, result);
    printf("\nA ∪ B = ");
    displaySet(result);

    setIntersection(setA, setB, result);
    printf("A ∩ B = ");
    displaySet(result);

    setDifference(setA, setB, result);
    printf("A - B = ");
    displaySet(result);

    return 0;
}