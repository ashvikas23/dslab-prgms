#include <stdio.h>
#include <stdlib.h>

#define MIN_DEGREE 3   // Minimum degree (t)

/* Structure for a B-Tree node */
struct BTreeNode {
    int *keys;                      // Keys array
    struct BTreeNode **child;       // Child pointers
    int n;                          // Number of keys
    int leaf;                       // 1 if leaf, 0 otherwise
};

/* Create a new B-Tree node */
struct BTreeNode *createNode(int leaf) {
    struct BTreeNode *node =
        (struct BTreeNode *)malloc(sizeof(struct BTreeNode));

    node->leaf = leaf;
    node->keys = (int *)malloc((2 * MIN_DEGREE - 1) * sizeof(int));
    node->child = (struct BTreeNode **)
        malloc((2 * MIN_DEGREE) * sizeof(struct BTreeNode *));
    node->n = 0;

    return node;
}

/* Traverse the B-Tree */
void traverse(struct BTreeNode *root) {
    if (root == NULL)
        return;

    int i;
    for (i = 0; i < root->n; i++) {
        if (!root->leaf)
            traverse(root->child[i]);
        printf("%d ", root->keys[i]);
    }

    if (!root->leaf)
        traverse(root->child[i]);
}

/* Search a key in the B-Tree */
struct BTreeNode *search(struct BTreeNode *root, int key) {
    int i = 0;

    while (i < root->n && key > root->keys[i])
        i++;

    if (i < root->n && root->keys[i] == key)
        return root;

    if (root->leaf)
        return NULL;

    return search(root->child[i], key);
}

/* Split child y of parent at index i */
void splitChild(struct BTreeNode *parent, int i, struct BTreeNode *y) {
    struct BTreeNode *z = createNode(y->leaf);
    z->n = MIN_DEGREE - 1;

    for (int j = 0; j < MIN_DEGREE - 1; j++)
        z->keys[j] = y->keys[j + MIN_DEGREE];

    if (!y->leaf) {
        for (int j = 0; j < MIN_DEGREE; j++)
            z->child[j] = y->child[j + MIN_DEGREE];
    }

    y->n = MIN_DEGREE - 1;

    for (int j = parent->n; j >= i + 1; j--)
        parent->child[j + 1] = parent->child[j];

    parent->child[i + 1] = z;

    for (int j = parent->n - 1; j >= i; j--)
        parent->keys[j + 1] = parent->keys[j];

    parent->keys[i] = y->keys[MIN_DEGREE - 1];
    parent->n++;
}

/* Insert into a non-full node */
void insertNonFull(struct BTreeNode *x, int k) {
    int i = x->n - 1;

    if (x->leaf) {
        while (i >= 0 && x->keys[i] > k) {
            x->keys[i + 1] = x->keys[i];
            i--;
        }
        x->keys[i + 1] = k;
        x->n++;
    } else {
        while (i >= 0 && x->keys[i] > k)
            i--;

        if (x->child[i + 1]->n == 2 * MIN_DEGREE - 1) {
            splitChild(x, i + 1, x->child[i + 1]);
            if (k > x->keys[i + 1])
                i++;
        }
        insertNonFull(x->child[i + 1], k);
    }
}

/* Insert a key into the B-Tree */
void insert(struct BTreeNode **root, int k) {
    if (*root == NULL) {
        *root = createNode(1);
        (*root)->keys[0] = k;
        (*root)->n = 1;
        return;
    }

    if ((*root)->n == 2 * MIN_DEGREE - 1) {
        struct BTreeNode *s = createNode(0);
        s->child[0] = *root;

        splitChild(s, 0, *root);

        int i = 0;
        if (s->keys[0] < k)
            i++;

        insertNonFull(s->child[i], k);
        *root = s;
    } else {
        insertNonFull(*root, k);
    }
}

/* Get predecessor */
int getPred(struct BTreeNode *x) {
    while (!x->leaf)
        x = x->child[x->n];
    return x->keys[x->n - 1];
}

/* Get successor */
int getSucc(struct BTreeNode *x) {
    while (!x->leaf)
        x = x->child[0];
    return x->keys[0];
}

/* Merge child at idx with next sibling */
void merge(struct BTreeNode *x, int idx) {
    struct BTreeNode *child = x->child[idx];
    struct BTreeNode *sibling = x->child[idx + 1];

    child->keys[MIN_DEGREE - 1] = x->keys[idx];

    for (int i = 0; i < sibling->n; i++)
        child->keys[i + MIN_DEGREE] = sibling->keys[i];

    if (!child->leaf) {
        for (int i = 0; i <= sibling->n; i++)
            child->child[i + MIN_DEGREE] = sibling->child[i];
    }

    for (int i = idx + 1; i < x->n; i++)
        x->keys[i - 1] = x->keys[i];

    for (int i = idx + 2; i <= x->n; i++)
        x->child[i - 1] = x->child[i];

    child->n += sibling->n + 1;
    x->n--;

    free(sibling);
}

/* Borrow from previous sibling */
void borrowFromPrev(struct BTreeNode *x, int idx) {
    struct BTreeNode *child = x->child[idx];
    struct BTreeNode *sibling = x->child[idx - 1];

    for (int i = child->n - 1; i >= 0; i--)
        child->keys[i + 1] = child->keys[i];

    if (!child->leaf) {
        for (int i = child->n; i >= 0; i--)
            child->child[i + 1] = child->child[i];
    }

    child->keys[0] = x->keys[idx - 1];
    if (!child->leaf)
        child->child[0] = sibling->child[sibling->n];

    x->keys[idx - 1] = sibling->keys[sibling->n - 1];

    child->n++;
    sibling->n--;
}

/* Borrow from next sibling */
void borrowFromNext(struct BTreeNode *x, int idx) {
    struct BTreeNode *child = x->child[idx];
    struct BTreeNode *sibling = x->child[idx + 1];

    child->keys[child->n] = x->keys[idx];

    if (!child->leaf)
        child->child[child->n + 1] = sibling->child[0];

    x->keys[idx] = sibling->keys[0];

    for (int i = 1; i < sibling->n; i++)
        sibling->keys[i - 1] = sibling->keys[i];

    if (!sibling->leaf) {
        for (int i = 1; i <= sibling->n; i++)
            sibling->child[i - 1] = sibling->child[i];
    }

    child->n++;
    sibling->n--;
}

/* Fill child during deletion */
void fill(struct BTreeNode *x, int idx) {
    if (idx != 0 && x->child[idx - 1]->n >= MIN_DEGREE)
        borrowFromPrev(x, idx);
    else if (idx != x->n && x->child[idx + 1]->n >= MIN_DEGREE)
        borrowFromNext(x, idx);
    else {
        if (idx != x->n)
            merge(x, idx);
        else
            merge(x, idx - 1);
    }
}

/* Remove key from subtree rooted at x */
void removeNode(struct BTreeNode *x, int k) {
    int idx = 0;

    while (idx < x->n && x->keys[idx] < k)
        idx++;

    if (idx < x->n && x->keys[idx] == k) {
        if (x->leaf) {
            for (int i = idx + 1; i < x->n; i++)
                x->keys[i - 1] = x->keys[i];
            x->n--;
        } else {
            if (x->child[idx]->n >= MIN_DEGREE) {
                int pred = getPred(x->child[idx]);
                x->keys[idx] = pred;
                removeNode(x->child[idx], pred);
            } else if (x->child[idx + 1]->n >= MIN_DEGREE) {
                int succ = getSucc(x->child[idx + 1]);
                x->keys[idx] = succ;
                removeNode(x->child[idx + 1], succ);
            } else {
                merge(x, idx);
                removeNode(x->child[idx], k);
            }
        }
    } else {
        if (x->leaf)
            return;

        int flag = (idx == x->n);

        if (x->child[idx]->n < MIN_DEGREE)
            fill(x, idx);

        if (flag && idx > x->n)
            removeNode(x->child[idx - 1], k);
        else
            removeNode(x->child[idx], k);
    }
}

/* Delete a key from the B-Tree */
void deleteKey(struct BTreeNode **root, int k) {
    if (*root == NULL)
        return;

    removeNode(*root, k);

    if ((*root)->n == 0) {
        struct BTreeNode *tmp = *root;

        if ((*root)->leaf)
            *root = NULL;
        else
            *root = (*root)->child[0];

        free(tmp);
    }
}

/* MAIN */
int main() {
    struct BTreeNode *root = NULL;
    int choice, key;

    while (1) {
        printf("\n--- B-TREE OPERATIONS ---\n");
        printf("1. Insert\n2. Delete\n3. Display\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                insert(&root, key);
                break;

            case 2:
                printf("Enter key to delete: ");
                scanf("%d", &key);
                deleteKey(&root, key);
                break;

            case 3:
                printf("B-Tree Traversal: ");
                traverse(root);
                printf("\n");
                break;

            case 4:
                exit(0);

            default:
                printf("Invalid choice!\n");
        }
    }
    return 0;
}
