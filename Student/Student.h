#ifndef STUDENT_H
#define STUDENT_H

#include<iostream>

using namespace std;
class Student
{
private:
    string Name;
    string Sex;
    int Class;
    int Id;//Student id
    double Score;
public:
    Student();
    Student(string name,string sex,int cla,int id,double sco );

    setName(string name);
    setSex(string sex);
    setId(int id);
    setClass(int cla);
    setScore(double sco);

    string getName();
    string getSex();
    int getId();
    int getClass();
    double getScore();
};
#endif
