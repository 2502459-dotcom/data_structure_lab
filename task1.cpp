#include <iostream>
using namespace std;

int main()
{
    int marks[6][4] = {
        {78, 85, 90, 88},
        {65, 72, 80, 75},
        {90, 92, 88, 95},
        {70, 68, 75, 80},
        {85, 80, 84, 86},
        {60, 75, 70, 72}
    };

    string subjects[4] = {
        "English", "Mathematics", "Programming", "AI"
    };

    int highestStudent = 0;
    int highestTotal = 0;

    cout << "Student Marks Table:\n\n";

    cout << "Student\tEnglish\tMath\tProgramming\tAI\n";

    for (int i = 0; i < 6; i++)
    {
        cout << "S" << i + 1 << "\t";

        int total = 0;

        for (int j = 0; j < 4; j++)
        {
            cout << marks[i][j] << "\t";
            total += marks[i][j];
        }

        double average = total / 4.0;

        cout << "\nTotal = " << total;
        cout << ", Average = " << average << "\n\n";

        if (total > highestTotal)
        {
            highestTotal = total;
            highestStudent = i;
        }
    }

    cout << "Highest Marks in Each Subject:\n";

    for (int j = 0; j < 4; j++)
    {
        int highest = marks[0][j];

        for (int i = 1; i < 6; i++)
        {
            if (marks[i][j] > highest)
            {
                highest = marks[i][j];
            }
        }

        cout << subjects[j] << ": " << highest << endl;
    }

    cout << "\nStudent with Highest Total Marks: S"
         << highestStudent + 1 << endl;

    cout << "Highest Total: " << highestTotal << endl;

    return 0;
}