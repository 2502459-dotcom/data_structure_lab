// Task 3: Hospital Emergency Department - Priority Queue implemented with an array
// Priority rule: a SMALLER number means HIGHER urgency (1 = most urgent).
// The array is kept sorted by priority (ascending). Patients with equal
// priority are treated in arrival order (FIFO), so the front is always next.
#include <iostream>
#include <string>
using namespace std;

const int MAX = 10;

struct Patient {
    string id;
    int priority;
};

class PriorityQueue {
    Patient arr[MAX];
    int size;
public:
    PriorityQueue() : size(0) {}

    bool isEmpty() { return size == 0; }
    bool isFull()  { return size == MAX; }

    void insert(const string& id, int priority) {
        if (isFull()) {
            cout << "Queue is full! Cannot admit patient " << id << ".\n";
            return;
        }
        // find position: after all patients with priority <= new priority
        int i = size - 1;
        while (i >= 0 && arr[i].priority > priority) {
            arr[i + 1] = arr[i];
            i--;
        }
        arr[i + 1] = {id, priority};
        size++;
        cout << "Patient " << id << " admitted with priority " << priority << ".\n";
    }

    void treat() {
        if (isEmpty()) {
            cout << "No patients waiting. Queue is empty.\n";
            return;
        }
        cout << "Treating patient " << arr[0].id << " (priority " << arr[0].priority << ").\n";
        for (int i = 1; i < size; i++) arr[i - 1] = arr[i];
        size--;
    }

    void display() {
        if (isEmpty()) {
            cout << "No patients waiting.\n";
            return;
        }
        cout << "\nWaiting patients (next to treat first):\n";
        cout << "  Patient ID   Priority\n";
        for (int i = 0; i < size; i++)
            cout << "  " << arr[i].id << "\t\t" << arr[i].priority << "\n";
    }
};

int main() {
    PriorityQueue pq;
    int choice, priority;
    string id;
    do {
        cout << "\n===== Hospital Emergency Department =====\n"
             << "(Priority 1 = highest urgency)\n"
             << "1. Add patient\n"
             << "2. Treat next patient\n"
             << "3. Display waiting patients\n"
             << "4. Exit\n"
             << "Enter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "Enter patient ID: "; cin >> id;
                cout << "Enter priority (1 = highest): "; cin >> priority;
                pq.insert(id, priority);
                break;
            case 2: pq.treat(); break;
            case 3: pq.display(); break;
            case 4: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice.\n";
        }
    } while (choice != 4);
    return 0;
}
