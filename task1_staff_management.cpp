// Lab 08 - Task 1: University Staff Management System (Binary Tree and BST)
#include <iostream>
#include <string>
#include <limits>
using namespace std;

// ---------------------------------------------------------------
// Node class: used by both the general binary tree and the BST
// ---------------------------------------------------------------
class Node {
public:
    int id;
    string name;
    Node *left, *right;
    Node(int i, const string &n = "") : id(i), name(n), left(nullptr), right(nullptr) {}
};

// ---------------------------------------------------------------
// Part A: General binary tree (no ordering rule)
// ---------------------------------------------------------------
class GeneralBinaryTree {
    Node *root;

    void destroy(Node *n) {
        if (!n) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }
    void display(Node *n) const {
        if (!n) return;
        cout << "  " << n->name << "  -> Left: " << (n->left ? n->left->name : "NULL")
             << " | Right: " << (n->right ? n->right->name : "NULL") << endl;
        display(n->left);
        display(n->right);
    }
    void inorderIds(Node *n) const {
        if (!n) return;
        inorderIds(n->left);
        cout << n->id << " ";
        inorderIds(n->right);
    }
public:
    GeneralBinaryTree() : root(nullptr) {}
    ~GeneralBinaryTree() { destroy(root); }

    // Builds an 8-member staff hierarchy by connecting nodes manually
    void build() {
        root = new Node(40, "Dr. Ahmed (Registrar)");
        root->left  = new Node(70, "Prof. Sara (Dean)");
        root->right = new Node(20, "Dr. Bilal (Director)");
        root->left->left   = new Node(60, "Mr. Usman (HoD CS)");
        root->left->right  = new Node(10, "Ms. Hina (HoD Math)");
        root->right->left  = new Node(50, "Mr. Kamran (Accountant)");
        root->right->right = new Node(30, "Ms. Ayesha (Librarian)");
        root->right->left->left = new Node(80, "Mr. Zain (Clerk)");
    }
    void display() const { display(root); }
    void displayInorderIds() const { inorderIds(root); cout << endl; }
};

// ---------------------------------------------------------------
// Part B: Binary Search Tree of unique staff IDs
// ---------------------------------------------------------------
class BST {
    Node *root;

    Node *copy(Node *n) const {
        if (!n) return nullptr;
        Node *c = new Node(n->id);
        c->left = copy(n->left);
        c->right = copy(n->right);
        return c;
    }
    void destroy(Node *n) {
        if (!n) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }
    bool insert(Node *&n, int id) {
        if (!n) { n = new Node(id); return true; }
        if (id < n->id) return insert(n->left, id);
        if (id > n->id) return insert(n->right, id);
        return false;                       // duplicate -> reject
    }
    Node *findMin(Node *n) const {
        while (n->left) n = n->left;
        return n;
    }
    bool remove(Node *&n, int id) {
        if (!n) return false;
        if (id < n->id) return remove(n->left, id);
        if (id > n->id) return remove(n->right, id);
        // node found
        if (!n->left && !n->right) {                       // Case 1: leaf
            cout << "  [Case: LEAF node " << id << "]" << endl;
            delete n; n = nullptr;
        } else if (!n->left || !n->right) {                // Case 2: one child
            Node *child = n->left ? n->left : n->right;
            cout << "  [Case: ONE CHILD node " << id << " -> replaced by child "
                 << child->id << "]" << endl;
            Node *old = n; n = child; delete old;
        } else {                                           // Case 3: two children
            Node *succ = findMin(n->right);
            cout << "  [Case: TWO CHILDREN node " << id << " -> replaced by in-order successor "
                 << succ->id << "]" << endl;
            n->id = succ->id;
            remove(n->right, succ->id);                    // remove the successor node
        }
        return true;
    }
    void inorder(Node *n) const {
        if (!n) return;
        inorder(n->left);
        cout << n->id << " ";
        inorder(n->right);
    }
    void structure(Node *n) const {
        if (!n) return;
        cout << "  " << n->id << " -> Left: ";
        if (n->left) cout << n->left->id; else cout << "NULL";
        cout << " | Right: ";
        if (n->right) cout << n->right->id; else cout << "NULL";
        cout << endl;
        structure(n->left);
        structure(n->right);
    }
public:
    BST() : root(nullptr) {}
    BST(const BST &o) : root(copy(o.root)) {}              // deep copy ("fresh copy")
    BST &operator=(const BST &o) {
        if (this != &o) { destroy(root); root = copy(o.root); }
        return *this;
    }
    ~BST() { destroy(root); }

    bool insert(int id) { return insert(root, id); }
    bool remove(int id) { return remove(root, id); }

    bool search(int id, int &visits) const {
        visits = 0;
        Node *cur = root;
        while (cur) {
            visits++;
            if (id == cur->id) return true;
            cur = (id < cur->id) ? cur->left : cur->right;
        }
        return false;
    }
    void inorder() const { inorder(root); cout << endl; }
    void structure() const { structure(root); }
};

// ---------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------
int readInt(const string &prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) return x;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "  Invalid input. Please enter a number.\n";
    }
}

void searchAndReport(const BST &t, int id) {
    int visits;
    bool found = t.search(id, visits);
    cout << "  Search " << id << ": " << (found ? "FOUND" : "NOT FOUND")
         << " | Node visits = " << visits << endl;
}

int main() {
    cout << "===== PART A: GENERAL BINARY TREE =====" << endl;
    GeneralBinaryTree gt;
    gt.build();
    gt.display();
    cout << "In-order of staff IDs in general tree: ";
    gt.displayInorderIds();

    cout << "\n===== PART B: BST OF STAFF IDs =====" << endl;
    BST bst;
    int initial[] = {48, 28, 68, 18, 38, 58, 78};
    for (int id : initial) bst.insert(id);
    cout << "Initial BST (in-order): "; bst.inorder();
    cout << "Initial BST structure:" << endl; bst.structure();

    BST original = bst;    // saved copy of the ORIGINAL 7-node BST for deletion tests

    cout << "\n--- Insert three additional staff IDs ---" << endl;
    int added = 0;
    while (added < 3) {
        int id = readInt("Enter new staff ID (" + to_string(added + 1) + "/3): ");
        if (bst.insert(id)) { cout << "  Inserted " << id << endl; added++; }
        else cout << "  Duplicate ID " << id << " rejected. Tree unchanged." << endl;
    }
    cout << "BST after insertions (in-order): "; bst.inorder();

    cout << "\n--- Search tests (with node-visit counts) ---" << endl;
    int existing = readInt("Enter an EXISTING staff ID to search: ");
    searchAndReport(bst, existing);
    int missing = readInt("Enter a MISSING staff ID to search: ");
    searchAndReport(bst, missing);
    int smaller = readInt("Enter an ID SMALLER than all registered IDs: ");
    searchAndReport(bst, smaller);

    cout << "\n--- Deletion tests on fresh copies of the original BST ---" << endl;
    {
        BST t = original;
        cout << "Test 1: delete leaf 18" << endl;
        t.remove(18);
        cout << "  In-order: "; t.inorder();
    }
    {
        BST t = original;
        t.insert(20);   // gives node 18 exactly one child (20)
        cout << "Test 2: node with one child (insert 20 so that 18 has one child), delete 18" << endl;
        t.remove(18);
        cout << "  In-order: "; t.inorder();
    }
    {
        BST t = original;
        cout << "Test 3: delete node with two children: 28" << endl;
        t.remove(28);
        cout << "  In-order: "; t.inorder();
    }
    {
        BST t = original;
        cout << "Test 4: delete root (two children): 48" << endl;
        t.remove(48);
        cout << "  In-order: "; t.inorder();
    }

    cout << "\n--- User deletion on the main BST ---" << endl;
    int del = readInt("Enter staff ID to delete: ");
    if (bst.remove(del)) cout << "  Deleted " << del << endl;
    else cout << "  ID " << del << " not found. Nothing deleted." << endl;

    cout << "\nRemaining staff IDs in ascending order (in-order traversal): ";
    bst.inorder();
    return 0;
}
