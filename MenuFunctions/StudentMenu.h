#ifndef STUDENTMENU_H
#define STUDENTMENU_H
using namespace std;
#include <iostream>
#include <string>
#include <vector>
#include "../H/student.h"
#include "../H/filemanipulation.h"
#include <chrono>

// #include "../H/attendanceStatus.h"
// #include "../H/dateStruct.h"
string currentDate();
void studentMenu(vector<Student> &students);
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
            addDataToJsonFile("Data\student.json", student);
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
string currentDate()
{
    // get current date
    auto now = chrono::system_clock::now();

    time_t now_c = chrono::system_clock::to_time_t(now); // convert to c time

    tm now_tm = *localtime(&now_c); // convert to tm struct for formatting

    ostringstream dateStream;
    dateStream << put_time(&now_tm, "%m/%d/%Y"); // format month/day/year
    return dateStream.str();
}
bool validationCheck(vector<Student> students, int &idx)
{
    cout << "Enter your StudentID: ";
    string ID;
    cin >> ID;
    idx = 0;
    for (int i = 0; i < students.size(); i++)
    {
        if (students.at(i).getID() == ID)
        {
            idx = i;
            return true;
        }
    }
    return false;
}

#endif // !STUDENTMENU_H