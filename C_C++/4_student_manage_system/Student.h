#pragma once
#include<string>
#include<utility>
class Student{
public:
    Student(int id,std::string name,double score):id_(id),name_(std::move(name)),score_(score){}

    int getId()const{
        return id_;
    }
    const std::string& getName()const{
        return name_;
    }
    double getScore()const{
        return score_;
    }
    void setName(std::string name){
        name_=std::move(name);
    }
    void setScore(double score){
        score_=score;
    }
private:
   
    int id_;
    std::string name_;
    double score_;
};
