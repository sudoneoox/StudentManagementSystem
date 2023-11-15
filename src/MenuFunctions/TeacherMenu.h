#ifndef TEACHERMENU_H
#define TEACHERMENU_H

using namespace std;
#include <iostream>

#include "../include/ClassDeclarations/teacher.h"
#include "../include/filemanipulation.h"
#include "../../include/Menu.h"

void TeacherMenu();

void TeacherMenu()
{
    char input;
    while (cin >> input)
    {
        if (input == '1')
        {
            Teacher t = Teacher();
            cin >> t;
            PrintMenuOption("Teacher Menu", "teacherMenuOptions");
        }
        if (input == '5')
        {
            break;
        }
    }
}
#endif // !TEACHERMENU_H