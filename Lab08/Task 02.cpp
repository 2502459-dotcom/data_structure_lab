#include <iostream>
using namespace std;

class Node {
public:
    int id;
    Node* left;
    Node* right;
    Node(int v) {
        id = v;
        left = NULL;
        right = NULL;
    }
};

class BST {
private:
    Node* root;

    void destroy(Node* n) {
        if (n == NULL) return;
        destroy(n->left);
        destroy(n->right);
        delete n;
    }

    Node* insertNode(Node* n, int v, bool& added) {
        if (n == NULL) {
            added = true;
            return new Node(v);
        }
        if (v < n->id) n->left = insertNode(n->left, v, added);
        else if (v > n->id) n->right = insertNode(n->right, v, added);
        // equal -> duplicate, nothing changes
        return n;
    }

    Node* findMin(Node* n) {
        while (n->left != NULL) n = n->left;
        return n;
    }

    Node* deleteNode(Node* n, int v, bool& done) {
        if (n == NULL) return NULL;
        if (v < n->id) {
            n->left = deleteNode(n->left, v, done);
        } else if (v > n->id) {
            n->right = deleteNode(n->right, v, done);
        } else {
            done = true;
            if (n->left == NULL && n->right == NULL) {      // leaf
                delete n;
                return NULL;
            }
            if (n->left == NULL) {                          // one child (right)
                Node* temp = n->right;
                delete n;
                return temp;
            }
            if (n->right == NULL) {                         // one child (left)
                Node* temp = n->left;
                delete n;
                return temp;
            }
            // two children: replace with smallest value in right subtree
            Node* small = findMin(n->right);
            n->id = small->id;
            bool dummy = false;
            n->right = deleteNode(n->right, small->id, dummy);
        }
        return n;
    }

    void inorder(Node* n) {
        if (n == NULL) return;
        inorder(n->left);
        cout << n->id << " ";
        inorder(n->right);
    }

    void preorder(Node* n) {
        if (n == NULL) return;
        cout << n->id << " ";
        preorder(n->left);
        preorder(n->right);
    }

    void postorder(Node* n) {
        if (n == NULL) return;
        postorder(n->left);
        postorder(n->right);
        cout << n->id << " ";
    }

    int count(Node* n) {
        if (n == NULL) return 0;
        return 1 + count(n->left) + count(n->right);
    }

    int height(Node* n) {
        if (n == NULL) return 0;
        int l = height(n->left);
        int r = height(n->right);
        if (l > r) return l + 1;
        return r + 1;
    }

public:
    BST() { root = NULL; }
    ~BST() { destroy(root); }

    void insert(int v) {
        bool added = false;
        root = insertNode(root, v, added);
        if (added) cout << "ID " << v << " inserted." << endl;
        else cout << "ID " << v << " already exists. Duplicate rejected." << endl;
    }

    void insertQuiet(int v) {
        bool added = false;
        root = insertNode(root, v, added);
    }

    void search(int v) {
        if (root == NULL) {
            cout << "Tree is empty." << endl;
            return;
        }
        Node* cur = root;
        while (cur != NULL) {
            if (v == cur->id) {
                cout << "ID " << v << " found." << endl;
                return;
            }
            if (v < cur->id) cur = cur->left;
            else cur = cur->right;
        }
        cout << "ID " << v << " not found." << endl;
    }

    void remove(int v) {
        if (root == NULL) {
            cout << "Tree is empty. Nothing to delete." << endl;
            return;
        }
        bool done = false;
        root = deleteNode(root, v, done);
        if (done) {
            cout << "ID " << v << " deleted. Updated IDs: ";
            inorder(root);
            cout << endl;
        } else {
            cout << "ID " << v << " does not exist. Nothing deleted." << endl;
        }
    }

    void showInorder() {
        if (root == NULL) { cout << "Tree is empty." << endl; return; }
        cout << "In-order: ";
        inorder(root);
        cout << endl;
    }

    void showPreorder() {
        if (root == NULL) { cout << "Tree is empty." << endl; return; }
        cout << "Pre-order: ";
        preorder(root);
        cout << endl;
    }

    void showPostorder() {
        if (root == NULL) { cout << "Tree is empty." << endl; return; }
        cout << "Post-order: ";
        postorder(root);
        cout << endl;
    }

    void showCount() {
        cout << "Total nodes: " << count(root) << endl;
    }

    void showHeight() {
        cout << "Height of BST: " << height(root) << endl;
    }
};

int main() {
    BST tree;
    int initial[9] = {55, 35, 75, 25, 45, 65, 85, 40, 50};
    for (int i = 0; i < 9; i++) tree.insertQuiet(initial[i]);

    int choice, id;
    do {
        cout << "\n===== HOSPITAL INVENTORY BST MENU =====" << endl;
        cout << "1. Insert an ID" << endl;
        cout << "2. Search for an ID" << endl;
        cout << "3. Delete an ID" << endl;
        cout << "4. Display in-order" << endl;
        cout << "5. Display pre-order" << endl;
        cout << "6. Display post-order" << endl;
        cout << "7. Count total nodes" << endl;
        cout << "8. Calculate height" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter choice: ";

        if (!(cin >> choice)) {          // not a number
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Enter a number from 1 to 9." << endl;
            choice = 0;
            continue;
        }

        switch (choice) {
            case 1:
                cout << "Enter ID to insert: ";
                cin >> id;
                tree.insert(id);
                break;
            case 2:
                cout << "Enter ID to search: ";
                cin >> id;
                tree.search(id);
                break;
            case 3:
                cout << "Enter ID to delete: ";
                cin >> id;
                tree.remove(id);
                break;
            case 4: tree.showInorder(); break;
            case 5: tree.showPreorder(); break;
            case 6: tree.showPostorder(); break;
            case 7: tree.showCount(); break;
            case 8: tree.showHeight(); break;
            case 9: cout << "Exiting program. Goodbye!" << endl; break;
            default:
                cout << "Invalid choice. Enter a number from 1 to 9." << endl;
        }
    } while (choice != 9);

    return 0;
}

