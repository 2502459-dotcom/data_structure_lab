#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    string name;
    Node* left;
    Node* right;
    Node(string n) {
        name = n;
        left = NULL;
        right = NULL;
    }
};

void showNode(Node* n) {
    if (n == NULL) return;
    cout << n->name << " -> Left: ";
    if (n->left) cout << n->left->name; else cout << "NULL";
    cout << ", Right: ";
    if (n->right) cout << n->right->name; else cout << "NULL";
    cout << endl;
    showNode(n->left);
    showNode(n->right);
}

// ---------- PART 2: BST ----------
class BSTNode {
public:
    int id;
    BSTNode* left;
    BSTNode* right;
    BSTNode(int v) {
        id = v;
        left = NULL;
        right = NULL;
    }
};

class BST {
public:
    BSTNode* root;

    BST() { root = NULL; }
    ~BST() { destroy(root); }

    void destroy(BSTNode* n) {
        if (n == NULL) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }

    // returns false if duplicate
    bool insert(int v) {
        if (root == NULL) {
            root = new BSTNode(v);
            return true;
        }
        BSTNode* cur = root;
        while (true) {
            if (v == cur->id) return false;
            if (v < cur->id) {
                if (cur->left == NULL) { cur->left = new BSTNode(v); return true; }
                cur = cur->left;
            } else {
                if (cur->right == NULL) { cur->right = new BSTNode(v); return true; }
                cur = cur->right;
            }
        }
    }

    void search(int v) {
        BSTNode* cur = root;
        int visits = 0;
        while (cur != NULL) {
            visits++;
            if (v == cur->id) {
                cout << "ID " << v << " FOUND. Node visits: " << visits << endl;
                return;
            }
            if (v < cur->id) cur = cur->left;
            else cur = cur->right;
        }
        cout << "ID " << v << " NOT FOUND. Node visits: " << visits << endl;
    }

    BSTNode* findMin(BSTNode* n) {
        while (n->left != NULL) n = n->left;
        return n;
    }

    BSTNode* deleteNode(BSTNode* n, int v, bool& done) {
        if (n == NULL) return NULL;
        if (v < n->id) {
            n->left = deleteNode(n->left, v, done);
        } else if (v > n->id) {
            n->right = deleteNode(n->right, v, done);
        } else {
            done = true;
            // Case 1: leaf
            if (n->left == NULL && n->right == NULL) {
                delete n;
                return NULL;
            }
            // Case 2: one child
            if (n->left == NULL) {
                BSTNode* temp = n->right;
                delete n;
                return temp;
            }
            if (n->right == NULL) {
                BSTNode* temp = n->left;
                delete n;
                return temp;
            }
            // Case 3: two children -> copy smallest value of right subtree
            BSTNode* small = findMin(n->right);
            n->id = small->id;
            bool dummy = false;
            n->right = deleteNode(n->right, small->id, dummy);
        }
        return n;
    }

    void remove(int v) {
        bool done = false;
        root = deleteNode(root, v, done);
        if (done) cout << "ID " << v << " deleted." << endl;
        else cout << "ID " << v << " not found. Nothing deleted." << endl;
    }

    void inorder(BSTNode* n) {
        if (n == NULL) return;
        inorder(n->left);
        cout << n->id << " ";
        inorder(n->right);
    }

    void showInorder() {
        inorder(root);
        cout << endl;
    }
};

// builds a fresh copy of the original BST
void buildOriginal(BST& t) {
    int ids[7] = {48, 28, 68, 18, 38, 58, 78};
    for (int i = 0; i < 7; i++) t.insert(ids[i]);
}

int main() {
    // ----- General binary tree (7 staff members) -----
    cout << "===== GENERAL BINARY TREE =====" << endl;
    Node* root = new Node("Dean");
    root->left = new Node("Prof Ali");
    root->right = new Node("Prof Sara");
    root->left->left = new Node("Dr Ahmed");
    root->left->right = new Node("Dr Hina");
    root->right->left = new Node("Mr Usman");
    root->right->right = new Node("Ms Zara");
    showNode(root);

    // ----- BST -----
    cout << "\n===== BST OF STAFF IDs =====" << endl;
    BST tree;
    buildOriginal(tree);
    cout << "Initial IDs (in-order): ";
    tree.showInorder();

    // three additional IDs from the user
    for (int i = 1; i <= 3; i++) {
        int x;
        cout << "Enter additional staff ID " << i << ": ";
        cin >> x;
        if (tree.insert(x)) cout << "Inserted " << x << endl;
        else cout << "Duplicate ID " << x << " rejected." << endl;
    }
    cout << "Tree now (in-order): ";
    tree.showInorder();

    // searches
    cout << "\n--- Search tests ---" << endl;
    tree.search(58);   // existing
    tree.search(99);   // missing
    tree.search(5);    // smaller than all IDs

    // deletion tests, each on a fresh copy of the original BST
    cout << "\n--- Deletion tests (fresh copy each time) ---" << endl;

    BST t1;
    buildOriginal(t1);
    cout << "Leaf node (18): ";
    t1.remove(18);
    t1.showInorder();

    BST t2;
    buildOriginal(t2);
    t2.remove(18);   // now 28 has only one child (38)
    cout << "One child node (28): ";
    t2.remove(28);
    t2.showInorder();

    BST t3;
    buildOriginal(t3);
    cout << "Two children node (48): ";
    t3.remove(48);
    t3.showInorder();

    int d;
    cout << "\nEnter a staff ID to delete: ";
    cin >> d;
    tree.remove(d);
    cout << "Remaining IDs in ascending order: ";
    tree.showInorder();

    cout << "\n===== EXPLANATION =====" << endl;
    cout << "A general binary tree has no rule about where values go, so its" << endl;
    cout << "in-order output can be in any order." << endl;
    cout << "In a BST, left < node < right for every node, so in-order" << endl;
    cout << "(left, node, right) always gives sorted values." << endl;

    return 0;
}
