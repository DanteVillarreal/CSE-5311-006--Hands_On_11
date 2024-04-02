
#include <stdio.h>
#include <stdlib.h>

typedef struct Node 
{
    int data;
    struct Node* left;
    struct Node* right;
} Node;

Node* newNode(int data) 
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

Node* insert(Node* node, int data) 
{
    if (node == NULL) return newNode(data);
    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    return node;
}

Node* minValueNode(Node* node) 
{
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

Node* deleteNode(Node* root, int data) 
{
    if (root == NULL) 
    {
        return root;
    }
    if (data < root->data)
    {
        root->left = deleteNode(root->left, data);
    }
    else if (data > root->data)
    {
        root->right = deleteNode(root->right, data);
    }
    else 
    {
        if (root->left == NULL) 
        {
            Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) 
        {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

void inorder(Node* root) 
{
    if (root != NULL) 
    {
        inorder(root->left);
        printf("%d \n", root->data);
        inorder(root->right);
    }
}

Node* search(Node* root, int key) 
{
    // Base Cases: root is null or key is present at root
    if (root == NULL || root->data == key)
       return root;
    
    // Key is greater than root's key
    if (root->data < key)
       return search(root->right, key);
 
    // Key is smaller than root's key
    return search(root->left, key);
}

int main() 
{
    Node* root = NULL;
    root = insert(root, 50);
    root = insert(root, 30);
    root = insert(root, 20);
    root = insert(root, 40);
    root = insert(root, 70);
    root = insert(root, 60);
    root = insert(root, 80);

    printf("Inorder traversal of the given tree \n");
    inorder(root);

    printf("\nDelete 20\n");
    root = deleteNode(root, 20);
    printf("Inorder traversal of the modified tree \n");
    inorder(root);

    printf("\nDelete 30\n");
    root = deleteNode(root, 30);
    printf("Inorder traversal of the modified tree \n");
    inorder(root);

    printf("\nDelete 50\n");
    root = deleteNode(root, 50);
    printf("Inorder traversal of the modified tree \n");
    inorder(root);

    // Search for a value in the tree
    int value_to_search = 60;
    printf("\nlooking for 60 in tree...");
    Node* result = search(root, value_to_search);
    if (result != NULL)
    {
        printf("\nFound %d in the tree\n", value_to_search);
    }
    else
    {
        printf("\n%d not found in the tree\n", value_to_search);
    }

    return 0;
}
