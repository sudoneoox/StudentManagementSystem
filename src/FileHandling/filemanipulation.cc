#include "../include/filemanipulation.h"

// !! Serialization Section
// serialize object to json
void to_jsonFromStudent(json& j, Student& s) {
    j = {
        {"name", s.getName()},
        {"email", s.getEmail()},
        {"ID", s.getID()},
        {"classSchedule", json::object()},
        {"attendanceRecord", s.GetAllAttendanceRecords()},
        {"AssignmentGrades",s.getGradesForAssignment()},
        {"ExamGrades", s.getGradesForExam()}
    };
    for (auto& classSchedule : s.getClassSchedule()) {
        // classSchedule.first is the classID and classSchedule.second is the class pointer format is {classID: className}
        j ["classSchedule"][classSchedule.first] = classSchedule.second->getName();
    }

}




// cout << j.dump(4) << "\n inside to_student json" << endl;

void to_jsonFromClass(json& j, Class& c) { //FIXME tojson for assignments and exams
    // cout << "inside to_jsonFromClass\n";
    j = {
        {"name", c.getName()},
        {"ID", c.getClassID()},
        {"students",json::object()}, // {studentID: studentName}
        {"teacher", json::object()}, // {teacherID: teacherName}
        {"assignments", json::object()}, // {assignmentID: assignmentName}
        {"exams", json::object()} // {examID: examName}
    };
    if (c.getTeacher() != nullptr) {
        j ["teacher"][c.getTeacher()->getID()] = c.getTeacher()->getName();

    }
    for (auto& student : c.getStudents()) {
        // student.first is the studentID and student.second is the student pointer format is {studentID: studentName}
        j ["students"][student.first] = student.second->getName();
    }

    for (auto& assignment : c.getAssignments()) {
        auto& assignmentPtr = assignment.second;
        json assignmentJson = {
            {"name", assignmentPtr->getName()},
            {"grades", json::object()}
        };

        for (auto& grade : assignmentPtr->getAllGrades()) {
            assignmentJson ["grades"][grade.first] = grade.second; // {studentID: grade}
        }

        j ["assignments"][assignmentPtr->getID()] = assignmentJson;
    }

    for (auto& exam : c.getExams()) {
        auto& examPtr = exam.second;
        json examJson = {
            {"name", examPtr->getName()},
            {"grades", json::object()} // {studentID: grade}
        };
        for (auto& grade : examPtr->getAllGrades()) {
            examJson ["grades"][grade.first] = grade.second; // {studentID: grade}
        }
        j ["exams"][examPtr->getID()] = examJson; // {examID: examJson}
    }

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
    if (j.contains("AssignmentGrades")) {
        auto grades = j.at("AssignmentGrades").get<map<string, double>>();
        for (const auto& pair : grades) {
            s.setGradeForAssignment(pair.first, pair.second);
        }
    }
    if (j.contains("ExamGrades")) {
        auto grades = j.at("ExamGrades").get<map<string, double>>();
        for (const auto& pair : grades) {
            s.setGradeForExam(pair.first, pair.second);
        }
    }
}

void from_json(const json& j, Class& c) {
    c.setClassID(j.at("ID").get<string>());
    c.setName(j.at("name").get<string>());
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
    if (j.contains("assignments")) {
        for (auto& [assignmentID, assignmentJson] : j ["assignments"].items()) {
            string assignmentName = assignmentJson.at("name").get<string>();
            Assignment* assignment = new Assignment(assignmentName, assignmentID);

            if (assignmentJson.contains("grades")) {
                auto& gradesJson = assignmentJson ["grades"];
                for (auto& [studentID, gradesJson] : gradesJson.items()) {
                    if (gradesJson.is_object() && gradesJson.contains(assignmentID)) {
                        double gradeatjson = gradesJson [assignmentID].get<double>();
                        assignment->setGrade(studentID, assignmentID, gradeatjson);
                    }
                }
            }
            c.addAssignment(assignment);
        }
    }
    else {
        cout << "no assignments for class " << c.getName() << endl;
    }

    if (j.contains("exams")) {
        for (auto& [examID, examJson] : j ["exams"].items()) {
            string examName = examJson.at("name").get<string>();
            Exam* exam = new Exam(examName, examID);

            if (examJson.contains("grades")) {
                auto& gradesJson = examJson ["grades"];
                for (auto& [studentID, gradeJson] : gradesJson.items()) {
                    if (gradeJson.is_object() && gradeJson.contains(examID)) {
                        double gradeatjson = gradeJson [examID].get<double>();
                        exam->setGrade(studentID, examID, gradeatjson);
                    }
                }
            }
            c.addExam(exam);
        }
    }
    else {
        cout << "no exams for class " << c.getName() << endl;
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
    bool preloadedStudent, preloadedTeacher, preloadedClass = false;

    if (option == "student") {
        if (isJsonFileEmpty(filename)) {
            cout << "Student data file is empty. Preloading Data with default values.\n";

            for (auto& [studentID, studentPtr] : allStudents) {
                addDataToJsonFile(filename, *studentPtr);
            }
            allStudents = createStudentObjectsFromJsonFile(filename);
            preloadedStudent = true;
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
            preloadedTeacher = true;
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
            preloadedClass = true;
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
    if (preloadedStudent && preloadedTeacher && preloadedClass) {
        cout << "Preloaded the JSON data successfully. Please rerun the program to link all the objects to one another" << endl;
        exit(0);
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
Student* findStudentByID(map<string, Student*>& allStudents, string studentID) {
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
