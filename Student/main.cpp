#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>

#include "Student.h"

using namespace std;

class StudentManager {
private:
    vector<Student> students;
    const string fileName = "students.txt";

public:
    StudentManager() {
        loadFromFile();
    }

    ~StudentManager() {
        saveToFile();
    }

    void addStudent() {
        string name, sex;
        int id, age, classNum;
        double score;

        cout << "Enter student name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter student ID: ";
        while (!(cin >> id)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a number: ";
        }

        if (findStudentIndex(id) != -1) {
            cout << "Error: This student ID already exists!" << endl;
            return;
        }

        cout << "Enter student gender: ";
        cin >> sex;

        cout << "Enter student age: ";
        while (!(cin >> age)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a number: ";
        }

        cout << "Enter student class: ";
        while (!(cin >> classNum)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a number: ";
        }

        cout << "Enter student score: ";
        while (!(cin >> score)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input, please enter a number: ";
        }

        students.emplace_back(name, sex, classNum, id, age, score);
        cout << "Student information added successfully!" << endl;
        saveToFile();
    }

    int findStudentIndex(int id) const {
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].getId() == id) {
                return i;
            }
        }
        return -1;
    }

    void queryStudent() const {
        int choice;
        cout << "Select query method:" << endl;
        cout << "1. Query by student ID" << endl;
        cout << "2. Query by student name" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            cout << "Enter student ID to query: ";
            cin >> id;
            int index = findStudentIndex(id);
            if (index != -1) {
                students[index].displayInfo();
            } else {
                cout << "Student not found!" << endl;
            }
        } else if (choice == 2) {
            string name;
            cout << "Enter student name to query: ";
            cin.ignore();
            getline(cin, name);
            bool found = false;
            for (const auto& student : students) {
                if (student.getName() == name) {
                    student.displayInfo();
                    found = true;
                }
            }
            if (!found) {
                cout << "Student not found!" << endl;
            }
        } else {
            cout << "Invalid choice!" << endl;
        }
    }

    void modifyStudent() {
        int id;
        cout << "Enter student ID to modify: ";
        cin >> id;
        int index = findStudentIndex(id);
        if (index != -1) {
            Student& s = students[index];
            cout << "Current information:" << endl;
            s.displayInfo();

            string name, sex;
            int age, classNum;
            double score;

            cout << "Enter new name (press Enter to keep unchanged): ";
            cin.ignore();
            getline(cin, name);
            if (!name.empty()) s.setName(name);

            cout << "Enter new gender (press Enter to keep unchanged): ";
            getline(cin, sex);
            if (!sex.empty()) s.setSex(sex);

            cout << "Enter new age (enter 0 to keep unchanged): ";
            cin >> age;
            if (age > 0) s.setAge(age);

            cout << "Enter new class (enter 0 to keep unchanged): ";
            cin >> classNum;
            if (classNum > 0) s.setClassName(classNum);

            cout << "Enter new score (enter -1 to keep unchanged): ";
            cin >> score;
            if (score >= 0) s.setScore(score);

            cout << "Student information modified successfully!" << endl;
            saveToFile();
        } else {
            cout << "Student not found!" << endl;
        }
    }

    void deleteStudent() {
        int id;
        cout << "Enter student ID to delete: ";
        cin >> id;
        int index = findStudentIndex(id);
        if (index != -1) {
            cout << "Found student information:" << endl;
            students[index].displayInfo();

            char confirm;
            cout << "Confirm deletion? (Y/N): ";
            cin >> confirm;

            if (confirm == 'Y' || confirm == 'y') {
                students.erase(students.begin() + index);
                cout << "Student information deleted successfully!" << endl;
                saveToFile();
            } else {
                cout << "Deletion canceled." << endl;
            }
        } else {
            cout << "Student not found!" << endl;
        }
    }

    void displayAllStudents() const {
        if (students.empty()) {
            cout << "No student information available!" << endl;
            return;
        }

        cout << "=========================================================================" << endl;
        cout << "| ID\t\t| Name\t\t| Gender\t| Age\t| Class\t| Score\t|" << endl;
        cout << "=========================================================================" << endl;

        for (const auto& student : students) {
            cout << "| " << student.getId() << "\t| "
                 << student.getName() << "\t| "
                 << student.getSex() << "\t\t| "
                 << student.getAge() << "\t| "
                 << student.getClassName() << "\t| "
                 << student.getScore() << "\t|" << endl;
        }

        cout << "=========================================================================" << endl;
        cout << "Total: " << students.size() << " students." << endl;
    }

    void statisticsScores() const {
        if (students.empty()) {
            cout << "No student information, cannot perform score statistics!" << endl;
            return;
        }

        int choice;
        cout << "Select statistics method:" << endl;
        cout << "1. Statistics for all students" << endl;
        cout << "2. Statistics by class" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        vector<Student> filteredStudents;

        if (choice == 1) {
            filteredStudents = students;
        } else if (choice == 2) {
            int classNum;
            cout << "Enter class to statistics: ";
            cin >> classNum;
            for (const auto& student : students) {
                if (student.getClassName() == classNum) {
                    filteredStudents.push_back(student);
                }
            }
            if (filteredStudents.empty()) {
                cout << "No students in this class!" << endl;
                return;
            }
        } else {
            cout << "Invalid choice!" << endl;
            return;
        }

        double sum = 0.0;
        double maxScore = filteredStudents[0].getScore();
        double minScore = filteredStudents[0].getScore();

        for (const auto& student : filteredStudents) {
            double score = student.getScore();
            sum += score;
            if (score > maxScore) maxScore = score;
            if (score < minScore) minScore = score;
        }

        double average = sum / filteredStudents.size();

        cout << "Score statistics results:" << endl;
        cout << "----------------------------------------" << endl;
        cout << "Total students: " << filteredStudents.size() << endl;
        cout << "Average score: " << average << endl;
        cout << "Highest score: " << maxScore << endl;
        cout << "Lowest score: " << minScore << endl;
        cout << "----------------------------------------" << endl;
    }

    void saveToFile() const {
        ofstream file(fileName);
        if (file.is_open()) {
            for (const auto& student : students) {
                file << student.getName() << ","
                     << student.getSex() << ","
                     << student.getClassName() << ","
                     << student.getId() << ","
                     << student.getAge() << ","
                     << student.getScore() << endl;
            }
            file.close();
        } else {
            cerr << "Failed to open file for saving data!" << endl;
        }
    }

    void loadFromFile() {
        ifstream file(fileName);
        if (file.is_open()) {
            students.clear();
            string line;
            while (getline(file, line)) {
                size_t pos = 0;
                vector<string> tokens;
                string token;
                while ((pos = line.find(',')) != string::npos) {
                    token = line.substr(0, pos);
                    tokens.push_back(token);
                    line.erase(0, pos + 1);
                }
                tokens.push_back(line);

                if (tokens.size() == 6) {
                    string name = tokens[0];
                    string sex = tokens[1];
                    int classNum = stoi(tokens[2]);
                    int id = stoi(tokens[3]);
                    int age = stoi(tokens[4]);
                    double score = stod(tokens[5]);
                    students.emplace_back(name, sex, classNum, id, age, score);
                }
            }
            file.close();
        }
    }

    void exportToTxt(const string& filename = "students_export.txt") const {
    ofstream file(filename);
    if (file.is_open()) {
        // 使用与 displayAllStudents 相同的表格格式
        file << "=========================================================================" << endl;
        file << "| ID\t\t| Name\t\t| Gender\t| Age\t| Class\t| Score\t|" << endl;
        file << "=========================================================================" << endl;

        for (const auto& student : students) {
            file << "| " << student.getId() << "\t| "
                 << student.getName() << "\t| "
                 << student.getSex() << "\t\t| "
                 << student.getAge() << "\t| "
                 << student.getClassName() << "\t| "
                 << student.getScore() << "\t|" << endl;
        }

        file << "=========================================================================" << endl;
        file << "Total: " << students.size() << " students." << endl;

        file.close();
        cout << "学生信息已成功导出到: " << filename << endl;
    } else {
        cerr << "无法打开文件: " << filename << endl;
    }
}
};

void showMenu() {
    cout << endl;
    cout << "****************         Welcome to Student Information Management System     *************************" << endl;
    cout << "***    1. Add Student Information" << endl;
    cout << "***    2. Query Student Information" << endl;
    cout << "***    3. Modify Student Information" << endl;
    cout << "***    4. Delete Student Information" << endl;
    cout << "***    5. Display All Students" << endl;
    cout << "***    6. Score Statistics" << endl;
    cout << "***    7. Export Students to TXT" << endl;
    cout << "***    0. Exit System" << endl;
    cout << "***********************************************************************************************************" << endl;
    cout << "Enter your choice (0-7): ";
}

int main() {
    StudentManager manager;
    int choice;

    while (true) {
        showMenu();

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Error: Please enter a valid number!" << endl;
            continue;
        }

        switch (choice) {
            case 1:
                manager.addStudent();
                break;
            case 2:
                manager.queryStudent();
                break;
            case 3:
                manager.modifyStudent();
                break;
            case 4:
                manager.deleteStudent();
                break;
            case 5:
                manager.displayAllStudents();
                break;
            case 6:
                manager.statisticsScores();
                break;
            case 7: {
                string filename;
                cout << "请输入导出文件名 (默认为 students_export.txt): ";
                cin.ignore(); // 清除输入缓冲区
                getline(cin, filename);
                if (filename.empty()) {
                    filename = "students_export.txt";
                }
                manager.exportToTxt(filename);
                break;
            }
            case 0:
                cout << "Confirm exit? (Y/N): ";
                char confirm;
                cin >> confirm;
                if (confirm == 'Y' || confirm == 'y') {
                    cout << "Exiting system, thank you for using!" << endl;
                    return 0;
                }
                break;
            default:
                cout << "Invalid choice, please re-enter!" << endl;
        }
    }
}

