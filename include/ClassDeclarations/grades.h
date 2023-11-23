#ifndef GRADE_H
#define GRADE_H
#include <string>
using namespace std;
#include <map>


class Grade
{
protected:
    string name;
    map<string, map<string, double>> studentGrades; // studentID, assignment/exam ID, grade
    string ID;
public:
    Grade() : name(""), ID("") {};
    Grade(string name, string ID) : name(name), ID(ID) {};
    void setGrade(string studentID, string assignmentID, double grade) {
        if (studentGrades.find(studentID) != studentGrades.end()) {
            studentGrades [studentID][assignmentID] = grade;
        }
        else {
            studentGrades [studentID] = map<string, double>();
            studentGrades [studentID][assignmentID] = grade;
        }
    }

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