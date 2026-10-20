// Task 2: Network Data Packet Management - Circular Queue using array and modulo
#include <iostream>
using namespace std;

const int SIZE = 5;

class CircularQueue {
    int arr[SIZE];
    int front, rear, count;
public:
    CircularQueue() : front(0), rear(-1), count(0) {}

    bool isFull()  { return count == SIZE; }
    bool isEmpty() { return count == 0; }

    void enqueue(int id) {
        if (isFull()) {
            cout << "Queue is FULL! Packet " << id << " dropped.\n";
            return;
        }
        rear = (rear + 1) % SIZE;      // circular movement
        arr[rear] = id;
        count++;
        cout << "Packet " << id << " inserted at index " << rear << ".\n";
    }

    void transmit() {
        if (isEmpty()) {
            cout << "Queue is EMPTY! No packet to transmit.\n";
            return;
        }
        cout << "Packet " << arr[front] << " transmitted (index " << front << " is now free).\n";
        front = (front + 1) % SIZE;    // circular movement
        count--;
    }

    void display() {
        if (isEmpty()) {
            cout << "No packets waiting for transmission.\n";
            return;
        }
        cout << "Packets waiting (oldest -> newest): ";
        for (int i = 0; i < count; i++) {
            int idx = (front + i) % SIZE;
            cout << arr[idx] << "[" << idx << "] ";
        }
        cout << "\n";
    }
};

int main() {
    CircularQueue q;
    int choice, id;
    do {
        cout << "\n===== Network Packet Management =====\n"
             << "1. Insert packet\n"
             << "2. Transmit oldest packet\n"
             << "3. Display waiting packets\n"
             << "4. Exit\n"
             << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1: cout << "Enter packet ID: "; cin >> id; q.enqueue(id); break;
            case 2: q.transmit(); break;
            case 3: q.display(); break;
            case 4: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 4);
    return 0;
}
