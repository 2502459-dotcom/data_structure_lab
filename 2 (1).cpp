
#include <iostream>
#include <string>
#include <queue>
#include <algorithm>
using namespace std;

class Node {
public:
    int emergencyID;
    string location;
    int severity;
    int height;

    Node* left;
    Node* right;

    Node(int id, string loc, int sev) {
        emergencyID = id;
        location = loc;
        severity = sev;
        height = 0;
        left = NULL;
        right = NULL;
    }
};

class AVL {
public:
    Node* root;

    AVL() {
        root = NULL;
    }

    // Get height of a node
    int getHeight(Node* node) {
        if (node == NULL)
            return -1;

        return node->height;
    }

    // Calculate balance factor
    int getBalance(Node* node) {
        if (node == NULL)
            return 0;

        return getHeight(node->left) - getHeight(node->right);
    }

    // Update node height
    void updateHeight(Node* node) {
        node->height = 1 + max(getHeight(node->left),
                               getHeight(node->right));
    }

    // Right Rotation
    Node* rightRotate(Node* y) {
        Node* x = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    // Left Rotation
    Node* leftRotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    // Insert emergency record
    Node* insert(Node* node, int id, string loc, int sev) {

        if (node == NULL)
            return new Node(id, loc, sev);

        if (id < node->emergencyID) {
            node->left = insert(node->left, id, loc, sev);
        }
        else if (id > node->emergencyID) {
            node->right = insert(node->right, id, loc, sev);
        }
        else {
            return node;
        }

        updateHeight(node);

        int balance = getBalance(node);

        // LL Case
        if (balance > 1 && id < node->left->emergencyID)
            return rightRotate(node);

        // RR Case
        if (balance < -1 && id > node->right->emergencyID)
            return leftRotate(node);

        // LR Case
        if (balance > 1 && id > node->left->emergencyID) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RL Case
        if (balance < -1 && id < node->right->emergencyID) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // Search emergency record
    Node* search(Node* node, int id) {
        if (node == NULL || node->emergencyID == id)
            return node;

        if (id < node->emergencyID)
            return search(node->left, id);

        return search(node->right, id);
    }

    // Find minimum node
    Node* findMin(Node* node) {
        while (node->left != NULL)
            node = node->left;

        return node;
    }

    // Delete emergency record
    Node* deleteNode(Node* node, int id) {

        if (node == NULL)
            return node;

        if (id < node->emergencyID) {
            node->left = deleteNode(node->left, id);
        }
        else if (id > node->emergencyID) {
            node->right = deleteNode(node->right, id);
        }
        else {

            // No child
            if (node->left == NULL && node->right == NULL) {
                delete node;
                return NULL;
            }

            // Only right child
            else if (node->left == NULL) {
                Node* temp = node->right;
                delete node;
                return temp;
            }

            // Only left child
            else if (node->right == NULL) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Two children
            Node* temp = findMin(node->right);

            node->emergencyID = temp->emergencyID;
            node->location = temp->location;
            node->severity = temp->severity;

            node->right = deleteNode(node->right,
                                     temp->emergencyID);
        }

        updateHeight(node);

        int balance = getBalance(node);

        // LL Case
        if (balance > 1 && getBalance(node->left) >= 0)
            return rightRotate(node);

        // LR Case
        if (balance > 1 && getBalance(node->left) < 0) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // RR Case
        if (balance < -1 && getBalance(node->right) <= 0)
            return leftRotate(node);

        // RL Case
        if (balance < -1 && getBalance(node->right) > 0) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // Display one emergency record
    void displayRecord(Node* node) {
        cout << "ID: " << node->emergencyID
             << " | Location: " << node->location
             << " | Severity: " << node->severity
             << " | Height: " << node->height
             << " | Balance Factor: " << getBalance(node)
             << endl;
    }

    // In-order Traversal
    void inOrder(Node* node) {
        if (node != NULL) {
            inOrder(node->left);
            displayRecord(node);
            inOrder(node->right);
        }
    }

    // Level-order Traversal (BFS)
    void levelOrder(Node* node) {
        if (node == NULL)
            return;

        queue<Node*> q;
        q.push(node);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            displayRecord(current);

            if (current->left != NULL)
                q.push(current->left);

            if (current->right != NULL)
                q.push(current->right);
        }
    }

    // Display final AVL tree structure
    void displayTree(Node* node, int space = 0) {
        if (node == NULL)
            return;

        space += 6;

        displayTree(node->right, space);

        cout << endl;

        for (int i = 6; i < space; i++)
            cout << " ";

        cout << node->emergencyID
             << " (BF:" << getBalance(node) << ")" << endl;

        displayTree(node->left, space);
    }
};

int main() {

    AVL rescue;

    // Insert 12 emergency records
    rescue.root = rescue.insert(rescue.root, 30, "Islamabad", 3);
    rescue.root = rescue.insert(rescue.root, 20, "Rawalpindi", 2);
    rescue.root = rescue.insert(rescue.root, 10, "Murree", 5);
    rescue.root = rescue.insert(rescue.root, 40, "Lahore", 4);
    rescue.root = rescue.insert(rescue.root, 50, "Karachi", 3);
    rescue.root = rescue.insert(rescue.root, 25, "Peshawar", 5);
    rescue.root = rescue.insert(rescue.root, 28, "Quetta", 2);
    rescue.root = rescue.insert(rescue.root, 27, "Multan", 4);
    rescue.root = rescue.insert(rescue.root, 60, "Faisalabad", 3);
    rescue.root = rescue.insert(rescue.root, 70, "Sialkot", 5);
    rescue.root = rescue.insert(rescue.root, 65, "Gujranwala", 2);
    rescue.root = rescue.insert(rescue.root, 5, "Abbottabad", 4);

    cout << "===== EMERGENCY RESCUE SYSTEM =====\n";

    // In-order traversal
    cout << "\n--- In-order Traversal ---\n";
    rescue.inOrder(rescue.root);

    // Level-order traversal
    cout << "\n--- Level-order Traversal (BFS) ---\n";
    rescue.levelOrder(rescue.root);

    // Search emergency
    cout << "\n--- Search Emergency ---\n";

    int searchID = 25;
    Node* found = rescue.search(rescue.root, searchID);

    if (found != NULL) {
        cout << "Emergency Record Found:\n";
        rescue.displayRecord(found);
    }
    else {
        cout << "Emergency Record Not Found!\n";
    }

    // Delete emergency
    cout << "\n--- Deleting Emergency ID 40 ---\n";

    rescue.root = rescue.deleteNode(rescue.root, 40);

    // Display updated records
    cout << "\n--- Updated In-order Traversal ---\n";
    rescue.inOrder(rescue.root);

    // Final AVL structure
    cout << "\n--- Final Balanced AVL Tree ---\n";
    rescue.displayTree(rescue.root);

    // Final BFS
    cout << "\n--- Final Level-order Traversal ---\n";
    rescue.levelOrder(rescue.root);

    return 0;
}

