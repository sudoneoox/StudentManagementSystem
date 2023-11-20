#ifndef GRADE_H
#define GRADE_H
#include <string>
using namespace std;


class Grade
{
protected:
    string name;
    string grade;
    string ID;
public:
    Grade() : name(""), grade(""), ID("") {};
    Grade(string name, string grade, string ID) : name(name), grade(grade), ID(ID) {};
    void setName(string name) { this->name = name; };
    void setGrade(string grade) { this->grade = grade; };
    void setID(string ID) { this->ID = ID; }
    string getName() { return name; };
    string getGrade() { return grade; };
    string getID() { return ID; }
};


#endif // !GRADE_H