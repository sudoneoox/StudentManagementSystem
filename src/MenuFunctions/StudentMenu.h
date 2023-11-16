#ifndef STUDENTMENU_H
#define STUDENTMENU_H

using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include <chrono>

#include "../../include/ClassDeclarations/student.h"
#include "../../include/filemanipulation.h"
#include "../../include/Menu.h"

string currentDate();
void studentMenu(Student &student);
bool validationCheck(vector<Student> students, int &idx);

void studentMenu(Student &student)
{
    char input;
    while (cin >> input && input != '7')
    {
        if (input == '1')
        {
            cout << "Showing Information For " << student.getName() << endl;
            cout << student << endl;
            PrintMenuOption("Student Menu", "studentMenuOptions");
        }
        else if (input == '2')
        {
            cout << "You will now be marked present for today's date "
                 << currentDate() << '\n';
            student.MarkAttendance(currentDate(), "PRESENT");
            addDataToJsonFile("../Data/students.json", student);
            PrintMenuOption("Student Menu", "studentMenuOptions");
        }
        else if (input == '3')
        {
            cout << "Displaying Available Classes\n";
        }
        else if (input == '7')
        {
            cout << "Exiting Student Menu\n";
            PrintMenuOption("Main Menu", "mainMenuOptions");
            break;
        }
    }
}

string currentDate() // function to get the current date in the format of month/day/year thank you stack exchange
{
    auto now = chrono::system_clock::now();

    time_t now_c = chrono::system_clock::to_time_t(now); // convert to c time

    tm now_tm = *localtime(&now_c); // convert to tm struct for formatting

    ostringstream dateStream;
    dateStream << put_time(&now_tm, "%m/%d/%Y"); // format month/day/year
    return dateStream.str();
}

bool validationCheck(vector<Student> students, int &idx) // function to check if the student ID is valid returns idx of student if true
{
    while (true)
    {
        cout << "Enter your StudentID or 0 to go back: ";
        string ID;
        cin >> ID;

        if (ID == "0")
        {
            return false; // Return false if user enters 0, indicating to go back
        }

        for (int i = 0; i < students.size(); i++)
        {
            if (students.at(i).getID() == ID)
            {
                idx = i;     // Set index if ID is found
                return true; // ID is valid, return true
            }
        }

        cout << "Invalid ID Try Again or Enter 0 to go back to the portal\n";
        // The loop will continue, prompting the user again
    }
}

#endif // !STUDENTMENU_H