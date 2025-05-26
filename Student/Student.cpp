#include<iostream>
#include"Student.h"

using namespace std;


Student::Student()
{
    setName("");
    setSex("Female");
    setClass(1);
    setId(00000);
    setScore(0.0);
}
Student::Student(string name,string sex,int cla,int id,double sco )
{
    setName(name);
    setSex(sex);
    setClass(cla);
    setId(id);
    setScore(sco);
}
Student::setName(string name)
{
    Name=name;
}
Student::setSex(string sex)
{
    Sex=sex;
}
Student::setId(int id)
{
    Id=id;
}
Student::setClass(int cla)
{
    Class=cla;
}
Student::setScore(double sco)
{
    Score=sco;
}

string Student::getName()
{
    return Name;
}
string Student::getSex()
{
    return Sex;
}
int Student::getId()
{
    return Id;
}
int Student::getClass()
{
    return Class;
}
double Student::getScore()
{
    return Score;
}
