#include <stdio.h>
#include <stdlib.h>

// Define structure for a BST node
struct Node {
    int data;
    struct Node *left, *right;
};

// Create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Insert into BST
struct Node* insert(struct Node* root, int value) {
    if (root == NULL) {
        printf("Inserted %d into BST.\n", value);
        return createNode(value);
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    } else if (value > root->data) {
        root->right = insert(root->right, value);
    } else {
        printf("Value %d already exists in BST (not inserted).\n", value);
    }
    return root;
}

// Find minimum value node (used for deletion)
struct Node* findMin(struct Node* node) {
    struct Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Delete from BST
struct Node* deleteNode(struct Node* root, int value) {
    if (root == NULL) {
        printf("Value %d not found (nothing deleted).\n", value);
        return root;
    }

    if (value < root->data) {
        root->left = deleteNode(root->left, value);
    } else if (value > root->data) {
        root->right = deleteNode(root->right, value);
    } else {
        // Node with one or no child
        if (root->left == NULL) {
            struct Node* temp = root->right;
            printf("Deleted %d from BST.\n", root->data);
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct Node* temp = root->left;
            printf("Deleted %d from BST.\n", root->data);
            free(root);
            return temp;
        }
        // Node with two children
        struct Node* temp = findMin(root->right);
        printf("Deleted %d (replaced with %d).\n", root->data, temp->data);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Search in BST
struct Node* search(struct Node* root, int value) {
    if (root == NULL) return NULL;
    if (root->data == value) return root;
    if (value < root->data) return search(root->left, value);
    return search(root->right, value);
}

// Traversals
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

void preorder(struct Node* root) {
    if (root != NULL) {
        printf("%d ", root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(struct Node* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printf("%d ", root->data);
    }
}

// Main function with menu-driven program
int main() {
    struct Node* root = NULL;
    int choice, value, tchoice;
    struct Node* result;

    while (1) {
        printf("\n--- Binary Search Tree Operations ---\n");
        printf("1. Insert\n2. Delete\n3. Search\n4. Traversals\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter value to insert: ");
            scanf("%d", &value);
            root = insert(root, value);
            break;
        case 2:
            printf("Enter value to delete: ");
            scanf("%d", &value);
            root = deleteNode(root, value);
            break;
        case 3:
            printf("Enter value to search: ");
            scanf("%d", &value);
            result = search(root, value);
            if (result != NULL)
                printf("Value %d found in BST.\n", value);
            else
                printf("Value %d not found in BST.\n", value);
            break;
        case 4:
            printf("\n--- Traversal Options ---\n");
            printf("1. Inorder\n2. Preorder\n3. Postorder\n");
            printf("Enter your choice: ");
            scanf("%d", &tchoice);
            switch (tchoice) {
                case 1:
                    printf("Inorder Traversal: ");
                    inorder(root);
                    printf("\n");
                    break;
                case 2:
                    printf("Preorder Traversal: ");
                    preorder(root);
                    printf("\n");
                    break;
                case 3:
                    printf("Postorder Traversal: ");
                    postorder(root);
                    printf("\n");
                    break;
                default:
                    printf("Invalid traversal choice!\n");
            }
            break;
        case 5:
            printf("Exiting program.\n");
            exit(0);
        default:
            printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}