#include "../include/ClassDeclarations/teacher.h"

using namespace std;

Teacher::Teacher() {
    this->name = "";
    this->email = "";
    this->ID = "";
    map<string, Class*> subjectsTaught;
};

void Teacher::addSubject(Class* subject) {
    subjectsTaught.insert(pair<string, Class*>(subject->getID(), subject));
};
void Teacher::setSubjectsTaught(map<string, Class*> subjectsTaught) {
    this->subjectsTaught = subjectsTaught;
};

Teacher::Teacher(string name, string email, string id) {
    this->name = name;
    this->email = email;
    this->ID = id;
    map<string, Class*> subjectsTaught;
};
Teacher::Teacher(const Teacher& other) {
    this->name = other.name;
    this->email = other.email;
    this->ID = other.ID;
    this->subjectsTaught = other.subjectsTaught;
};
Teacher::~Teacher() {
    map<string, Class*>::iterator iter;
    for (iter = subjectsTaught.begin(); iter != subjectsTaught.end(); iter++)
    {
        delete iter->second;
    }
};
map<string, Class*> Teacher::GetSubjectsTaught() const {
    return subjectsTaught;
};
void Teacher::UpdateSubjects(map<string, Class*> newSubjects) {
    subjectsTaught = newSubjects;
};
void Teacher::EnterGrade(Assignment* assignment, Student* student, double grade) {
    cout << "still need to complete";
};

map<Student*, string> GenerateAttendance(string startDate, string endDate) {
    cout << "still need to complete";
};

Teacher& Teacher::operator=(const Teacher& RHS) {
    if (this != &RHS)
    {
        this->name = RHS.name;
        this->email = RHS.email;
        this->ID = RHS.ID;
        this->subjectsTaught = RHS.subjectsTaught;
    }

    return *this;
};

istream& operator>>(istream& IN, Teacher& teacher) {
    cout << "Enter Name: ";
    IN >> teacher.name;
    cout << "Enter Email: ";
    IN >> teacher.email;
    cout << "Enter ID: ";
    IN >> teacher.ID;
    return IN;
};