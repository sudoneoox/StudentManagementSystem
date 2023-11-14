#ifndef FILEMANIPULATION_H
#define FILEMANIPULATION_H

#include <iostream>
#include "./student.h"
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

void addDataToJsonFile(const string &filePath, Student &s);
void addDataToJsonFileFromClass(const string &filePath, Class *c);
void createJsonFile(const string &filePath);
json loadDataFromFile(const string &filename);
void to_json(json &j, Student s);
void to_jsonFromClass(json &j, Class *c);
void from_json(const json &j, Student &s);
bool isJsonFileEmpty(string &filename);
vector<Student> crateStudentObjectsFromJsonFile(string &filename);
map<string, Class *> createClassObjectsFromJsonFile(string &filename);

#endif // !FILEMANIPULATION_H