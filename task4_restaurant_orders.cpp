#include <iostream>
#include <string>
using namespace std;

// Node of the singly linked list
class Node {
public:
    string data;
    Node* next;
    Node(const string& d) : data(d), next(nullptr) {}
};

// Linked List based Stack for restaurant orders
class OrderStack {
private:
    Node* top;

public:
    OrderStack() : top(nullptr) {}

    ~OrderStack() {
        while (!isEmpty()) {
            Node* temp = top;
            top = top->next;
            delete temp;
        }
    }

    bool isEmpty() const { return top == nullptr; }

    void push(const string& id) {
        Node* newNode = new Node(id);
        newNode->next = top;
        top = newNode;
        cout << "New order stored: " << id << endl;
    }

    void pop() {
        if (isEmpty()) {
            cout << "No orders to process." << endl;
            return;
        }
        Node* temp = top;
        cout << "Processed order: " << temp->data << endl;
        top = top->next;
        delete temp;
    }

    void peek() const {
        if (isEmpty()) cout << "Current TOP order: (none)" << endl;
        else cout << "Current TOP order: " << top->data << endl;
    }

    void display() const {
        if (isEmpty()) { cout << "(no orders)" << endl; return; }
        for (Node* cur = top; cur != nullptr; cur = cur->next) {
            cout << "  " << cur->data;
            if (cur == top) cout << "   <-- TOP";
            cout << endl;
        }
    }
};

int main() {
    OrderStack restaurant;

    cout << "=== Step 1: Push order IDs ===" << endl;
    restaurant.push("ORD-101");
    restaurant.push("ORD-102");
    restaurant.push("ORD-103");
    restaurant.push("ORD-104");

    cout << "\n=== Step 2: All orders (TOP to bottom) ===" << endl;
    restaurant.display();

    cout << "\n=== Step 3: Two POP operations ===" << endl;
    restaurant.pop();
    restaurant.pop();

    cout << "\n=== Step 4: Current TOP order ===" << endl;
    restaurant.peek();

    cout << "\n=== Step 5: Remaining orders ===" << endl;
    restaurant.display();

    cout << "\n=== Step 6: Is the Stack empty? ===" << endl;
    cout << (restaurant.isEmpty() ? "Yes, the stack is empty." : "No, the stack is NOT empty.") << endl;

    return 0;
}
