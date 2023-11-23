#ifndef FILEMANIPULATION_H
#define FILEMANIPULATION_H

#include <iostream>
#include "../include/ClassDeclarations/student.h"
#include "../include/ClassDeclarations/class.h"
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;


// !Global Variables
extern map<string, Teacher*> allTeachers; // map of all the teachers in the program
extern map<string, Student*> allStudents; // map of all the students in the program
extern map<string, Class*> allClasses; // map of all the classes in the program 

// !Deseriaalization Section
void from_json(const json& j, Student& s); // converts json to student object
void from_json(const json& j, Class& c); // converts json to class object
void from_json(const json& j, Teacher& t); // converts json to teacher object

// !Serializatoin Section
void to_jsonFromStudent(json& j, Student& s); // converts student object to json
void to_jsonFromClass(json& j, Class& c); // converts class object to json
void to_jsonFromTeacher(json& j, Teacher& t); // converts teacher object to json

//! Data Preloading Functions whenever the program starts 
void preloadDataJsonFile(string option, string filename); // loads data from json file

//! File Manipulation Section

void addDataToJsonFile(const string& filePath, Student& s); // adds data to json file
void addDataToJsonFileFromClass(const string& filePath, Class& c);
void addDataToJsonFile(const string& filePath, Teacher& t);


//! Helper Functions
void createJsonFile(const string& filePath); // creates json file
json loadDataFromFile(const string& filename); // loads data from json file
void saveJsonToFile(const json& data, const string& filePath); // saves data to json file
bool isJsonFileEmpty(string& filename); // checks if json file is empty
map<string, Student*> createStudentObjectsFromJsonFile(string& filename); // creates student objects from json file
map<string, Class*> createClassObjectsFromJsonFile(string& filename); // creates class objects from json file
map<string, Teacher*> createTeacherObjectsFromJsonFile(string& filename); // creates teacher objects from json file

// finders
Student* findStudentByID(map<string, Student*>& allStudents, string studentID); // finds student by ID
Teacher* findTeacherByID(map<string, Teacher*>& allTeachers, string teacherID); // finds teacher by ID
Class* findClassByID(map<string, Class*>& allClasses, string classID); // finds class by ID

#endif // !FILEMANIPULATION_H