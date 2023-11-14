#include "./H/filemanipulation.h"

void addDataToJsonFile(const string &filePath, Student &s)
{

    createJsonFile(filePath); // create json file if it doesn't exist
    ifstream infile(filePath);

    json existingJsonData = loadDataFromFile(filePath); // load existing json data from file

    json studentJson;
    to_json(studentJson, s);                   // create json object from student object
    string studentID = s.getID();              // get student ID
    existingJsonData[studentID] = studentJson; // add student data to existing json data

    ofstream outfile(filePath);
    if (outfile.is_open())
    {
        outfile << existingJsonData.dump(4); // write json data to file .dump() function pretty prints the json data
        outfile.close();
    }
    else
    {
        cout << "Error opening file" << endl;
    }
}

void addDataToJsonFileFromClass(const string &filePath, Class *c) // function to add data to json file from class object
{

    createJsonFile(filePath); // create json file if it doesn't exist
    ifstream infile(filePath);

    json existingJsonData = loadDataFromFile(filePath); // load existing json data from file

    json classJson;
    to_jsonFromClass(classJson, c);        // create json object from student object
    string classID = c->getClassID();      // get student ID
    existingJsonData[classID] = classJson; // add student data to existing json data

    ofstream outfile(filePath);
    if (outfile.is_open())
    {
        outfile << existingJsonData.dump(4); // write json data to file
        outfile.close();
    }
    else
    {
        cout << "Error opening file" << endl;
    }
}

void createJsonFile(const string &filePath) // function to create json file if it doesn't exist
{
    ofstream outfile(filePath, ios::out | ios::app);
    if (!outfile.is_open())
    {
        cout << "Error opening file" << endl;
        return;
    }
    if (!outfile.tellp() == 0) // check if json file is empty
    {
        outfile << "{}"; // if not empty, add empty json object
    }

    outfile.close();
}

json loadDataFromFile(const string &filename) // function to load data from json file
{
    ifstream file(filename);
    json data;
    if (file.peek() != ifstream::traits_type::eof()) // check if json file is empty
    {
        try
        {
            file >> data;
        }
        catch (const json::parse_error &e)
        {
            std::cout << "Parse error: " << e.what() << std::endl;
            return json{};
        }
    }
    cout << "DATA ";
    for (auto &el : data.items())
    {
        cout << el.key() << '\n';
    }
    return data;
}

void to_json(json &j, Student s) // convert student object to json object
{
    j = json{
        {"name", s.getName()},
        {"email", s.getEmail()},
    };
    for (auto &cls : s.getClassSchedule())
    {
        j["classSchedule"].push_back(cls->getClassID());
    }

    j["attendanceRecord"] = s.GetAllAttendanceRecords();
}

void to_jsonFromClass(json &j, Class *c) // convert class object to json object
{
    j = json{
        {"name", c->getName()},
    };
    for (auto &student : c->getStudents())
    {
        j["students"].push_back(student->getID());
    }
}

void from_json(const json &j, Student &s)
{
    // Extract data from the JSON object and set it to the Student object
    string name, email, ID;

    if (j.contains("name"))
    {
        name = j.at("name").get<string>();
    }
    if (j.contains("email"))
    {
        email = j.at("email").get<string>();
    }

    s.setName(name);
    s.setEmail(email);

    // TODO add other properties
}

// void from_json(const json &j, Class &c)
// {
//     // extract data from class obj and set it to the class object
//     string name, ID;
//     vector<Student *> studentList;

//     if (j.contains("name"))
//     {
//         name = j.at("name").get<string>();
//     }
//     if (j.contains("ID"))
//     {
//         ID = j.at("ID").get<string>();
//     }
//     if (j.contains("students"))
//     {
//         studentList = j.at("students").get<vector<Student *>>();
//     }
//     c.setClassID(ID);
//     c.setName(name);
//     c.setStudentList(studentList);
//     c.setTeacher(nullptr);
// }

bool isJsonFileEmpty(string &filename) // function to check if json file is empty
{
    ifstream file(filename);
    json data;
    if (file.peek() == ifstream::traits_type::eof()) // check if json file is empty
    {
        return true;
    }

    try
    {
        file >> data;
    }
    catch (const json::parse_error &e) // catch parse error if json file is not empty
    {
        std::cout << "Parse error: " << e.what() << std::endl;
        return true;
    }

    return data.empty(); // return true if json file is empty
}

vector<Student> crateStudentObjectsFromJsonFile(string &filename) // function to create student objects from json file
{
    vector<Student> students;
    json studentData = loadDataFromFile(filename);
    for (auto &student : studentData.items())
    {
        Student s;
        string id = student.key();
        string name = student.value().at("name").get<string>();
        string email = student.value().at("email").get<string>();
        map<string, string> attendanceRecord = student.value().at("attendanceRecord").get<map<string, string>>();
        s.setID(id);
        s.setName(name);
        s.setEmail(email);
        s.setAttendanceRecord(attendanceRecord);
        students.push_back(s);
    }
    return students;
}

map<string, Class *> createClassObjectsFromJsonFile(string &filename) // function to create class objects from json file
{
    map<string, Class *> allClasses;
    json classData = loadDataFromFile(filename);
    for (auto &cls : classData.items())
    {
        string classID = cls.key();
        string className = cls.value().at("name").get<string>();
        // vector<Student *> studentList = cls.value().at("students").get<vector<Student *>>();
        Class *c = new Class(className, classID);
        allClasses[classID] = c; // map<string, Class *> allClasses;
    }
    return allClasses;
}