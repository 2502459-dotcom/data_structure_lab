#include <iostream>
#include <string>
using namespace std;

// Array-based Stack storing text editor actions
class UndoStack {
private:
    static const int MAX = 10;
    string actions[MAX];
    int top;

public:
    UndoStack() : top(-1) {}

    bool isEmpty() const { return top == -1; }
    bool isFull() const { return top == MAX - 1; }

    void push(const string& action) {
        if (isFull()) {
            cout << "Stack overflow! Cannot add: " << action << endl;
            return;
        }
        actions[++top] = action;
        cout << "Performed: " << action << endl;
    }

    string pop() {
        if (isEmpty()) {
            cout << "Nothing to undo." << endl;
            return "";
        }

        string action = actions[top--];
        cout << "Undo -> reversed action: " << action << endl;
        return action;
    }

    void undo() {
        pop();
    }

    void peek() const {
        if (isEmpty()) cout << "Current TOP action: (none)" << endl;
        else cout << "Current TOP action: " << actions[top] << endl;
    }

    void display() const {
        if (isEmpty()) { cout << "(no actions)" << endl; return; }
        for (int i = top; i >= 0; i--) {
            cout << "  " << actions[i];
            if (i == top) cout << "   <-- TOP";
            cout << endl;
        }
    }
};

int main() {
    UndoStack editor;

    cout << "=== Step 1: Push actions ===" << endl;
    editor.push("Type \"Hello\"");
    editor.push("Type \"World\"");
    editor.push("Add \"!\"");
    editor.push("Delete \"!\"");

    cout << "\n=== Step 2: All actions (TOP to bottom) ===" << endl;
    editor.display();

    cout << "\n=== Step 3: Two POP operations (Undo x2) ===" << endl;
    editor.undo();
    editor.undo();

    cout << "\n=== Step 4: Current TOP action ===" << endl;
    editor.peek();

    cout << "\n=== Step 5: Remaining actions ===" << endl;
    editor.display();

    return 0;
}
