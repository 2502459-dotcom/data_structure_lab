// Task 3: Computer File Explorer - DFS Traversals (In-order, Pre-order, Post-order)
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class Node {
public:
    string folder;
    Node* left;
    Node* right;

    Node(string f) {
        folder = f;
        left = NULL;
        right = NULL;
    }
};

// In-order : Left -> Root -> Right
void inorder(Node* root) {
    if (root == NULL)
        return;
    inorder(root->left);
    cout << root->folder << "  ";
    inorder(root->right);
}

// Pre-order : Root -> Left -> Right
void preorder(Node* root) {
    if (root == NULL)
        return;
    cout << root->folder << "  ";
    preorder(root->left);
    preorder(root->right);
}

// Post-order : Left -> Right -> Root
void postorder(Node* root) {
    if (root == NULL)
        return;
    postorder(root->left);
    postorder(root->right);
    cout << root->folder << "  ";
}

int main() {
    Node* root = new Node("C_Drive");

    root->left  = new Node("Documents");
    root->right = new Node("Pictures");

    root->left->left   = new Node("Projects");
    root->left->right  = new Node("Notes");
    root->right->left  = new Node("Vacation");
    root->right->right = new Node("Screenshots");

    cout << "======= COMPUTER FILE EXPLORER (DFS) =======" << endl << endl;

    cout << "Tree:" << endl;
    cout << "                 C_Drive" << endl;
    cout << "               /         \\" << endl;
    cout << "        Documents       Pictures" << endl;
    cout << "         /    \\          /     \\" << endl;
    cout << "   Projects  Notes  Vacation  Screenshots" << endl << endl;

    cout << "1) In-order   (Left -> Root -> Right) :" << endl << "   ";
    inorder(root);
    cout << endl << endl;

    cout << "2) Pre-order  (Root -> Left -> Right) :" << endl << "   ";
    preorder(root);
    cout << endl << endl;

    cout << "3) Post-order (Left -> Right -> Root) :" << endl << "   ";
    postorder(root);
    cout << endl << endl;

    cout << "Visiting order explanation:" << endl;
    cout << "- In-order   : go as deep LEFT as possible, visit the folder, then go RIGHT." << endl;
    cout << "- Pre-order  : visit the folder FIRST, then its left subtree, then its right subtree." << endl;
    cout << "- Post-order : visit left subtree, right subtree, and the folder LAST." << endl;

    cout << endl;
    system("pause");
    return 0;
}
