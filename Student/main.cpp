#include<iostream>
#include<cmath>
#include<cstring>
#include<vector>

using namespace std;
class Student {
private:
    string name;
    int id;
    int age;
    double score;

public:
    Student(string n, int i, int a, double s) : name(n), id(i), age(a), score(s) {}

    string getName() const { return name; }
    int getId() const { return id; }
    int getAge() const { return age; }
    double getScore() const { return score; }

    void setName(string n) { name = n; }
    void setAge(int a) { age = a; }
    void setScore(double s) { score = s; }

    void displayInfo() const {
        cout << "Name: " << name << endl;
        cout << "ID: " << id << endl;
        cout << "Age: " << age << endl;
        cout << "Score: " << score << endl;
    }
};

class StudentManager {
private:
    vector<Student> students;

public:

    void addStudent(string name, int id, int age, double score) {
        for (const auto& s : students) {
            if (s.getId() == id) {
                cout << "Error: This ID already exists!" << endl;
                return;
            }
        }
        students.emplace_back(name, id, age, score);
        cout << "Student information entered successfully!" << endl;
    }


    int findStudent(int id) const {
        for (size_t i = 0; i < students.size(); i++) {
            if (students[i].getId() == id) {
                return i;
            }
        }
        return -1;
    }


    void queryStudent(int id) const {
        int index = findStudent(id);
        if (index != -1) {
            students[index].displayInfo();
        } else {
            cout << "The student was not found!" << endl;
        }
    }


    void modifyStudent(int id) {
        int index = findStudent(id);
        if (index != -1) {
            Student& s = students[index];
            cout << "Current information:" << endl;
            s.displayInfo();

            cout << "Please enter a new name (press Enter to keep unchanged):";
            cin.ignore();
            string name;
            getline(cin, name);
            if (!name.empty()) s.setName(name);

            cout << "Please enter a new age (enter 0 to keep unchanged):";
            int age;
            cin >> age;
            if (age > 0) s.setAge(age);

            cout << "Please enter a new score (enter -1 to keep unchanged):";
            double score;
            cin >> score;
            if (score >= 0) s.setScore(score);

            cout << "Student information modified successfully!" << endl;
        } else {
            cout << "The student was not found!" << endl;
        }
    }
};

StudentManager manager;


void handleInfoEntry() {
    string name;
    int id, age;
    double score;

    cout << "Please enter the student ID: ";
    cin >> id;
    cout << "Please enter the student Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Please enter the student Age: ";
    cin >> age;
    cout << "Please enter the student Score: ";
    cin >> score;

    manager.addStudent(name, id, age, score);
}


void handleInfoQuery() {
    int id;
    cout << "Please enter the student ID to query: ";
    cin >> id;
    manager.queryStudent(id);
}


void handleInfoModify() {
    int id;
    cout << "Please enter the student ID to modify: ";
    cin >> id;
    manager.modifyStudent(id);
}

int main() {
    int choice;

    while (true) {

    cout << "****************         Welcome to student information management system     *************************" << endl;
    cout << "***    1 to Information entry " << endl;
    cout << "***    2 to Check  informations " << endl;
    cout << "***    3 to Change informations " << endl;
    cout << "***    4 to Delete informations " << endl;
    cout << "***    5 to Show informations " << endl;
    cout << "***    6 to Get Scores " << endl;
    cout << "***    0 to Exit!  " << endl;
    cout << "***********************************************************************************************************" << endl;
    cout << "Input your choice: " << endl;


        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Error: Please enter a valid number!" << endl;
            continue;
        }

        switch (choice) {
            case 1:
                handleInfoEntry();
                break;
            case 2:
                handleInfoQuery();
                break;
            case 3:
                handleInfoModify();
                break;
            case 0:
                cout << "Exiting the system. Goodbye!" << endl;
                return 0;
            default:
                cout << "This function has not been implemented yet!" << endl;
        }
    }
}

