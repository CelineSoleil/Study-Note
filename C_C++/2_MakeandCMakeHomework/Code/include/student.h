#pragma once
#include<vector>
#include<string>
struct Student{
    std::string name;
    int score;
};
double average(const std::vector<Student>& students);
Student topStudent(const std::vector<Student>& students);
void printAll(const std::vector<Student>& students);