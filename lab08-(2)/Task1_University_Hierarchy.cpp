// Task 1: University Department Hierarchy - Binary Tree Creation
#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;

class Node {
public:
    string name;     // name of the department member
    Node* left;
    Node* right;

    Node(string n) {
        name = n;
        left = NULL;
        right = NULL;
    }
};

// Displays every member with his/her left and right child (pre-order walk)
void displayMembers(Node* root) {
    if (root == NULL)
        return;

    cout << "Member : " << root->name << endl;
    cout << "   Left child  : " << (root->left  ? root->left->name  : "NULL") << endl;
    cout << "   Right child : " << (root->right ? root->right->name : "NULL") << endl;
    cout << "-------------------------------------------" << endl;

    displayMembers(root->left);
    displayMembers(root->right);
}

// Prints the tree sideways (root on the left, right subtree on top)
void printTree(Node* root, int space) {
    if (root == NULL)
        return;
    space += 8;
    printTree(root->right, space);
    cout << endl;
    for (int i = 8; i < space; i++)
        cout << " ";
    cout << root->name << endl;
    printTree(root->left, space);
}

int main() {
    // Level 0 : Head of Department
    Node* root = new Node("Dr. Ahmed (HOD)");

    // Level 1 : Coordinators
    root->left  = new Node("Dr. Sara (CS Coordinator)");
    root->right = new Node("Dr. Bilal (AI Coordinator)");

    // Level 2 : Faculty members
    root->left->left   = new Node("Mr. Ali (Faculty)");
    root->left->right  = new Node("Ms. Hina (Faculty)");
    root->right->left  = new Node("Mr. Usman (Faculty)");
    root->right->right = new Node("Ms. Ayesha (Faculty)");

    cout << "======= UNIVERSITY DEPARTMENT HIERARCHY =======" << endl << endl;
    displayMembers(root);

    cout << endl << "Tree structure (rotated 90 degrees, root on left):" << endl;
    printTree(root, 0);

    cout << endl;
    system("pause");
    return 0;
}
