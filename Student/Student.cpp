#include<iostream>
#include"Student.h"

using namespace std;


Student::Student()
{
    setName("");
    setSex("Female");
    setClassName(1);
    setId(00000);
    setAge(0);
    setScore(0.0);
}
Student::Student(string name,string sex,int className,int id,int age,double score )
{
    setName(name);
    setSex(sex);
    setClassName(className);
    setId(id);
    setAge(age);
    setScore(score);
}

void Student::setName(string name)
{
    this->name = name;
}

void Student::setSex(string sex)
{
    this->sex = sex;
}

void Student::setId(int id)
{
    this->id = id;
}

void Student::setClassName(int className)
{
    this->className = className;
}

void Student::setAge(int age)
{
    this->age = age;
}

void Student::setScore(double score)
{
    this->score = score;
}

string Student::getName() const
{
    return name;
}

string Student::getSex() const
{
    return sex;
}

int Student::getId() const
{
    return id;
}

int Student::getClassName() const
{
    return className;
}

int Student::getAge() const
{
    return age;
}

double Student::getScore() const
{
    return score;
}

void Student::displayInfo() const
{
    cout << "=================================================================" << endl;
    cout << "Student Name: " << name << endl;
    cout << "Student ID: " << id << endl;
    cout << "Student Gender: " << sex << endl;
    cout << "Student Age: " << age << endl;
    cout << "Student Class: " << className << endl;
    cout << "Student Score: " << score << endl;
    cout << "=================================================================" << endl;
}
