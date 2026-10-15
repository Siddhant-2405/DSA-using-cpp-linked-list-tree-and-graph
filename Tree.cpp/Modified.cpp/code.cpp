#include <iostream>
#include <algorithm>
using namespace std;

struct Node {
    int key, height;
    Node *left, *right;

    Node(int value) {
        key = value;
        height = 1;
        left = right = NULL;
    }
};

int height(Node* n) {
    return n ? n->height : 0;
}

int balanceFactor(Node* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* t = x->right;

    x->right = y;
    y->left = t;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* t = y->left;

    y->left = x;
    x->right = t;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

Node* insertAVL(Node* root, int key) {
    if (!root)
        return new Node(key);

    if (key < root->key)
        root->left = insertAVL(root->left, key);
    else if (key > root->key)
        root->right = insertAVL(root->right, key);
    else
        return root;

    root->height = 1 + max(height(root->left), height(root->right));

    int b = balanceFactor(root);

    if (b > 1 && key < root->left->key)
        return rightRotate(root);

    if (b < -1 && key > root->right->key)
        return leftRotate(root);

    if (b > 1 && key > root->left->key) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    if (b < -1 && key < root->right->key) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

Node* insertBST(Node* root, int key) {
    if (!root)
        return new Node(key);

    if (key < root->key)
        root->left = insertBST(root->left, key);
    else if (key > root->key)
        root->right = insertBST(root->right, key);

    return root;
}

bool searchPath(Node* root, int key, int &comparisons,
                int &pathLength) {
    if (!root)
        return false;

    comparisons++;
    pathLength++;

    cout << root->key;

    if (root->key == key)
        return true;

    cout << " -> ";

    if (key < root->key)
        return searchPath(root->left, key, comparisons, pathLength);

    return searchPath(root->right, key, comparisons, pathLength);
}

void performSearch(Node* root, int key, string treeName) {
    int comparisons = 0, pathLength = 0;

    cout << treeName << " Search Path: ";

    bool found = searchPath(root, key, comparisons, pathLength);

    if (comparisons == 0)
        cout << "Empty tree";

    cout << "\nResult: " << (found ? "Key found" : "Key not found");
    cout << "\nComparisons: " << comparisons;
    cout << "\nSearch Path Length: " << pathLength << endl;
}

int main() {
    Node *avlRoot = NULL, *bstRoot = NULL;
    int n, value, m, key;

    cout << "Enter number of elements: ";
    cin >> n;

    cout << "Enter elements: ";

    for (int i = 0; i < n; i++) {
        cin >> value;
        avlRoot = insertAVL(avlRoot, value);
        bstRoot = insertBST(bstRoot, value);
    }

    cout << "Enter number of keys to search: ";
    cin >> m;

    for (int i = 0; i < m; i++) {
        cout << "\nEnter key to search: ";
        cin >> key;

        cout << "\nAVL Tree:\n";
        performSearch(avlRoot, key, "AVL");

        cout << "\nOrdinary BST:\n";
        performSearch(bstRoot, key, "BST");

        cout << "\n-------------------------\n";
    }

    return 0;
}
