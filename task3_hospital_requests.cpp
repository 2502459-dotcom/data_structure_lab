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

// Linked List based Stack for emergency requests
class RequestStack {
private:
    Node* top;

public:
    RequestStack() : top(nullptr) {}

    ~RequestStack() {
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
        cout << "Request received: " << id << endl;
    }

    void pop() {
        if (isEmpty()) {
            cout << "No requests to handle." << endl;
            return;
        }
        Node* temp = top;
        cout << "Handled request: " << temp->data << endl;
        top = top->next;
        delete temp;
    }

    void peek() const {
        if (isEmpty()) cout << "New TOP request: (none)" << endl;
        else cout << "New TOP request: " << top->data << endl;
    }

    void display() const {
        if (isEmpty()) { cout << "(no requests)" << endl; return; }
        for (Node* cur = top; cur != nullptr; cur = cur->next) {
            cout << "  " << cur->data;
            if (cur == top) cout << "   <-- TOP";
            cout << endl;
        }
    }
};

int main() {
    RequestStack hospital;

    cout << "=== Step 1: Push patient request IDs ===" << endl;
    hospital.push("P101");
    hospital.push("P102");
    hospital.push("P103");
    hospital.push("P104");

    cout << "\n=== Step 2: All requests (TOP to bottom) ===" << endl;
    hospital.display();

    cout << "\n=== Step 3: POP to handle latest request ===" << endl;
    hospital.pop();

    cout << "\n=== Step 4: New TOP request ===" << endl;
    hospital.peek();

    cout << "\n=== Step 5: Remaining requests ===" << endl;
    hospital.display();

    return 0;
}
