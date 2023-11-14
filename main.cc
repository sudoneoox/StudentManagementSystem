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

int main()
{
    string StudentJSON, ClassJSON, TeacherJSON;
    vector<Student> students;
    vector<Teacher> teachers;
    map<string, Class *> allClasses;

    !isJsonFileEmpty(StudentJSON) ? StudentJSON = "Data\student.json" : StudentJSON = "Data\student.json";
    !isJsonFileEmpty(ClassJSON) ? ClassJSON = "Data\class.json" : ClassJSON = "Data\class.json";
    !isJsonFileEmpty(TeacherJSON) ? TeacherJSON = "Data\Teacher.json" : TeacherJSON = "Data\Teacher.json";

    students = crateStudentObjectsFromJsonFile(StudentJSON);
    allClasses = createClassObjectsFromJsonFile(ClassJSON);

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
