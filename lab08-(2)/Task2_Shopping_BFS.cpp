// Task 2: Online Shopping Categories - BFS Traversal using a queue
#include <iostream>
#include <string>
#include <queue>
#include <cstdlib>
using namespace std;

class Node {
public:
    string category;
    Node* left;
    Node* right;

    Node(string c) {
        category = c;
        left = NULL;
        right = NULL;
    }
};

// Breadth-First Traversal (level by level) using a queue
void bfs(Node* root) {
    if (root == NULL) {
        cout << "Tree is empty." << endl;
        return;
    }

    queue<Node*> q;
    q.push(root);
    int level = 0;

    while (!q.empty()) {
        int count = q.size();          // number of nodes on the current level
        cout << "Level " << level << " : ";

        for (int i = 0; i < count; i++) {
            Node* current = q.front();
            q.pop();

            cout << current->category;
            if (i < count - 1)
                cout << ", ";

            if (current->left != NULL)
                q.push(current->left);
            if (current->right != NULL)
                q.push(current->right);
        }
        cout << endl;
        level++;
    }
}

// Same BFS but prints all categories in one line (final BFS order)
void bfsOrder(Node* root) {
    if (root == NULL)
        return;

    queue<Node*> q;
    q.push(root);

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();
        cout << current->category;

        if (current->left != NULL)
            q.push(current->left);
        if (current->right != NULL)
            q.push(current->right);

        if (!q.empty())
            cout << " -> ";
    }
    cout << endl;
}

int main() {
    Node* root = new Node("All Products");

    root->left  = new Node("Electronics");
    root->right = new Node("Clothing");

    root->left->left   = new Node("Mobiles");
    root->left->right  = new Node("Laptops");
    root->right->left  = new Node("Men");
    root->right->right = new Node("Women");

    root->left->left->left = new Node("Accessories");

    cout << "======= ONLINE SHOPPING CATEGORIES (BFS) =======" << endl << endl;

    cout << "Level by level visit:" << endl;
    bfs(root);

    cout << endl << "BFS order of all categories:" << endl;
    bfsOrder(root);

    cout << endl;
    system("pause");
    return 0;
}
