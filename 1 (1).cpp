
#include <iostream>
#include <string>
using namespace std;

class Node {
public:
    int flightNo;
    string destination;
    string departureTime;
    Node* left;
    Node* right;

    Node(int no, string dest, string time) {
        flightNo = no;
        destination = dest;
        departureTime = time;
        left = NULL;
        right = NULL;
    }
};

class BST {
public:
    Node* root;

    BST() {
        root = NULL;
    }

    // Insert a flight
    Node* insert(Node* node, int no, string dest, string time) {
        if (node == NULL) {
            return new Node(no, dest, time);
        }

        if (no < node->flightNo) {
            node->left = insert(node->left, no, dest, time);
        }
        else if (no > node->flightNo) {
            node->right = insert(node->right, no, dest, time);
        }

        return node;
    }

    // Search for a flight
    Node* search(Node* node, int no) {
        if (node == NULL || node->flightNo == no) {
            return node;
        }

        if (no < node->flightNo) {
            return search(node->left, no);
        }

        return search(node->right, no);
    }

    // Find minimum value
    Node* findMin(Node* node) {
        while (node != NULL && node->left != NULL) {
            node = node->left;
        }
        return node;
    }

    // Find maximum value
    Node* findMax(Node* node) {
        while (node != NULL && node->right != NULL) {
            node = node->right;
        }
        return node;
    }

    // Delete a flight
    Node* deleteNode(Node* node, int no) {
        if (node == NULL) {
            return node;
        }

        if (no < node->flightNo) {
            node->left = deleteNode(node->left, no);
        }
        else if (no > node->flightNo) {
            node->right = deleteNode(node->right, no);
        }
        else {
            // Case 1: No child
            if (node->left == NULL && node->right == NULL) {
                delete node;
                return NULL;
            }

            // Case 2: One child
            else if (node->left == NULL) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == NULL) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: Two children
            Node* temp = findMin(node->right);

            node->flightNo = temp->flightNo;
            node->destination = temp->destination;
            node->departureTime = temp->departureTime;

            node->right = deleteNode(node->right, temp->flightNo);
        }

        return node;
    }

    // In-order traversal
    void inOrder(Node* node) {
        if (node != NULL) {
            inOrder(node->left);
            displayFlight(node);
            inOrder(node->right);
        }
    }

    // Pre-order traversal
    void preOrder(Node* node) {
        if (node != NULL) {
            displayFlight(node);
            preOrder(node->left);
            preOrder(node->right);
        }
    }

    // Post-order traversal
    void postOrder(Node* node) {
        if (node != NULL) {
            postOrder(node->left);
            postOrder(node->right);
            displayFlight(node);
        }
    }

    // Display flight information
    void displayFlight(Node* node) {
        cout << node->flightNo << " | "
             << node->destination << " | "
             << node->departureTime << endl;
    }

    // Count total flights
    int countNodes(Node* node) {
        if (node == NULL) {
            return 0;
        }

        return 1 + countNodes(node->left)
                 + countNodes(node->right);
    }

    // Calculate tree height
    int height(Node* node) {
        if (node == NULL) {
            return 0;
        }

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        if (leftHeight > rightHeight) {
            return 1 + leftHeight;
        }
        else {
            return 1 + rightHeight;
        }
    }

    // Display BST structure
    void displayTree(Node* node, int space = 0) {
        if (node == NULL) {
            return;
        }

        space += 5;

        displayTree(node->right, space);

        cout << endl;

        for (int i = 5; i < space; i++) {
            cout << " ";
        }

        cout << node->flightNo << endl;

        displayTree(node->left, space);
    }
};

int main() {
    BST airport;

    // Insert 12 flight records
    airport.root = airport.insert(airport.root, 50, "London", "08:00");
    airport.root = airport.insert(airport.root, 30, "Dubai", "09:00");
    airport.root = airport.insert(airport.root, 70, "Paris", "10:00");
    airport.root = airport.insert(airport.root, 20, "Istanbul", "11:00");
    airport.root = airport.insert(airport.root, 40, "Doha", "12:00");
    airport.root = airport.insert(airport.root, 60, "Tokyo", "13:00");
    airport.root = airport.insert(airport.root, 80, "New York", "14:00");
    airport.root = airport.insert(airport.root, 10, "Riyadh", "15:00");
    airport.root = airport.insert(airport.root, 25, "Jeddah", "16:00");
    airport.root = airport.insert(airport.root, 35, "Rome", "17:00");
    airport.root = airport.insert(airport.root, 45, "Berlin", "18:00");
    airport.root = airport.insert(airport.root, 65, "Singapore", "19:00");

    cout << "===== AIRPORT FLIGHT SCHEDULING SYSTEM =====\n";

    cout << "\n--- In-order Traversal ---\n";
    airport.inOrder(airport.root);

    cout << "\n--- Pre-order Traversal ---\n";
    airport.preOrder(airport.root);

    cout << "\n--- Post-order Traversal ---\n";
    airport.postOrder(airport.root);

    // Search flight
    int searchNo = 40;
    Node* found = airport.search(airport.root, searchNo);

    cout << "\n--- Search Flight ---\n";
    if (found != NULL) {
        cout << "Flight Found: ";
        airport.displayFlight(found);
    }
    else {
        cout << "Flight Not Found!\n";
    }

    // Minimum and maximum
    cout << "\n--- Minimum and Maximum Flights ---\n";
    cout << "Minimum Flight Number: "
         << airport.findMin(airport.root)->flightNo << endl;

    cout << "Maximum Flight Number: "
         << airport.findMax(airport.root)->flightNo << endl;

    // Count flights
    cout << "\nTotal Flights: "
         << airport.countNodes(airport.root) << endl;

    // Height
    cout << "Tree Height: "
         << airport.height(airport.root) << endl;

    // Delete flights
    cout << "\n--- Deleting Flight 10 (Leaf Node) ---\n";
    airport.root = airport.deleteNode(airport.root, 10);

    cout << "\n--- Deleting Flight 30 (One Child) ---\n";
    airport.root = airport.deleteNode(airport.root, 30);

    cout << "\n--- Deleting Flight 50 (Two Children) ---\n";
    airport.root = airport.deleteNode(airport.root, 50);

    // Display final tree
    cout << "\n--- Final BST Structure ---\n";
    airport.displayTree(airport.root);

    cout << "\n--- Final In-order Traversal ---\n";
    airport.inOrder(airport.root);

    cout << "\nFinal Total Flights: "
         << airport.countNodes(airport.root) << endl;

    cout << "Final Tree Height: "
         << airport.height(airport.root) << endl;

    return 0;
}

