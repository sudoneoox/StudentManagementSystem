#include "../include/ClassDeclarations/assignment.h"
#include "../include/ClassDeclarations/class.h"
#include "../include/ClassDeclarations/people.h"
#include "../include/ClassDeclarations/student.h"
#include "../include/ClassDeclarations/teacher.h"
#include "../include/filemanipulation.h"
#include "../include/Menu.h"

#include "./MenuFunctions/StudentMenu.h"
#include "./MenuFunctions/TeacherMenu.h"
#include "./MenuFunctions/ClassMenu.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

vector<Student> students;
vector<Teacher> teachers;
map<string, Class *> allClasses;

int main()
{

    PreloadData("student", "../Data/students.json");
    PreloadData("teacher", "../Data/teachers.json");
    PreloadData("class", "../Data/class.json");

    cout << students.size() << "in main\n"
         << endl;
    cout << teachers.size() << endl;

    char input;
    PrintMenuOption("Student Management System", "mainMenuOptions");
    while (cin >> input)
    {
        if (input == '1')
        {
            int idx;
            cout << students.at(0);
            bool correctID = validationCheck(students, idx);
            if (correctID)
            {
                string name = students.at(idx).getName();
                PrintMenuOption("Student Menu | " + name, "studentMenuOptions");
                studentMenu(students.at(idx));
                PrintMenuOption("Student Management System", "mainMenuOptions");
            }
            else if (!correctID)
            {
                PrintMenuOption("Student Management System", "mainMenuOptions");
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
            cout << "Invalid option Please Try Again\n ";
            PrintMenuOption("Student Management System", "mainMenuOptions");
        }
    }
    return 0;
}
