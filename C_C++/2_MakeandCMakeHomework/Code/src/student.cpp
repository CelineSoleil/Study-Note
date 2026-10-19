#include "student.h"
#include <iostream>
double average(const std::vector<Student>&students){
    double sum=0;
    for(const auto& Student:students){
        sum+=Student.score;
    }
    double avg=sum/students.size();
    return avg;
}

Student topStudent(const std::vector<Student>&students){
    Student topStudent;
    topStudent.score=-1;
    topStudent.name="";
    for(const auto&Student:students){
        if(Student.score>topStudent.score){
            topStudent.name=Student.name;
            topStudent.score=Student.score;
        }
    }
    return topStudent;
}