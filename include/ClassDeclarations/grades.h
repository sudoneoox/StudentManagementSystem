#ifndef GRADE_H
#define GRADE_H
#include <string>
using namespace std;
#include <map>


class Grade // abstract class for assignment and exam
{
protected:
    string name;
    map<string, map<string, double>> studentGrades; // studentID, assignment/exam ID, grade
    string ID;
public:
    Grade() : name(""), ID("") {};
    Grade(string name, string ID) : name(name), ID(ID) {};

    //setters
    void setGrade(string studentID, string assignmentID, double grade) { // sets grade for assignment
        if (studentGrades.find(studentID) != studentGrades.end()) { // if studentID exists
            studentGrades [studentID][assignmentID] = grade; // set grade
        }
        else {
            studentGrades [studentID] = map<string, double>(); // create new map for studentID
            studentGrades [studentID][assignmentID] = grade; // set grade
        }
    }

    //getters
    double getGrade(string studentID, string assignmentID) {
        if (studentGrades.find(studentID) != studentGrades.end() &&
            studentGrades [studentID].find(assignmentID) != studentGrades [studentID].end()) {
            return studentGrades [studentID][assignmentID];
        }
        return -1;
    }
    string getName() {
        return name;
    }
    map<string, map<string, double>>& getAllGrades() {
        return studentGrades;
    }

    string getID() {
        return ID;
    }
};


#endif // !GRADE_H