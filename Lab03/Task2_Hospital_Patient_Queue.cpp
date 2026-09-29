#include <iostream>
#include <string>
using namespace std;
struct Node {
    string patientId;
    Node* next;

    Node(const string& id) {
        patientId = id;
        next = nullptr;
    }
};

class PatientQueue {
private:
    Node* head;

public:
    PatientQueue() { head = nullptr; }

    ~PatientQueue() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addPatient(const string& id) {
        Node* newNode = new Node(id);

        if (head == nullptr) {
            head = newNode;
            return;
        }

        Node* current = head;
        while (current->next != nullptr)
            current = current->next;
        current->next = newNode;
    }

    void display() const {
        if (head == nullptr) {
            cout << "No patients are waiting.\n";
            return;
        }

        Node* current = head;
        while (current != nullptr) {
            cout << current->patientId;
            if (current->next != nullptr)
                cout << " -> ";
            current = current->next;
        }
        cout << "\n";
    }

    void servePatient() {
        if (head == nullptr) {
            cout << "No patients to serve.\n";
            return;
        }

        Node* temp = head;
        head = head->next;
        cout << "Patient " << temp->patientId << " is being served.\n";
        delete temp;
    }
};

int main() {
    PatientQueue queue;
    int choice;
    string id;

    do {
        cout << "\n===== Hospital Patient Queue =====\n";
        cout << "1. Add a patient\n";
        cout << "2. Display waiting patients\n";
        cout << "3. Serve first patient\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Patient ID: ";
            cin >> id;
            queue.addPatient(id);
            cout << "Patient " << id << " added to the queue.\n";
            break;
        case 2:
            cout << "Waiting Patients:\n";
            queue.display();
            break;
        case 3:
            queue.servePatient();
            cout << "Updated Queue:\n";
            queue.display();
            break;
        case 4:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 4);

    return 0;
}