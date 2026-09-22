#include <iostream>
using namespace std;

int main()
{
    int parking[4][5] = {
        {1, 0, 1, 0, 1},
        {0, 1, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 1, 1}
    };

    int occupied = 0;
    int empty = 0;

    cout << "Parking Layout:\n\n";

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << parking[i][j] << "\t";

            if (parking[i][j] == 1)
                occupied++;
            else
                empty++;
        }

        cout << endl;
    }

    cout << "\nTotal Occupied Spaces: " << occupied << endl;
    cout << "Total Empty Spaces: " << empty << endl;

    int row, column;

    cout << "\nEnter row number (0-3): ";
    cin >> row;

    cout << "Enter column number (0-4): ";
    cin >> column;

    if (parking[row][column] == 0)
        cout << "Selected parking space is Available." << endl;
    else
        cout << "Selected parking space is Occupied." << endl;

    cout << "\nTotal Parking Capacity: 20" << endl;
    cout << "Current Occupancy: " << occupied << endl;

    return 0;
}