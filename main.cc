#include "./H/assignment.h"
#include "./H/class.h"
#include "./H/people.h"
#include "./H/student.h"
#include "./H/teacher.h"
#include "./H/Menu.h"
#include "./H/filemanipulation.h"
#include "./MenuFunctions/StudentMenu.h"
#include "./MenuFunctions/TeacherMenu.h"
#include "./MenuFunctions/ClassMenu.h"

#include <iostream>
#include <unordered_map>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

void PrintMenuOption(string name, string menu);
map<string, Class *> createClassObjectsFromJsonFile(string &filename);

int main()
{
    string StudentJSON = "Data\student.json";
    string ClassJSON = "Data\class.json";

    vector<Student> students;
    vector<Teacher> teachers;
    map<string, Class *> allClasses;
    if (!isJsonFileEmpty(ClassJSON))
    {
        cout << "class data not empty\n";
        allClasses = createClassObjectsFromJsonFile(ClassJSON);
    }
    if (!isJsonFileEmpty(StudentJSON))
    {
        cout << "student data not empty\n";
        students = crateStudentObjectsFromJsonFile(StudentJSON);
    }

    char input;
    PrintMenuOption("Student Management System", "mainMenuOptions");
    while (cin >> input)
    {
        if (input == '1')
        {
            int idx;
            bool correctID = validationCheck(students, idx);
            if (correctID)
            {
                string name = students.at(idx).getName();
                PrintMenuOption("Student Menu | " + name, "studentMenuOptions");
                studentMenu(students.at(idx));
                PrintMenuOption("Student Management System", "mainMenuOptions");
            }
            else
            {
                cout << "Invalid ID\n";
                correctID = validationCheck(students, idx);
            }
        }
        else if (input == '2')
        {
            PrintMenuOption("Teacher Menu", "teacherMenuOptions");
            TeacherMenu();
        }
        else if (input == '3')
        {
            PrintMenuOption("Class Menu", "classMenuOptions");
            ClassMenu(allClasses);
        }
        else if (input == '4')
        {
            cout << "Exiting program\n";
            break;
        }
        else
        {
            cout << "Invalid input Please Try Again\n ";
            PrintMenuOption("Student Management System", "mainMenuOptions");
        }
    }
    return 0;
}
