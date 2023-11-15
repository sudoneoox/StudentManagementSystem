#include "../include/ClassDeclarations/teacher.h"

using namespace std;

Teacher::Teacher()
{
    this->name = "";
    this->email = "";
    this->ID = "";
    vector<Class *> subjectsTaught;
};
Teacher::Teacher(string name, string email, string id)
{
    this->name = name;
    this->email = email;
    this->ID = id;
    vector<Class *> subjectsTaught;
};
Teacher::Teacher(const Teacher &other)
{
    this->name = other.name;
    this->email = other.email;
    this->ID = other.ID;
    this->subjectsTaught = other.subjectsTaught;
};
vector<Class *> Teacher::GetSubjectsTaught() const
{
    return subjectsTaught;
};
void Teacher::UpdateSubjects(vector<Class *> newSubjects)
{
    subjectsTaught = newSubjects;
};
void Teacher::EnterGrade(Assignment *assignment, Student *student, double grade)
{
    cout << "still need to complete";
};
map<Student *, string> GenerateAttendance(string startDate, string endDate){

};

Teacher &Teacher::operator=(const Teacher &RHS)
{
    if (this != &RHS)
    {
        this->name = RHS.name;
        this->email = RHS.email;
        this->ID = RHS.ID;
        this->subjectsTaught = RHS.subjectsTaught;
    }

    return *this;
};

istream &operator>>(istream &IN, Teacher &teacher)
{
    cout << "Enter Name: ";
    IN >> teacher.name;
    cout << "Enter Email: ";
    IN >> teacher.email;
    cout << "Enter ID: ";
    IN >> teacher.ID;
    return IN;
};