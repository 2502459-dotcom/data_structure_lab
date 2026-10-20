// Task 1: Bank Customer Service System - Simple (Linear) Queue using array
#include <iostream>
using namespace std;

const int MAX = 5;  // fixed size

class LinearQueue {
    int arr[MAX];
    int front, rear;
public:
    LinearQueue() : front(-1), rear(-1) {}

    bool isEmpty() { return front == -1 || front > rear; }
    bool isFull()  { return rear == MAX - 1; }

    void enqueue(int token) {
        if (isFull()) {
            cout << "Overflow! Queue is full. Cannot add token " << token << ".\n";
            return;
        }
        if (front == -1) front = 0;
        arr[++rear] = token;
        cout << "Customer with token " << token << " joined the queue.\n";
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Underflow! No customers waiting.\n";
            return;
        }
        cout << "Now serving customer with token " << arr[front++] << ".\n";
        if (front > rear) front = rear = -1;  // queue became empty, reset
    }

    int count() { return isEmpty() ? 0 : rear - front + 1; }

    void display() {
        if (isEmpty()) {
            cout << "No customers are waiting.\n";
            return;
        }
        cout << "Waiting customers (front -> rear): ";
        for (int i = front; i <= rear; i++) cout << arr[i] << " ";
        cout << "\n";
    }
};

int main() {
    LinearQueue q;
    int choice, token;
    do {
        cout << "\n===== Bank Customer Service System =====\n"
             << "1. Add customer (enqueue)\n"
             << "2. Serve next customer (dequeue)\n"
             << "3. Display waiting customers\n"
             << "4. Number of waiting customers\n"
             << "5. Exit\n"
             << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: cout << "Enter token number: "; cin >> token; q.enqueue(token); break;
            case 2: q.dequeue(); break;
            case 3: q.display(); break;
            case 4: cout << "Waiting customers: " << q.count() << "\n"; break;
            case 5: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 5);
    return 0;
}
