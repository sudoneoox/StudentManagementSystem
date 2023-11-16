#include "../include/filemanipulation.h"

// !! Serialization Section
// serialize object to json
void to_json(json &j, Student s)
{
    j = {
        {"name", s.getName()},
        {"email", s.getEmail()},
        {"ID", s.getID()},
        {"classSchedule", vector<string>()},
        {"attendanceRecord", map<string, string>()}};
    j["attendanceRecord"] = s.GetAllAttendanceRecords();
    cout << "in to_json " << s.GetAllAttendanceRecords().at("11/15/2023") << endl;
    for (auto &cls : s.getClassSchedule())
    {
        j["classSchedule"].push_back(cls->getClassID());
    }
    cout << j.dump(4) << endl;
}

void to_jsonFromClass(json &j, Class *c)
{
    j = {
        {"name", c->getName()},
        {"ID", c->getClassID()},
        {"students", vector<string>()}};
    for (const auto &student : c->getStudents())
    {
        cout << student->getID() << endl;
        j["students"].push_back(student->getID());
    }
}
void to_jsonFromTeacher(json &j, Teacher &t)
{
    j = json{
        {"name", t.getName()},
        {"email", t.getEmail()},
        {"ID", t.getID()},
        {"subjectsTaught", json::array()}};

    for (const auto &subject : t.GetSubjectsTaught())
    {
        j["subjectsTaught"].push_back(subject->getClassID()); // Assuming Class has getClassID()
    }
}

// !! Deserialization Section
// deserialize json to object
void from_json(const json &j, Student &s)
{
    s.setName(j.at("name").get<string>());
    s.setEmail(j.at("email").get<string>());
    s.setID(j.at("ID").get<string>());
    if (j.contains("classSchedule") && j["classSchedule"].is_array())
    {
        vector<Class *> classes;
        for (const auto &classIDJson : j["classSchedule"])
        {
            string classID = classIDJson.get<string>();
            auto it = allClasses.find(classID);
            if (it != allClasses.end())
            {
                classes.push_back(it->second);
            }
        }
        s.enrollInClasses(classes);
    }
    cout << "attendance record is object? " << j["attendanceRecord"].is_object() << endl;
    if (j.contains("attendanceRecord") && j["attendanceRecord"].is_object())
    {
        map<string, string> attendanceRecord;
        for (const auto &attendanceRecordJson : j["attendanceRecord"].items())
        {
            string date = attendanceRecordJson.key();
            string status = attendanceRecordJson.value().get<string>();
            attendanceRecord[date] = status;
        }
        s.setAttendanceRecord(attendanceRecord);
    }
    // TODO: Add other properties and relationships
}

void from_json(const json &j, Class &c)
{
    c.setClassID(j.at("ID").get<string>());
    c.setName(j.at("name").get<string>());
}

void from_json(const json &j, Teacher &t)
{
    t.setName(j.at("name").get<string>());
    t.setEmail(j.at("email").get<string>());
    t.setID(j.at("ID").get<string>());

    if (j.contains("subjectsTaught") && j["subjectsTaught"].is_array())
    {
        vector<Class *> subjects;
        for (const auto &classIDJson : j["subjectsTaught"])
        {
            string classID = classIDJson.get<string>();
            auto it = allClasses.find(classID);
            if (it != allClasses.end())
            {
                subjects.push_back(it->second);
            }
        }
        t.UpdateSubjects(subjects);
    }
}

// !!Data Preloading function whenever the program starts
void PreloadData(string option, string filename)
{
    if (option == "student")
    {
        if (isJsonFileEmpty(filename))
        {
            cout << "Student data file is empty. Preloading Data with default values.\n";
            students = {
                Student("Diego", "drcorona@cougarnet.uh.edu", "1000"),
                Student("Jane", "janedoe@cougarnet.uh.edu", "1001")};
            students.at(0).MarkAttendance("11/15/2023", "ABSENT");
            students.at(1).MarkAttendance("11/15/2023", "ABSENT");
            for (auto &student : students)
            {
                addDataToJsonFile(filename, student);
            }
        }
        else
        {
            students = crateStudentObjectsFromJsonFile(filename);
        }
    }
    else if (option == "teacher")
    {
        if (isJsonFileEmpty(filename))
        {
            cout << "Teacher data file is empty. Preloading Data with default values.\n";
            teachers = {
                Teacher("Dr. Corona", "teacher@cougarnet.uh.edu", "2000"),
                Teacher("Dr. Doe", "doe@uh.edu", "2001")};
            for (auto &teacher : teachers)
            {
                addDataToJsonFile(filename, teacher);
            }
        }
        else
        {
            teachers = createTeacherObjectsFromJsonFile(filename);
        }
    }
    else if (option == "class")
    {
        if (isJsonFileEmpty(filename))
        {
            cout << "Class data file is empty. Preloading Data with default values.\n";
            Class *mathClass = new Class("Math 101", "C001");
            mathClass->addStudent(&students[0]);
            mathClass->addStudent(&students[1]);
            cout << mathClass->getStudents().size() << endl;
            Class *scienceClass = new Class("Science 102", "C002");
            allClasses = {{"C001", mathClass}, {"C002", scienceClass}};

            for (auto &[classID, classPtr] : allClasses)
            {
                addDataToJsonFileFromClass(filename, classPtr);
            }
        }
        else
        {
            allClasses = createClassObjectsFromJsonFile(filename);
        }
    }
}

// !!File Manipulation Functions
void addDataToJsonFile(const string &filePath, Student &s)
{
    createJsonFile(filePath);
    json existingJsonData = loadDataFromFile(filePath);
    json studentJson;
    to_json(studentJson, s);

    existingJsonData[s.getID()] = studentJson;
    saveJsonToFile(existingJsonData, filePath);
}

void addDataToJsonFileFromClass(const string &filePath, Class *c)
{
    createJsonFile(filePath);
    json existingJsonData = loadDataFromFile(filePath);
    json classJson;
    to_jsonFromClass(classJson, c);
    existingJsonData[c->getClassID()] = classJson;
    saveJsonToFile(existingJsonData, filePath);
}

void addDataToJsonFile(const string &filePath, Teacher &t)
{
    createJsonFile(filePath);
    json existingJsonData = loadDataFromFile(filePath);
    json teacherJson;
    to_jsonFromTeacher(teacherJson, t);
    existingJsonData[t.getID()] = teacherJson;
    saveJsonToFile(existingJsonData, filePath);
}

void createJsonFile(const string &filePath)
{
    ofstream outfile(filePath, ios::out | ios::app);
    if (!outfile.is_open())
    {
        cout << "Error opening file\n";
        return;
    }
    if (outfile.tellp() == 0)
    {
        outfile << "{}";
    }
    outfile.close();
}

void saveJsonToFile(const json &data, const string &filePath)
{
    ofstream outfile(filePath, ios::out | ios::trunc);
    if (!outfile.is_open())
    {
        cout << "Error opening file\n";
        return;
    }
    outfile << setw(4) << data << endl; // pretty print with 4 spaces
    outfile.close();
}

json loadDataFromFile(const string &filename)
{
    ifstream file(filename);
    json data;
    if (file.peek() != ifstream::traits_type::eof())
    {
        try
        {
            file >> data;
        }
        catch (const json::parse_error &e)
        {
            cout << "Parse error: " << e.what() << '\n';
            return json{};
        }
    }
    return data;
}

// !! Other Helper Functions Section
bool isJsonFileEmpty(string &filename)
{
    ifstream file(filename);
    if (file.peek() == ifstream::traits_type::eof())
    {
        return true;
    }
    json data;
    try
    {
        file >> data;
    }
    catch (const json::parse_error &e)
    {
        cout << "Parse error: " << e.what() << '\n';
        return true;
    }
    return data.empty();
}

vector<Student> crateStudentObjectsFromJsonFile(string &filename)
{
    vector<Student> students;
    json studentData = loadDataFromFile(filename);
    for (auto &[id, data] : studentData.items())
    {
        Student s;
        from_json(data, s);
        students.push_back(s);
    }
    return students;
}

map<string, Class *> createClassObjectsFromJsonFile(string &filename)
{
    map<string, Class *> allClasses;
    json classData = loadDataFromFile(filename);
    for (auto &cls : classData.items())
    {
        string classID = cls.key();
        string className = cls.value().at("name").get<string>();
        Class *c = new Class(className, classID);
        json studentIDsJSONFORMAT = cls.value().at("students"); // TODO: rework this
        allClasses[classID] = c;                                // map<string, Class *> allClasses;
    }
    return allClasses;
}

vector<Teacher> createTeacherObjectsFromJsonFile(string &filename)

{
    vector<Teacher> teachers;
    json teacherData = loadDataFromFile(filename);
    for (auto &[id, data] : teacherData.items())
    {
        Teacher t;
        from_json(data, t);
        teachers.push_back(t);
    }
    return teachers;
}
// !FINDERS
Student *findStudentByID(vector<Student> &students, string &studentID)
{
    for (auto it = students.begin(); it != students.end(); ++it)
    {
        if (it->getID() == studentID)
        {
            return &(*it);
        }
    }
    return nullptr;
}

Teacher *findTeacherByID(vector<Teacher> &teachers, string &teacherID)
{
    for (auto it = teachers.begin(); it != teachers.end(); ++it)
    {
        if (it->getID() == teacherID)
        {
            return &(*it);
        }
    }
    return nullptr;
}

Class *findClassByID(map<string, Class *> &allClasses, string &classID)
{
    for (auto &cls : allClasses)
    {
        if (cls.first == classID)
        {
            return cls.second;
        }
    }
    return nullptr;
}
