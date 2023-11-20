#ifndef GRADE_H
#define GRADE_H
#include <string>
using namespace std;
#include <map>


class Grade
{
protected:
    string name;
    map<string, double> grades;
    string ID;
public:
    Grade() : name(""), ID("") {};
    Grade(string name, string ID) : name(name), ID(ID) {};
    void setGrade(string studentID, double grade) {
        grades [studentID] = grade;
    }
    double getGrade(string studentID) {
        auto it = grades.find(studentID);
        if (it != grades.end()) {
            return it->second;
        }
        return -1;
    }
    string getName() {
        return name;
    }
    map<string, double> getGrades() {
        return grades;
    }
    string getID() {
        return ID;
    }


};


#endif // !GRADE_H