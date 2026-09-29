#include <iostream>
using namespace std;
struct Node {
    int rollNo;
    Node* next;

    Node(int r) {
        rollNo = r;
        next = nullptr;
    }
};

class StudentList {
private:
    Node* head;

public:
    StudentList() { head = nullptr; }

    ~StudentList() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
    }

    void addStudent(int rollNo) {
        Node* newNode = new Node(rollNo);

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
            cout << "No students registered yet.\n";
            return;
        }

        cout << "Registered Students:\n";
        Node* current = head;
        while (current != nullptr) {
            cout << current->rollNo;
            if (current->next != nullptr)
                cout << " -> ";
            current = current->next;
        }
        cout << "\n";
    }

    bool search(int rollNo) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->rollNo == rollNo)
                return true;
            current = current->next;
        }
        return false;
    }
};

int main() {
    StudentList list;
    int choice, roll;

    do {
        cout << "\n===== Student Registration System =====\n";
        cout << "1. Register a student\n";
        cout << "2. Display registered students\n";
        cout << "3. Search a student by roll number\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Roll Number: ";
            cin >> roll;
            list.addStudent(roll);
            cout << "Student " << roll << " registered successfully.\n";
            break;
        case 2:
            list.display();
            break;
        case 3:
            cout << "Enter Roll Number to Search: ";
            cin >> roll;
            if (list.search(roll))
                cout << "Student Found\n";
            else
                cout << "Student Not Found\n";
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