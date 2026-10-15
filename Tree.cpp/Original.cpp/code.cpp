#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int key;
    Node *left, *right;
    int height;

    Node(int value) {
        key = value;
        left = right = NULL;
        height = 1;
    }
};

int height(Node* n) {
    return (n == NULL) ? 0 : n->height;
}

int getBalance(Node* n) {
    return (n == NULL) ? 0 :
           height(n->left) - height(n->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left),
                        height(y->right));
    x->height = 1 + max(height(x->left),
                        height(x->right));

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left),
                        height(x->right));
    y->height = 1 + max(height(y->left),
                        height(y->right));

    return y;
}

Node* insert(Node* node, int key) {
    if (node == NULL)
        return new Node(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;

    node->height = 1 + max(height(node->left),
                           height(node->right));

    int balance = getBalance(node);

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

bool searchPath(Node* root, int key) {
    if (root == NULL)
        return false;

    cout << root->key;

    if (root->key == key)
        return true;

    if (key < root->key) {
        cout << " -> ";
        return searchPath(root->left, key);
    } else {
        cout << " -> ";
        return searchPath(root->right, key);
    }
}

int main() {
    Node* root = NULL;
    int n, value, key;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements: ";

    for (int i = 0; i < n; i++) {
        cin >> value;
        root = insert(root, value);
    }

    cout << "Enter key to search: ";
    cin >> key;

    cout << "Search Path: ";

    if (searchPath(root, key))
        cout << "\nKey found!";
    else
        cout << "\nKey not found!";

    cout << endl;

    return 0;
}
