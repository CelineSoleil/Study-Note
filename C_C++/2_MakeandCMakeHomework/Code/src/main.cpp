#include"student.h"
#include <iostream>
int main(){
    std::vector<Student> students;
    students.push_back({"Jack",90});
    students.push_back({"Tom",80});
    students.push_back({"Luck",70});

    printAll(students);
    Student top=topStudent(students);
    std::cout<<"Top Student: "<<top.name<<" "<<top.score<<std::endl;

    return 0;
}