#ifndef FILEMANIPULATION_H
#define FILEMANIPULATION_H

#include <iostream>
#include "../include/ClassDeclarations/student.h"
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;


// !Global
// extern vector<Student> students;
// extern vector<Teacher> teachers;
extern map<string, Teacher*> allTeachers;
extern map<string, Student*> allStudents;
extern map<string, Class*> allClasses;

// !Deseriaalization Section
void from_json(const json& j, Student& s);
void from_json(const json& j, Class& c);
void from_json(const json& j, Teacher& t);

// !Serializatoin Section
void to_jsonFromStudent(json& j, Student& s);
void to_jsonFromClass(json& j, Class& c);
void to_jsonFromTeacher(json& j, Teacher& t);

//! Data Preloading Functions whenever the program starts
void preloadDataJsonFile(string option, string filename);

//! File Manipulation Section

void addDataToJsonFile(const string& filePath, Student& s);
void(const string& filePath, Class& c);
void addDataToJsonFile(const string& filePath, Teacher& t);


//! Helper Functions
void createJsonFile(const string& filePath);
json loadDataFromFile(const string& filename);
void saveJsonToFile(const json& data, const string& filePath);
bool isJsonFileEmpty(string& filename);
map<string, Student*> createStudentObjectsFromJsonFile(string& filename);
map<string, Class*> createClassObjectsFromJsonFile(string& filename);
map<string, Teacher*> createTeacherObjectsFromJsonFile(string& filename);

// finders
Student* findStudentByID(map<string, Student*>& allStudents, string studentID);
Teacher* findTeacherByID(map<string, Teacher*>& allTeachers, string teacherID);
Class* findClassByID(map<string, Class*>& allClasses, string classID);

#endif // !FILEMANIPULATION_H