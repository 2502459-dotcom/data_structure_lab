#include <iostream>
#include <string>
using namespace std;

// Array-based Stack storing visited web pages
class BrowserHistory {
private:
    static const int MAX = 10;
    string pages[MAX];
    int top;

public:
    BrowserHistory() : top(-1) {}

    bool isEmpty() const { return top == -1; }
    bool isFull() const { return top == MAX - 1; }

    void push(const string& page) {
        if (isFull()) {
            cout << "History full! Cannot visit: " << page << endl;
            return;
        }
        pages[++top] = page;
        cout << "Visited: " << page << endl;
    }

    void pop() {
        if (isEmpty()) {
            cout << "No history to go back to." << endl;
            return;
        }
        cout << "Back pressed. Removed page: " << pages[top--] << endl;
    }

    void peek() const {
        if (isEmpty()) cout << "Current page: (none)" << endl;
        else cout << "Current TOP page: " << pages[top] << endl;
    }

    void display() const {
        if (isEmpty()) { cout << "(history is empty)" << endl; return; }
        for (int i = top; i >= 0; i--) {
            cout << "  " << pages[i];
            if (i == top) cout << "   <-- TOP";
            cout << endl;
        }
    }
};

int main() {
    BrowserHistory browser;

    cout << "=== Step 1: Push visited pages ===" << endl;
    browser.push("Google");
    browser.push("YouTube");
    browser.push("Facebook");
    browser.push("GitHub");

    cout << "\n=== Step 2: All pages (TOP to bottom) ===" << endl;
    browser.display();

    cout << "\n=== Step 3: POP (Back button) ===" << endl;
    browser.pop();

    cout << "\n=== Step 4: Current TOP page ===" << endl;
    browser.peek();

    cout << "\n=== Step 5: Remaining browsing history ===" << endl;
    browser.display();

    return 0;
}
