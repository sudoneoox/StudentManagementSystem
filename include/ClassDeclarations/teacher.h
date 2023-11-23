#ifndef TEACHER_H
#define TEACHER_H

// #include <vector>
#include <string>
#include <map>

#include "./class.h"
#include "./people.h"
#include "./assignment.h"
#include "./student.h"

using namespace std;

class Class;
class Student;

class Teacher : public People
{
private:
    map<string, Class*> subjectsTaught; // classID, class pointer

public:
    //constructors and destructors
    Teacher();
    Teacher(string name, string email, string id);
    Teacher(const Teacher& other);
    ~Teacher(); // destructor destroys all classes taught by teacher

    //getters
    map<string, Class*> GetSubjectsTaught() const; // returns subjects taught


    //setters
    void setSubjectsTaught(map<string, Class*> subjectsTaught); // sets subjects taught
    void addSubject(Class* subject); // adds singular subject to subjects taught


    //methods
    void printSubjectsTaught(); // prints subjects taught

    //operator overloading
    Teacher& operator=(const Teacher& RHS); // assignment operator overloading
    friend istream& operator>>(istream& IN, Teacher& teacher); // input operator overloading
    friend ostream& operator<<(ostream& OUT, Teacher& teacher); // output operator overloading displays subjects taught

};

#endif // !TEACHER_H