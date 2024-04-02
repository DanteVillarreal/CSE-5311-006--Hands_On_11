#include <stdio.h>
#include <stdlib.h>

// Structure definition for an AVL tree node
struct Node 
{
    int data;
    struct Node* left;
    struct Node* right;
    int height; // Height of the subtree rooted at this node
};

// Global root node (initially NULL)
struct Node* root = NULL;


// Creates a new node in the AVL tree
struct Node* Create(int data) 
{
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    // Check for memory allocation error
    if (newNode == NULL) 
    {
        printf("\nMemory can't be allocated\n");
        return NULL;
    }

    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Calculates the height of a subtree
int Height(struct Node* root) 
{
    if (root == NULL) 
    {
        return 0;
    }

    int leftHeight = Height(root->left);
    int rightHeight = Height(root->right);

    return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
}

// Calculates the balance factor of a node
int BalanceFactor(struct Node* root) 
{
    if (root == NULL) 
    {
        return 0;
    }

    int leftHeight = Height(root->left);
    int rightHeight = Height(root->right);

    return leftHeight - rightHeight;
}

// Left rotation operation
struct Node* RotateLeft(struct Node* root) 
{
    struct Node* rightChild = root->right;
    root->right = rightChild->left;
    rightChild->left = root;

    // Update heights after rotation
    root->height = Height(root);
    rightChild->height = Height(rightChild);

    return rightChild;
}

// Right rotation operation
struct Node* RotateRight(struct Node* root) 
{
    struct Node* leftChild = root->left;
    root->left = leftChild->right;
    leftChild->right = root;

    // Update heights after rotation
    root->height = Height(root);
    leftChild->height = Height(leftChild);

    return leftChild;
}

// Inserts a new node into the AVL tree
struct Node* Insert(struct Node* root, int data) 
{
    if (root == NULL) 
    {
        return Create(data);
    }

    if (data > root->data) 
    {
        root->right = Insert(root->right, data);
    } else if (data < root->data) 
    {
        root->left = Insert(root->left, data);
    } else 
    { // Duplicate data (not allowed in BSTs)
        printf("Duplicate data insertion not allowed\n");
        return root;
    }

    // Update height after insertion
    root->height = Height(root);

    // Balance factor check and rotations
    int balance = BalanceFactor(root);

    // Left Left Case
    if (balance > 1 && data < root->left->data) 
    {
        return RotateRight(root);
    }

    // Right Right Case
    if (balance < -1 && data > root->right->data) 
    {
        return RotateLeft(root);
    }

    // Left Right Case
    if (balance > 1 && data > root->left->data) 
    {
        root->left = RotateLeft(root->left);
        return RotateRight(root);
    }

    // Right Left Case
    if (balance < -1 && data < root->right->data) 
    {
        root->right = RotateRight(root->right);
        return RotateLeft(root);
    }

    return root;
}

// Deletes a node from the AVL tree
struct Node* Delete(struct Node* root, int data) 
{
    if (root == NULL) 
    {
        return root;
    }

    int cmp; // Comparison value

    // Find the node to be deleted
    if ((cmp = data - root->data) < 0) 
    {
        root->left = Delete(root->left, data);
    } else if (cmp > 0) 
    {
        root->right = Delete(root->right, data);
    } else 
    {
        // Node with one or no child
        if (root->left == NULL) 
        {
            struct Node* temp = root->right;
            free(root);
            return temp;
        } 
        else if (root->right == NULL) 
        {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children: Get inorder successor (smallest in the right subtree)
        struct Node* temp = root->right;
        while (temp->left != NULL) 
        {
            temp = temp->left;
        }

        // Copy the inorder successor's data to the current node
        root->data = temp->data;

        // Delete the inorder successor
        root->right = Delete(root->right, temp->data);
    }

    // Update height after deletion
    root->height = Height(root);

    // Balance factor check and rotations (similar to Insert)
    int balance = BalanceFactor(root);

    // Left Left Case
    if (balance > 1 && BalanceFactor(root->left) >= 0) 
    {
        return RotateRight(root);
    }

    // Right Right Case
    if (balance < -1 && BalanceFactor(root->right) <= 0) 
    {
        return RotateLeft(root);
    }

    // Left Right Case
    if (balance > 1 && BalanceFactor(root->left) < 0) 
    {
        root->left = RotateLeft(root->left);
        return RotateRight(root);
    }

    // Right Left Case
    if (balance < -1 && BalanceFactor(root->right) > 0) 
    {
        root->right = RotateRight(root->right);
        return RotateLeft(root);
    }

    return root;
}

// Searches for a node with a specific data value
struct Node* Search(struct Node* root, int key) 
{
    if (root == NULL || key == root->data) 
    {
        return root; // Key found or tree is empty
    }

    if (key < root->data) 
    {
        return Search(root->left, key);
    } 
    else 
    {
        return Search(root->right, key);
    }
}

// In-order traversal for printing the tree elements
void InOrder(struct Node* root) 
{
    if (root == NULL) 
    {
        return;
    }

    InOrder(root->left);
    printf("%d ", root->data);
    InOrder(root->right);
}

int main() 
{
    int data;
    struct Node* result;

    // 7 insertions
    for (int i = 1; i <= 7; i++) 
    {
        printf("\nEnter data for insertion %d: ", i);
        scanf("%d", &data);
        root = Insert(root, data);
        printf("\nInorder traversal after insertion %d:\n", i);
        InOrder(root);
        printf("\n");
    }

    // 2 deletions
    for (int i = 1; i <= 2; i++) 
    {
        printf("\nEnter data for deletion %d: ", i);
        scanf("%d", &data);
        root = Delete(root, data);
        printf("\nInorder traversal after deletion %d:\n", i);
        InOrder(root);
        printf("\n");
    }

    printf("\n\nchoose a node to search: ");
    scanf("%d", &data);
    result = Search(root, data); // Now compatible pointer types
    if (result == NULL)
    {
        printf("Data not found in the AVL tree.\n");
    }
    else 
    {
        printf("Data found in the AVL tree.\n");
    }

    return 0;
}
