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


void updateClassInfo(Class& c); // updates the class info
void generateAttendanceReport(Class& c); // generates an attendance report from a start date to end date for a class
void enterExamGrades(Class& c); // this function enters exam grades for a class depending on the exams that are set in that class
void getOverallClassAverage(Class& c); // this function gets the overall class average for all the students in the class
void addAssesment(Class& c);
void addExam(Class& c);
void addAssignment(Class& c);


void ClassMenu(Class& c) {
    string className = c.getName(); // gets the class name
    string teacherName = c.getTeacher()->getName(); // gets the teacher name
    PrintMenuOption("Class Menu | " + teacherName + " | " + className, "classMenuOptions"); // prints the class menu options WITH the teacher name and class name
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
            getOverallClassAverage(c);
            PrintMenuOption("Class Menu | " + teacherName + " | " + className, "classMenuOptions");
        }
        else if (input == "5") {
            addAssesment(c);
            PrintMenuOption("Class Menu | " + teacherName + " | " + className, "classMenuOptions");
        }
        else if (input == "6") {
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


void addAssesment(Class& c) {
    while (true) {
        cout << "Would you like to add an assignment or an exam (0 to exit)? (a/e) \n";
        string input;
        cin >> input;
        if (input == "a" || input == "A" || input == "assignment" || input == "Assignment") {
            addAssignment(c);
            break;
        }
        else if (input == "e" || input == "E" || input == "exam" || input == "Exam") {
            addExam(c);
            break;
        }
        else if (input == "0") {
            return;
        }
        else {
            cout << "Invalid Input\n";
        }
    }
    return;
}

void addExam(Class& c) {
    Exam* exam = new Exam();
    while (true) {
        cout << "Enter the name of the exam (0 to exit): ";
        if (cin.peek() == '\n') cin.ignore(); // ignores the newline character if it exists
        string name;
        getline(cin, name);
        if (name == "0") {
            delete exam; // deletes the exam pointer if the user wants to exit
            return;
        }
        cout << "Enter the ID of the new Exam (0 to exit): ";
        if (cin.peek() == '\n') cin.ignore(); // ignores the newline character if it exists
        string ID;
        getline(cin, ID);
        if (ID == "0") {
            delete exam; // deletes the exam pointer if the user wants to exit
            return;
        }
        exam->setName(name);
        exam->setID(ID);
        c.addExam(exam);
        addDataToJsonFileFromClass("../Data/class.json", c); // updates the class json file
        cout << "Exam added successfully\n";
        return;
    }
    return;
}

void addAssignment(Class& c) {
    Assignment* assignment = new Assignment();
    while (true) {
        cout << "Enter the name of the assignment (0 to exit): ";
        if (cin.peek() == '\n') cin.ignore(); // ignores the newline character if it exists
        string name;
        getline(cin, name);
        if (name == "0") {
            delete assignment; // deletes the assignment pointer if the user wants to exit
            return;
        }
        cout << "Enter the ID of the new assignment (0 to exit): ";
        string ID;
        if (cin.peek() == '\n') cin.ignore(); // ignores the newline character if it exists
        getline(cin, ID);
        if (ID == "0") {
            delete assignment; // deletes the assignment pointer if the user wants to exit
            return;
        }
        assignment->setName(name);
        assignment->setID(ID);
        c.addAssignment(assignment);
        addDataToJsonFileFromClass("../Data/class.json", c); // updates the class json file
        cout << "Assignment added successfully\n";
        break;
    }
    return;
}


// this function enters exam grades for a class depending on the exams that are set in that class
void enterExamGrades(Class& c) {
    while (true) {
        cout << "Enter the ID of the exam you would like to enter grades for (0 to exit): ";
        for (auto& [examID, examPtr] : c.getExams()) { // iterates through the exams in the class
            cout << endl << examID << ": " << examPtr->getName() << endl; // prints the exam ID and name
        }
        string examID;
        cin >> examID;
        if (examID == "0") {
            return;
        }

        auto exam = c.getExam(examID); // gets the exam from the class
        if (!exam) {
            cout << "Invalid Exam ID. Please try again." << endl;
            return;
        }

        cout << "Entering grades for Exam: " << exam->getName() << endl;
        for (auto& [studentID, studentPtr] : c.getStudents()) { // iterates through the students in the class
            cout << "Enter the grade for " << studentPtr->getName() << " (ID: " << studentID << "): ";
            double grade;
            cin >> grade;
            string ID = studentPtr->getID();
            c.setStudentGradeForExam(ID, examID, grade); // sets the grade for the student in the class
            studentPtr->setGradeForExam(examID, grade);  // sets the grade for the student in the student class
            addDataToJsonFile("../Data/students.json", *studentPtr); // updates the student json file
        }

        addDataToJsonFileFromClass("../Data/class.json", c); // updates the class json file
        cout << "Exam grades entered successfully." << endl;
        break;
    }
    return;
}

// this function gets the overall class average for all the students in the class
void getOverallClassAverage(Class& c) {
    double totalGPA = 0.0; // total GPA of all the students in the class
    int count = 0; // number of students in the class
    for (auto& [studentID, studentPtr] : c.getStudents()) { // iterates through the students in the class
        double studentGPA = c.calculateTotalGrade(studentID); // gets the total grade for the student
        if (studentGPA >= 0) { // if the student has a grade
            totalGPA += studentGPA; // adds the student's grade to the total GPA
            count++; // increments the number of students in the class
        }
    }
    double overallGPA = count > 0 ? totalGPA / count : 0.0; // calculates the overall GPA for the class
    cout << "Overall Class GPA for " << c.getName() << ": " << overallGPA << endl; // prints the overall GPA for the class
}



// generates an attendance report from a start date to end date for a class
void generateAttendanceReport(Class& c) {
    cout << "Would you like to generate an attendance report for this class? (y/n)\n";
    string input;
    cin >> input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignores the newline character
    if (input == "y" || input == "Y") {
        cout << "Enter the Start Data (MM/DD/YYYY): ";
        string startDate;
        getline(cin, startDate); // gets the start date
        cout << "\nEnter the End Data (MM/DD/YYYY): ";
        string endDate;
        getline(cin, endDate); // gets the end date
        cout << "\nAttendance Report for " << c.getName() << " from " << startDate << " to " << endDate << endl;

        for (auto& [studentID, studentPtr] : c.getStudents()) {
            cout << studentPtr->getName() << "\n" << studentPtr->GetAttendanceRecordRange(startDate, endDate) << endl; // prints the attendance record for the student
        }
    }
    else {
        cout << "Not generating an attendance report\n";
        return;
    }
}

// this function updates the class info
void updateClassInfo(Class& c) {
    cout << "Would you like to change the name of this class? (y/n)\n";
    string input;
    cin >> input;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ignores the newline character
    if (input == "y" || input == "Y") {
        cout << "Enter the new name of the class: ";
        string newName;
        getline(cin, newName);
        c.setName(newName); // sets the new name of the class
        addDataToJsonFileFromClass("../Data/class.json", c); // updates the class json file
        addDataToJsonFile("../Data/teachers.json", *c.getTeacher()); // updates the teacher json file
        for (auto s = c.getStudents().begin(); s != c.getStudents().end(); s++) {
            addDataToJsonFile("../Data/students.json", *s->second); // updates the student json file for all the students that have that class
        }
    }
    else {
        cout << "Not changing the name of the class\n";
        return;
    }
}

#endif // !CLASSMENU_H