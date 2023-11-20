#include "../include/filemanipulation.h"

// !! Serialization Section
// serialize object to json
void to_jsonFromStudent(json& j, Student& s) {
    j = {
        {"name", s.getName()},
        {"email", s.getEmail()},
        {"ID", s.getID()},
        {"classSchedule", json::object()},
        {"attendanceRecord", s.GetAllAttendanceRecords()}
    };
    for (auto& classSchedule : s.getClassSchedule()) {
        // classSchedule.first is the classID and classSchedule.second is the class pointer format is {classID: className}
        j ["classSchedule"][classSchedule.first] = classSchedule.second->getName();
    }
    // cout << j.dump(4) << "\n inside to_student json" << endl;
}

void to_jsonFromClass(json& j, Class& c) {
    // cout << "inside to_jsonFromClass\n";
    j = {
        {"name", c.getName()},
        {"ID", c.getClassID()},
        {"students",json::object()}, // {studentID: studentName}
        {"teacher", json::object()} // {teacherID: teacherName}
    };
    if (c.getTeacher() != nullptr) {
        j ["teacher"][c.getTeacher()->getID()] = c.getTeacher()->getName();

    }
    for (auto& student : c.getStudents()) {
        // student.first is the studentID and student.second is the student pointer format is {studentID: studentName}
        j ["students"][student.first] = student.second->getName();
    }
    // cout << "good here\n";
    // cout << j.dump(4) << "\n inside to_class json" << endl;
}

void to_jsonFromTeacher(json& j, Teacher& t) {
    j = {
        {"name", t.getName()},
        {"email", t.getEmail()},
        {"ID", t.getID()},
        {"subjectsTaught", json::object()} };

    for (auto& subject : t.GetSubjectsTaught()) {
        // subject.first is the classID and subject.second is the class pointer format is {classID: className}
        j ["subjectsTaught"][subject.first] = subject.second->getName();
    }

    // cout << j.dump(4) << "\n inside to_teacher json" << endl;
}

// !! Deserialization Section
// deserialize json to object
void from_json(const json& j, Student& s) {
    s.setName(j.at("name").get<string>());
    s.setEmail(j.at("email").get<string>());
    s.setID(j.at("ID").get<string>());
    if (j.contains("classSchedule") && j ["classSchedule"].is_object()) {
        map<string, Class*> classSchedule;
        for (const auto& classScheduleJson : j ["classSchedule"].items()) {
            string classID = classScheduleJson.key();
            string className = classScheduleJson.value().get<string>();
            auto it = allClasses.find(classID);
            if (it != allClasses.end()) {
                classSchedule [classID] = it->second;
            }
        }
        s.enrollInClasses(classSchedule);
    }
    else {
        cout << "no class schedule for student " << s.getName() << endl;
    }
    if (j.contains("attendanceRecord") && j ["attendanceRecord"].is_object()) {
        map<string, string> attendanceRecord;
        for (const auto& attendanceRecordJson : j ["attendanceRecord"].items()) {
            string date = attendanceRecordJson.key();
            string status = attendanceRecordJson.value().get<string>();
            attendanceRecord [date] = status;
        }
        s.setAttendanceRecord(attendanceRecord);
    }

}

void from_json(const json& j, Class& c) {
    c.setClassID(j.at("ID").get<string>());
    c.setName(j.at("name").get<string>());
    cout << endl << c.getName() << " class pointer: " << &c << endl;
    if (j.contains("teacher") && j ["teacher"].is_object()) {
        string teacherID = j ["teacher"].items().begin().key();
        string teacherName = j ["teacher"].items().begin().value().get<string>();
        auto it = allTeachers.find(teacherID);
        if (it != allTeachers.end()) {
            c.setTeacher(it->second);
        }
    }
    else {
        cout << "no teacher for class " << c.getName() << endl;
    }

    if (j.contains("students") && j ["students"].is_object()) {
        map<string, Student*> students;
        for (const auto& studentJson : j ["students"].items()) {
            string studentID = studentJson.key();
            string studentName = studentJson.value().get<string>();
            auto it = allStudents.find(studentID);
            if (it != allStudents.end()) {
                students [studentID] = it->second;
            }
        }
        c.setStudentList(students);
    }
    else {
        cout << "no students for class " << c.getName() << endl;
    }
}

void from_json(const json& j, Teacher& t) {
    t.setName(j.at("name").get<string>());
    t.setEmail(j.at("email").get<string>());
    t.setID(j.at("ID").get<string>());

    if (j.contains("subjectsTaught") && j ["subjectsTaught"].is_object()) {
        map<string, Class*> subjectsTaught;
        for (const auto& subjectTaughtJson : j ["subjectsTaught"].items()) {
            string classID = subjectTaughtJson.key();
            string className = subjectTaughtJson.value().get<string>();
            auto it = allClasses.find(classID);
            if (it != allClasses.end()) {
                cout << endl << "in it->second: " << it->second;
                cout << endl << "in it->second->getName(): " << it->second->getName();
                subjectsTaught [classID] = it->second;
            }
        }
        t.setSubjectsTaught(subjectsTaught);
    }
    else {
        cout << "no subjects taught for teacher " << t.getName() << endl;
    }

}

// !!Data Preloading function whenever the program starts

/*
this function is integral for the program to work
its used to preload data from the json files into the maps
*/
void  preloadDataJsonFile(string option, string filename) {
    if (option == "student") {
        if (isJsonFileEmpty(filename)) {
            cout << "Student data file is empty. Preloading Data with default values.\n";

            for (auto& [studentID, studentPtr] : allStudents) {
                addDataToJsonFile(filename, *studentPtr);
            }
            allStudents = createStudentObjectsFromJsonFile(filename);
        }
        else {
            json studentData = loadDataFromFile(filename);
            for (auto& [studentID, studentJson] : studentData.items()) {
                if (allStudents.find(studentID) == allStudents.end()) {
                    // Student does not exist, create a new one
                    Student* newStudent = new Student();
                    from_json(studentJson, *newStudent);
                    allStudents [studentID] = newStudent;
                }
                else {
                    // Student exists, update its properties
                    from_json(studentJson, *allStudents [studentID]);
                }
            }
        }
    }
    else if (option == "teacher") {
        if (isJsonFileEmpty(filename)) {
            cout << "Teacher data file is empty. Preloading Data with default values.\n";

            for (auto& [teacherID, teacherPtr] : allTeachers) {
                addDataToJsonFile(filename, *teacherPtr);
            }
            allTeachers = createTeacherObjectsFromJsonFile(filename);
        }
        else {
            json teacherData = loadDataFromFile(filename);
            for (auto& [teacherID, teacherJson] : teacherData.items()) {
                if (allTeachers.find(teacherID) == allTeachers.end()) {
                    // Teacher does not exist, create a new one
                    Teacher* newTeacher = new Teacher();
                    from_json(teacherJson, *newTeacher);
                    allTeachers [teacherID] = newTeacher;
                }
                else {
                    // Teacher exists, update its properties
                    from_json(teacherJson, *allTeachers [teacherID]);
                }
            }
        }
    }
    else if (option == "class") {
        if (isJsonFileEmpty(filename)) {
            cout << "Class data file is empty. Preloading Data with default values.\n";

            for (auto& [classID, classPtr] : allClasses) {
                addDataToJsonFileFromClass(filename, *classPtr);
            }
            allClasses = createClassObjectsFromJsonFile(filename);
        }
        else {
            json classData = loadDataFromFile(filename);
            for (auto& [classID, classJson] : classData.items()) {
                if (allClasses.find(classID) == allClasses.end()) {
                    // Class does not exist, create a new one
                    Class* newClass = new Class();
                    from_json(classJson, *newClass);
                    allClasses [classID] = newClass;
                }
                else {
                    // Class exists, update its properties
                    from_json(classJson, *allClasses [classID]);
                }
            }
        }
    }
}
// !!File Manipulation Functions






void addDataToJsonFile(const string& filePath, Student& s) {
    createJsonFile(filePath);
    json existingJsonData = loadDataFromFile(filePath);
    json studentJson;
    to_jsonFromStudent(studentJson, s);

    existingJsonData [s.getID()] = studentJson;
    saveJsonToFile(existingJsonData, filePath);
}

void addDataToJsonFileFromClass(const string& filePath, Class& c) {
    createJsonFile(filePath);
    json existingJsonData = loadDataFromFile(filePath);
    json classJson;
    to_jsonFromClass(classJson, c);
    existingJsonData [c.getClassID()] = classJson;
    saveJsonToFile(existingJsonData, filePath);
}

void addDataToJsonFile(const string& filePath, Teacher& t) {
    createJsonFile(filePath);
    json existingJsonData = loadDataFromFile(filePath);
    json teacherJson;
    to_jsonFromTeacher(teacherJson, t);
    existingJsonData [t.getID()] = teacherJson;
    saveJsonToFile(existingJsonData, filePath);
}

void createJsonFile(const string& filePath) {
    ofstream outfile(filePath, ios::out | ios::app);
    if (!outfile.is_open()) {
        cout << "Error opening file\n";
        return;
    }
    if (outfile.tellp() == 0) {
        outfile << "{}";
    }
    outfile.close();
}

void saveJsonToFile(const json& data, const string& filePath) {
    ofstream outfile(filePath, ios::out | ios::trunc);
    if (!outfile.is_open()) {
        cout << "Error opening file\n";
        return;
    }
    outfile << setw(4) << data << endl; // pretty print with 4 spaces
    outfile.close();
}


json loadDataFromFile(const string& filename) {
    ifstream file(filename);
    json data;
    if (file.peek() != ifstream::traits_type::eof()) {
        try {
            file >> data;
        } catch (const json::parse_error& e) {
            cout << "Parse error: " << e.what() << '\n';
            return json{};
        }
    }
    return data;
}

// !! Other Helper Functions Section
bool isJsonFileEmpty(string& filename) {
    ifstream file(filename);
    if (file.peek() == ifstream::traits_type::eof()) {
        return true;
    }
    json data;
    try {
        file >> data;
    } catch (const json::parse_error& e) {
        cout << "Parse error: " << e.what() << '\n';
        return true;
    }
    return data.empty();
}

map<string, Student*> createStudentObjectsFromJsonFile(string& filename) {
    map<string, Student*> allStudents;
    json studentData = loadDataFromFile(filename);
    for (auto& [id, data] : studentData.items()) {
        Student* studentPtr = new Student();
        from_json(data, *studentPtr);
        allStudents [id] = studentPtr;
    }
    return allStudents;
}

map<string, Class*> createClassObjectsFromJsonFile(string& filename) {
    map<string, Class*> allClasses;
    json classData = loadDataFromFile(filename);
    for (auto& cls : classData.items()) {
        Class* clsPtr = new Class();
        from_json(cls.value(), *clsPtr);
        allClasses [cls.key()] = clsPtr;
    }
    return allClasses;
}

map<string, Teacher*> createTeacherObjectsFromJsonFile(string& filename) {
    map<string, Teacher*> allTeachers;
    json teacherData = loadDataFromFile(filename);
    for (auto& [id, data] : teacherData.items()) {
        Teacher* teacherPtr = new Teacher();
        from_json(data, *teacherPtr);
        allTeachers [id] = teacherPtr;
    }
    return allTeachers;
}
// !FINDERS
Student* findStudentByID(map<string, Student*>, string studentID) {
    for (auto& student : allStudents) {
        if (student.first == studentID) {
            return student.second;
        }
    }
    return nullptr;
}
Teacher* findTeacherByID(map<string, Teacher*>& allTeachers, string teacherID) {
    for (auto& teacher : allTeachers) {
        if (teacher.first == teacherID) {
            return teacher.second;
        }
    }
    return nullptr;
}

Class* findClassByID(map<string, Class*>& allClasses, string classID) {
    for (auto& cls : allClasses) {
        if (cls.first == classID) {
            return cls.second;
        }
    }
    return nullptr;
}
