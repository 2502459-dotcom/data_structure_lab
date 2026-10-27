// Lab 08 - Task 2: Hospital and Emergency Inventory Management System (BST)
#include <iostream>
#include <limits>
using namespace std;

class Node {
public:
    int id;
    Node *left, *right;
    Node(int v) : id(v), left(nullptr), right(nullptr) {}
};

class BST {
    Node *root;

    void destroy(Node *n) {                 // post-order release of all nodes
        if (!n) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }
    bool insert(Node *&n, int id) {
        if (!n) { n = new Node(id); return true; }
        if (id < n->id) return insert(n->left, id);
        if (id > n->id) return insert(n->right, id);
        return false;                       // duplicate
    }
    bool search(Node *n, int id) const {
        if (!n) return false;
        if (id == n->id) return true;
        return id < n->id ? search(n->left, id) : search(n->right, id);
    }
    Node *findMin(Node *n) const {
        while (n->left) n = n->left;
        return n;
    }
    bool remove(Node *&n, int id) {
        if (!n) return false;
        if (id < n->id) return remove(n->left, id);
        if (id > n->id) return remove(n->right, id);
        if (!n->left && !n->right) {                 // leaf
            delete n; n = nullptr;
        } else if (!n->left || !n->right) {          // one child
            Node *child = n->left ? n->left : n->right;
            Node *old = n; n = child; delete old;
        } else {                                     // two children
            Node *succ = findMin(n->right);          // in-order successor
            n->id = succ->id;                        // copy successor value
            remove(n->right, succ->id);              // delete successor node
        }
        return true;
    }
    void inorder(Node *n) const   { if (!n) return; inorder(n->left);  cout << n->id << " "; inorder(n->right); }
    void preorder(Node *n) const  { if (!n) return; cout << n->id << " "; preorder(n->left);  preorder(n->right); }
    void postorder(Node *n) const { if (!n) return; postorder(n->left); postorder(n->right); cout << n->id << " "; }
    int count(Node *n) const  { return n ? 1 + count(n->left) + count(n->right) : 0; }
    int height(Node *n) const {                      // number of levels (empty tree = 0)
        if (!n) return 0;
        int l = height(n->left), r = height(n->right);
        return 1 + (l > r ? l : r);
    }
public:
    BST() : root(nullptr) {}
    ~BST() { destroy(root); }
    BST(const BST &) = delete;                       // avoid accidental shallow copies
    BST &operator=(const BST &) = delete;

    bool insert(int id) { return insert(root, id); }
    bool search(int id) const { return search(root, id); }
    bool remove(int id) { return remove(root, id); }
    bool empty() const { return root == nullptr; }
    void inorder() const   { inorder(root);   cout << endl; }
    void preorder() const  { preorder(root);  cout << endl; }
    void postorder() const { postorder(root); cout << endl; }
    int count() const  { return count(root); }
    int height() const { return height(root); }
};

// Reads an integer; re-prompts on invalid (non-numeric) input
int readInt(const char *prompt) {
    int x;
    while (true) {
        cout << prompt;
        if (cin >> x) return x;
        if (cin.eof()) exit(0);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input! Please enter a number.\n";
    }
}

void showMenu() {
    cout << "\n===== Hospital & Emergency Inventory BST =====\n"
         << "1. Insert an ID\n2. Search for an ID\n3. Delete an ID\n"
         << "4. Display in-order traversal\n5. Display pre-order traversal\n"
         << "6. Display post-order traversal\n7. Count total number of nodes\n"
         << "8. Calculate height of the BST\n9. Exit\n";
}

int main() {
    BST tree;
    int initial[] = {55, 35, 75, 25, 45, 65, 85, 40, 50};
    for (int id : initial) tree.insert(id);
    cout << "Initial IDs loaded into the BST.\n";

    int choice;
    do {
        showMenu();
        choice = readInt("Enter your choice (1-9): ");
        switch (choice) {
        case 1: {
            int id = readInt("Enter ID to insert: ");
            if (tree.insert(id)) cout << "ID " << id << " inserted successfully.\n";
            else cout << "ID " << id << " already exists. Duplicate rejected; tree unchanged.\n";
            break;
        }
        case 2: {
            if (tree.empty()) { cout << "Tree is empty. Nothing to search.\n"; break; }
            int id = readInt("Enter ID to search: ");
            cout << "ID " << id << (tree.search(id) ? " FOUND in the tree.\n" : " NOT FOUND in the tree.\n");
            break;
        }
        case 3: {
            if (tree.empty()) { cout << "Tree is empty. Nothing to delete.\n"; break; }
            int id = readInt("Enter ID to delete: ");
            if (tree.remove(id)) {
                cout << "ID " << id << " deleted successfully.\nUpdated IDs (in-order): ";
                tree.inorder();
            } else cout << "ID " << id << " does not exist. Nothing deleted.\n";
            break;
        }
        case 4: if (tree.empty()) cout << "Tree is empty.\n"; else { cout << "In-order: ";   tree.inorder(); }   break;
        case 5: if (tree.empty()) cout << "Tree is empty.\n"; else { cout << "Pre-order: ";  tree.preorder(); }  break;
        case 6: if (tree.empty()) cout << "Tree is empty.\n"; else { cout << "Post-order: "; tree.postorder(); } break;
        case 7: cout << "Total number of nodes: " << tree.count() << endl; break;
        case 8: cout << "Height of BST: " << tree.height() << " levels ("
                     << (tree.empty() ? 0 : tree.height() - 1) << " edges)\n"; break;
        case 9: cout << "Exiting. All nodes will be released by the destructor.\n"; break;
        default: cout << "Invalid choice! Please select a number between 1 and 9.\n";
        }
    } while (choice != 9);
    return 0;
}
