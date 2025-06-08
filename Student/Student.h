#ifndef STUDENT_H
#define STUDENT_H

#include <string>

using namespace std;

class Student
{
private:
    string name;
    string sex;
    int className;
    int id;
    int age;
    double score;
public:
    Student();
    Student(string name,string sex,int className,int id,int age,double score );

    void setName(string name);
    void setSex(string sex);
    void setId(int id);
    void setClassName(int className);
    void setAge(int age);
    void setScore(double score);

    string getName() const;
    string getSex() const;
    int getId() const;
    int getClassName() const;
    int getAge() const;
    double getScore() const;

    void displayInfo() const;
};
#endif
