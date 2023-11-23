#ifndef CLASSMENU_H
#define CLASSMENU_H

#include <iostream>
#include <string>
#include <map>

#include "../../include/ClassDeclarations/class.h"
#include "../../include/filemanipulation.h"
#include "../../include/Menu.h"
#include "../../include/ClassDeclarations/teacher.h"

using namespace std;


void updateClassInfo(Class& c);
void generateAttendanceReport(Class& c);
void enterExamGrades(Class& c);
void getOverallClassGPA(Class& c);

void ClassMenu(Class& c) {
    string className = c.getName();
    string teacherName = c.getTeacher()->getName();
    PrintMenuOption("Class Menu | " + teacherName + " | " + className, "classMenuOptions");
    string input;
    while (true || cin >> input) {
        cout << "Enter 0 to go back to the teacher menu at any time\n";
        cin >> input;
        if (input == "0") {
            return;
        }
        else if (input == "1") {
            updateClassInfo(c);
            PrintMenuOption("Class Menu | " + teacherName + " | " + className, "classMenuOptions");
        }
        else if (input == "2") {
            generateAttendanceReport(c);
            PrintMenuOption("Class Menu | " + teacherName + " | " + className, "classMenuOptions");
        }
        else if (input == "3") {
            enterExamGrades(c);
            PrintMenuOption("Class Menu | " + teacherName + " | " + className, "classMenuOptions");
        }
        else if (input == "4") {
            getOverallClassGPA(c);
            PrintMenuOption("Class Menu | " + teacherName + " | " + className, "classMenuOptions");
        }
        else if (input == "5") {
            cout << "Leaving Class Menu\n";
            break;
        }
        else {
            cout << "Invalid Input\n";
            PrintMenuOption("Class Menu | " + teacherName + " | " + className, "classMenuOptions");
        }

    }
    return;
}


void enterExamGrades(Class& c) {
    while (true) {
        cout << "Enter the ID of the exam you would like to enter grades for (0 to exit): ";
        string examID;
        cin >> examID;
        if (examID == "0") {
            return;
        }

        auto exam = c.getExam(examID);
        if (!exam) {
            cout << "Invalid Exam ID. Please try again." << endl;
            return;
        }

        cout << "Entering grades for Exam: " << exam->getName() << endl;
        for (auto& [studentID, studentPtr] : c.getStudents()) {
            cout << "Enter the grade for " << studentPtr->getName() << " (ID: " << studentID << "): ";
            double grade;
            cin >> grade;
            string ID = studentPtr->getID();
            c.setStudentGradeForExam(ID, examID, grade);
            studentPtr->setGradeForExam(examID, grade);
            addDataToJsonFile("../Data/students.json", *studentPtr);
        }

        addDataToJsonFileFromClass("../Data/class.json", c);
        cout << "Exam grades entered successfully." << endl;
        break;
    }
    return;
}

void getOverallClassGPA(Class& c) {
    double totalGPA = 0.0;
    int count = 0;
    for (auto& [studentID, studentPtr] : c.getStudents()) {
        double studentGPA = c.calculateTotalGrade(studentID);
        if (studentGPA >= 0) {
            totalGPA += studentGPA;
            count++;
        }
    }
    double overallGPA = count > 0 ? totalGPA / count : 0.0;
    cout << "Overall Class GPA for " << c.getName() << ": " << overallGPA << endl;
}




void generateAttendanceReport(Class& c) {
    cout << "Would you like to generate an attendance report for this class? (y/n)\n";
    string input;
    cin >> input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (input == "y" || input == "Y") {
        cout << "Enter the Start Data (MM/DD/YYYY): ";
        string startDate;
        getline(cin, startDate);
        cout << "\nEnter the End Data (MM/DD/YYYY): ";
        string endDate;
        getline(cin, endDate);
        cout << "\nAttendance Report for " << c.getName() << " from " << startDate << " to " << endDate << endl;

        for (auto& [studentID, studentPtr] : c.getStudents()) {
            cout << studentPtr->getName() << "\n" << studentPtr->GetAttendanceRecordRange(startDate, endDate) << endl;
        }
    }
    else {
        cout << "Not generating an attendance report\n";
        return;
    }
}

void updateClassInfo(Class& c) {
    cout << "Would you like to change the name of this class? (y/n)\n";
    string input;
    cin >> input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (input == "y" || input == "Y") {
        cout << "Enter the new name of the class: ";
        string newName;
        getline(cin, newName);
        c.setName(newName);
        addDataToJsonFileFromClass("../Data/class.json", c);
        addDataToJsonFile("../Data/teachers.json", *c.getTeacher());
        for (auto s = c.getStudents().begin(); s != c.getStudents().end(); s++) {
            addDataToJsonFile("../Data/students.json", *s->second);
        }
    }
    else {
        cout << "Not changing the name of the class\n";
        return;
    }
}

#endif // !CLASSMENU_H