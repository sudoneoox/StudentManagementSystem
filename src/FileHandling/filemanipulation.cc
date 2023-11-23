#include "../include/filemanipulation.h"

// !! Serialization Section
// seriliaze Student Class Object into json so that it can be saved in a json format
/*
@param j: the json object to be serialized
@param s: the student object to be serialized
*/
void to_jsonFromStudent(json& j, Student& s) {
    j = {
        {"name", s.getName()}, // studentName
        {"email", s.getEmail()}, // studentEmail
        {"ID", s.getID()}, // studentID
        {"classSchedule", json::object()}, // {classID: className}
        {"attendanceRecord", s.GetAllAttendanceRecords()}, // {date: status}
        {"AssignmentGrades",s.getGradesForAssignment()}, // {assignmentID: grade}
        {"ExamGrades", s.getGradesForExam()} // {examID: grade}
    };
    for (auto& classSchedule : s.getClassSchedule()) {
        // classSchedule.first is the classID and classSchedule.second is the class pointer format is {classID: className}
        j ["classSchedule"][classSchedule.first] = classSchedule.second->getName();
    }

}


// seriliaze Class Class Object into json so that it can be saved in a json format
/*
@param j: the json object to be serialized
@param c: the class object to be serialized
*/
void to_jsonFromClass(json& j, Class& c) {
    j = {
        {"name", c.getName()}, // className
        {"ID", c.getClassID()}, // classID
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

/*
@param j: the json object to be serialized
@param t: the teacher object to be serialized
serializes teacher object into json so that it can be saved in a json format
*/
void to_jsonFromTeacher(json& j, Teacher& t) {
    j = {
        {"name", t.getName()}, // teacherName
        {"email", t.getEmail()}, // teacherEmail
        {"ID", t.getID()}, // teacherID
        {"subjectsTaught", json::object()} }; // {classID: className}

    for (auto& subject : t.GetSubjectsTaught()) {
        // subject.first is the classID and subject.second is the class pointer format is {classID: className}
        j ["subjectsTaught"][subject.first] = subject.second->getName();
    }
}

/* !! Deserialization Section this is used to deserialize the json data into objects so that they can be used in the program its a way
 to turn json data into class objects effectively
*/

/*
@param j: the json object to be deserialized
@param s: the student object to be deserialized
*/
void from_json(const json& j, Student& s) {
    s.setName(j.at("name").get<string>()); // studentName
    s.setEmail(j.at("email").get<string>()); // studentEmail 
    s.setID(j.at("ID").get<string>()); // studentID 
    if (j.contains("classSchedule") && j ["classSchedule"].is_object()) { // {classID: className}
        map<string, Class*> classSchedule;
        for (const auto& classScheduleJson : j ["classSchedule"].items()) {
            string classID = classScheduleJson.key();
            string className = classScheduleJson.value().get<string>();
            auto it = allClasses.find(classID);
            if (it != allClasses.end()) {
                classSchedule [classID] = it->second;
            }
        }
        s.enrollInClasses(classSchedule); // adds the classes to the student object
    }
    else {
        cout << "no class schedule for student " << s.getName() << endl;
    }
    if (j.contains("attendanceRecord") && j ["attendanceRecord"].is_object()) { // {date: status}
        map<string, string> attendanceRecord;
        for (const auto& attendanceRecordJson : j ["attendanceRecord"].items()) {
            string date = attendanceRecordJson.key();
            string status = attendanceRecordJson.value().get<string>();
            attendanceRecord [date] = status;
        }
        s.setAttendanceRecord(attendanceRecord); // adds the attendance record to the student object
    }
    if (j.contains("AssignmentGrades")) { // {assignmentID: grade}
        auto grades = j.at("AssignmentGrades").get<map<string, double>>();
        for (const auto& pair : grades) {
            s.setGradeForAssignment(pair.first, pair.second); // adds the assignment grades to the student object
        }
    }
    if (j.contains("ExamGrades")) { // {examID: grade}
        auto grades = j.at("ExamGrades").get<map<string, double>>();
        for (const auto& pair : grades) {
            s.setGradeForExam(pair.first, pair.second); // adds the exam grades to the student object
        }
    }
}

/*
@param j: the json object to be deserialized
@param c: the class object to be deserialized
*/
void from_json(const json& j, Class& c) {
    c.setClassID(j.at("ID").get<string>()); // classID
    c.setName(j.at("name").get<string>());  // className
    if (j.contains("teacher") && j ["teacher"].is_object()) { // {teacherID: teacherName}
        string teacherID = j ["teacher"].items().begin().key();
        string teacherName = j ["teacher"].items().begin().value().get<string>();
        auto it = allTeachers.find(teacherID);
        if (it != allTeachers.end()) {
            c.setTeacher(it->second); // adds the teacher pointer stored in the map to the class object
        }
    }
    else {
        cout << "no teacher for class " << c.getName() << endl;
    }

    if (j.contains("students") && j ["students"].is_object()) { // {studentID: studentName}
        map<string, Student*> students;
        for (const auto& studentJson : j ["students"].items()) {
            string studentID = studentJson.key();
            string studentName = studentJson.value().get<string>();
            auto it = allStudents.find(studentID);
            if (it != allStudents.end()) {
                students [studentID] = it->second;  // adds the student pointer stored in the map to the class object
            }
        }
        c.setStudentList(students); // adds the students to the class object
    }
    else {
        cout << "no students for class " << c.getName() << endl;
    }
    if (j.contains("assignments")) { // {assignmentID: assignmentName}
        for (auto& [assignmentID, assignmentJson] : j ["assignments"].items()) {
            string assignmentName = assignmentJson.at("name").get<string>();
            Assignment* assignment = new Assignment(assignmentName, assignmentID); // creates a new assignment object

            if (assignmentJson.contains("grades")) { // {studentID: grade}
                auto& gradesJson = assignmentJson ["grades"];
                for (auto& [studentID, gradesJson] : gradesJson.items()) {
                    if (gradesJson.is_object() && gradesJson.contains(assignmentID)) {
                        double gradeatjson = gradesJson [assignmentID].get<double>();
                        assignment->setGrade(studentID, assignmentID, gradeatjson); // adds the assignment grades to the assignment object
                    }
                }
            }
            c.addAssignment(assignment); // adds the assignment object to the class object
        }
    }
    else {
        cout << "no assignments for class " << c.getName() << endl;
    }

    if (j.contains("exams")) { // {examID: examName}
        for (auto& [examID, examJson] : j ["exams"].items()) {
            string examName = examJson.at("name").get<string>();
            Exam* exam = new Exam(examName, examID); // creates a new exam object

            if (examJson.contains("grades")) {
                auto& gradesJson = examJson ["grades"];
                for (auto& [studentID, gradeJson] : gradesJson.items()) {
                    if (gradeJson.is_object() && gradeJson.contains(examID)) {
                        double gradeatjson = gradeJson [examID].get<double>();
                        exam->setGrade(studentID, examID, gradeatjson); // adds the exam grades to the exam object
                    }
                }
            }
            c.addExam(exam); // adds the exam object to the class object
        }
    }
    else {
        cout << "no exams for class " << c.getName() << endl;
    }

}

/*
@param j: the json object to be deserialized
@param t: the teacher object to be deserialized
*/
void from_json(const json& j, Teacher& t) {
    t.setName(j.at("name").get<string>()); // teacherName
    t.setEmail(j.at("email").get<string>()); // teacherEmail
    t.setID(j.at("ID").get<string>()); // teacherID

    if (j.contains("subjectsTaught") && j ["subjectsTaught"].is_object()) { // {classID: className}
        map<string, Class*> subjectsTaught;
        for (const auto& subjectTaughtJson : j ["subjectsTaught"].items()) {
            string classID = subjectTaughtJson.key();
            string className = subjectTaughtJson.value().get<string>();
            auto it = allClasses.find(classID);
            if (it != allClasses.end()) {
                subjectsTaught [classID] = it->second;  // adds the class pointer stored in the map to the teacher object
            }
        }
        t.setSubjectsTaught(subjectsTaught); // adds the classes to the teacher object
    }
    else {
        cout << "no subjects taught for teacher " << t.getName() << endl;
    }

}

// !!Data Preloading function whenever the program starts
/*
@param option: the option to preload data for
@param filename: the filename to preload data from
This function checks if the json file is empty and if it is it preloads the data from the global variables that were created in the initClasses function
If the json file is not empty it loads the data from the json file from the previous session and creates the objects from the json file
If the json file was empty it exits the program and asks the user to rerun the program to link all the objects to one another
*/
void  preloadDataJsonFile(string option, string filename) {
    bool preloadedStudent, preloadedTeacher, preloadedClass = false; // checks if the data was preloaded for all the options

    if (option == "student") {
        if (isJsonFileEmpty(filename)) { // checks if the json file is empty
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
                    from_json(studentJson, *newStudent); // creates a new student object from the json file
                    allStudents [studentID] = newStudent; // adds the student object to the map
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
            allTeachers = createTeacherObjectsFromJsonFile(filename); // creates teacher objects from the json file
            preloadedTeacher = true;
        }
        else {
            json teacherData = loadDataFromFile(filename);
            for (auto& [teacherID, teacherJson] : teacherData.items()) {
                if (allTeachers.find(teacherID) == allTeachers.end()) {
                    // Teacher does not exist, create a new one
                    Teacher* newTeacher = new Teacher();
                    from_json(teacherJson, *newTeacher);
                    allTeachers [teacherID] = newTeacher; // adds the teacher object to the map
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
    if (preloadedStudent && preloadedTeacher && preloadedClass) { // checks if all the data was preloaded
        cout << "Preloaded the JSON data successfully. Please rerun the program to link all the objects to one another" << endl; // this is to make sure that all the objects are linked to one another
        exit(0);
    }
}


// !!File Manipulation/Handling Functions

/*
@param filePath: the path to the file to be created
@param s: the student object to be added to the file

This function creates a json file if it does not exist and adds the student object to the json file

*/
void addDataToJsonFile(const string& filePath, Student& s) {
    createJsonFile(filePath);
    json existingJsonData = loadDataFromFile(filePath);
    json studentJson;
    to_jsonFromStudent(studentJson, s);

    existingJsonData [s.getID()] = studentJson;
    saveJsonToFile(existingJsonData, filePath);
}

/*
@param filePath: the path to the file to be created
@param c: the class object to be added to the file
this function creates a json file if it does not exist and adds the class object to the json file
*/

void addDataToJsonFileFromClass(const string& filePath, Class& c) {
    createJsonFile(filePath);
    json existingJsonData = loadDataFromFile(filePath);
    json classJson;
    to_jsonFromClass(classJson, c);
    existingJsonData [c.getClassID()] = classJson;
    saveJsonToFile(existingJsonData, filePath);
}


/*
@param filePath: the path to the file to be created
@param t: the teacher object to be added to the file
this function creates a json file if it does not exist and adds the teacher object to the json file
*/
void addDataToJsonFile(const string& filePath, Teacher& t) {
    createJsonFile(filePath);
    json existingJsonData = loadDataFromFile(filePath);
    json teacherJson;
    to_jsonFromTeacher(teacherJson, t);
    existingJsonData [t.getID()] = teacherJson;
    saveJsonToFile(existingJsonData, filePath);
}



/*
@param filePath: the path to the file to be created
This function creates a json file if it does not exist
*/
void createJsonFile(const string& filePath) {
    ofstream outfile(filePath, ios::out | ios::app); // app appends to the file
    if (!outfile.is_open()) {
        cout << "Error opening file\n";
        return;
    }
    if (outfile.tellp() == 0) { // checks if the file is empty
        outfile << "{}";
    }
    outfile.close();
}


/*
@param data: the json object to be saved to the file
@param filePath: the path to the file to be created
This function saves the json object to the file
*/
void saveJsonToFile(const json& data, const string& filePath) {
    ofstream outfile(filePath, ios::out | ios::trunc); // trunc deletes the contents of the file
    if (!outfile.is_open()) { // checks if the file is open
        cout << "Error opening file\n";
        return;
    }
    outfile << setw(4) << data << endl; // pretty print with 4 spaces
    outfile.close();
}

/*
@param filename: the path to the file to be loaded
This function loads the json data from the file
*/
json loadDataFromFile(const string& filename) {
    ifstream file(filename);
    json data;
    if (file.peek() != ifstream::traits_type::eof()) { // checks if the file is empty
        try {
            file >> data;
        } catch (const json::parse_error& e) { // catches any parse errors
            cout << "Parse error: " << e.what() << '\n';
            return json{};
        }
    }
    return data;
}

// !! Other Helper Functions Section
/*
@param filename: the path to the file to be checked
This function checks if the json file is empty
*/
bool isJsonFileEmpty(string& filename) {
    ifstream file(filename);
    if (file.peek() == ifstream::traits_type::eof()) { // checks if the file is empty
        return true;
    }
    json data;
    try {
        file >> data;
    } catch (const json::parse_error& e) {
        cout << "Parse error: " << e.what() << '\n';
        return true;
    }
    return data.empty(); // returns true if the json file is empty
}


/*
@param filename: the path to the file to be deleted
this function uses the previous functions to create student objects out of the json file

*/
map<string, Student*> createStudentObjectsFromJsonFile(string& filename) {
    map<string, Student*> allStudents; // {studentID: studentPtr}
    json studentData = loadDataFromFile(filename); // loads the data from the json file
    for (auto& [id, data] : studentData.items()) {
        Student* studentPtr = new Student();
        from_json(data, *studentPtr);
        allStudents [id] = studentPtr;
    }
    return allStudents;
}

map<string, Class*> createClassObjectsFromJsonFile(string& filename) {
    map<string, Class*> allClasses; // {classID: classPtr}
    json classData = loadDataFromFile(filename);
    for (auto& cls : classData.items()) {
        Class* clsPtr = new Class();
        from_json(cls.value(), *clsPtr);
        allClasses [cls.key()] = clsPtr;
    }
    return allClasses;
}

map<string, Teacher*> createTeacherObjectsFromJsonFile(string& filename) {
    map<string, Teacher*> allTeachers; // {teacherID: teacherPtr}
    json teacherData = loadDataFromFile(filename);
    for (auto& [id, data] : teacherData.items()) {
        Teacher* teacherPtr = new Teacher(); // creates a new teacher object
        from_json(data, *teacherPtr);
        allTeachers [id] = teacherPtr;
    }
    return allTeachers;
}
// !FINDERS SECTION these helper functions return the pointer of the object that is being searched for since the objects are stored in maps in the form of {ID: pointer}
Student* findStudentByID(map<string, Student*>& allStudents, string studentID) {
    for (auto& student : allStudents) {
        if (student.first == studentID) {
            return student.second;
        }
    }
    return nullptr; // returns nullptr if the student is not found
}

Teacher* findTeacherByID(map<string, Teacher*>& allTeachers, string teacherID) {
    for (auto& teacher : allTeachers) {
        if (teacher.first == teacherID) {
            return teacher.second;
        }
    }
    return nullptr; // returns nullptr if the teacher is not found
}

Class* findClassByID(map<string, Class*>& allClasses, string classID) {
    for (auto& cls : allClasses) {
        if (cls.first == classID) {
            return cls.second;
        }
    }
    return nullptr; // returns nullptr if the class is not found
}
