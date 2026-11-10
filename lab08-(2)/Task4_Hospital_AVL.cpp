// Task 4: Hospital Appointment System - AVL Tree
#include <iostream>
#include <cstdlib>
using namespace std;

class Node {
public:
    int token;
    Node* left;
    Node* right;
    int height;

    Node(int t) {
        token = t;
        left = NULL;
        right = NULL;
        height = 1;        // a new node is a leaf
    }
};

int maxOf(int a, int b) {
    return (a > b) ? a : b;
}

// Height of a node (0 for NULL)
int getHeight(Node* n) {
    if (n == NULL)
        return 0;
    return n->height;
}

// Balance factor = height(left) - height(right)
int getBalance(Node* n) {
    if (n == NULL)
        return 0;
    return getHeight(n->left) - getHeight(n->right);
}

void updateHeight(Node* n) {
    n->height = 1 + maxOf(getHeight(n->left), getHeight(n->right));
}

// Right Rotation (used for LL case)
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    updateHeight(y);
    updateHeight(x);
    return x;
}

// Left Rotation (used for RR case)
Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    y->left = x;
    x->right = T2;

    updateHeight(x);
    updateHeight(y);
    return y;
}

// Insert according to BST rules, then rebalance
Node* insert(Node* root, int token) {
    // 1. Normal BST insertion
    if (root == NULL)
        return new Node(token);

    if (token < root->token)
        root->left = insert(root->left, token);
    else if (token > root->token)
        root->right = insert(root->right, token);
    else
        return root;               // duplicate tokens not allowed

    // 2. Update height
    updateHeight(root);

    // 3. Get balance factor
    int balance = getBalance(root);

    // 4. Four rotation cases
    // LL Case
    if (balance > 1 && token < root->left->token) {
        cout << "   [LL case at node " << root->token << "] -> Right Rotation" << endl;
        return rightRotate(root);
    }
    // RR Case
    if (balance < -1 && token > root->right->token) {
        cout << "   [RR case at node " << root->token << "] -> Left Rotation" << endl;
        return leftRotate(root);
    }
    // LR Case
    if (balance > 1 && token > root->left->token) {
        cout << "   [LR case at node " << root->token << "] -> Left Rotation on "
             << root->left->token << ", then Right Rotation on " << root->token << endl;
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    // RL Case
    if (balance < -1 && token < root->right->token) {
        cout << "   [RL case at node " << root->token << "] -> Right Rotation on "
             << root->right->token << ", then Left Rotation on " << root->token << endl;
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// In-order traversal (gives sorted tokens)
void inorder(Node* root) {
    if (root == NULL)
        return;
    inorder(root->left);
    cout << root->token << "  ";
    inorder(root->right);
}

// Print every node with height, balance factor and children (pre-order)
void displayDetails(Node* root) {
    if (root == NULL)
        return;

    cout << "Token " << root->token
         << " | Height = " << getHeight(root)
         << " | Balance Factor = " << getBalance(root)
         << " | Left = ";
    if (root->left) cout << root->left->token; else cout << "NULL";
    cout << " | Right = ";
    if (root->right) cout << root->right->token; else cout << "NULL";
    cout << endl;

    displayDetails(root->left);
    displayDetails(root->right);
}

// Sideways tree structure (root on the left, right subtree on top)
void printTree(Node* root, int space) {
    if (root == NULL)
        return;
    space += 8;
    printTree(root->right, space);
    cout << endl;
    for (int i = 8; i < space; i++)
        cout << " ";
    cout << root->token << endl;
    printTree(root->left, space);
}

int main() {
    Node* root = NULL;
    int tokens[7] = {15, 25, 35, 45, 55, 65, 75};

    cout << "======= HOSPITAL APPOINTMENT SYSTEM (AVL TREE) =======" << endl << endl;

    for (int i = 0; i < 7; i++) {
        cout << "Inserting token " << tokens[i] << endl;
        root = insert(root, tokens[i]);
        cout << "   In-order now : ";
        inorder(root);
        cout << "(root = " << root->token << ")" << endl << endl;
    }

    cout << "-----------------------------------------------" << endl;
    cout << "In-order Traversal of appointment tokens:" << endl;
    inorder(root);
    cout << endl << endl;

    cout << "Height and Balance Factor of each node:" << endl;
    displayDetails(root);

    cout << endl << "Final balanced tree structure (root on left):" << endl;
    printTree(root, 0);

    cout << endl << "Tree shape:" << endl;
    cout << "                45" << endl;
    cout << "            /        \\" << endl;
    cout << "          25          65" << endl;
    cout << "         /  \\        /  \\" << endl;
    cout << "       15    35    55    75" << endl;

    cout << endl;
    system("pause");
    return 0;
}
