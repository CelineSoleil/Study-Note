#include"student.h"
#include <iostream>
void printAll(const std::vector<Student>& students){
    for(const auto& student:students){
        std::cout<<student.name<<" "<<student.score<<std::endl;
    }
    std::cout<<average(students)<<std::endl;
}