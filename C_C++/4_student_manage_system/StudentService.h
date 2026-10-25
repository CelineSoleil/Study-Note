#pragma once

#include "Student.h"

#include<memory>
#include<unordered_map>
#include<vector>

class StudentService{
public:
    //添加
    bool Add_Student(int id,const std::string& name,double score);
    //删除
    bool Remove_Student(int id);
    //改
    bool Update_Student(int id,const std::string& newName,double newScore);
    //查学号
    Student* Find_By_Id(int id)const;
    //查姓名，允许同名，vector
    std::vector<Student*> Find_By_Name(const std::string name)const;
    //查成绩，允许相同成绩
    std::vector<Student*> Find_By_Score(double score)const;
    //获取全部学生
    std::vector<Student*> Get_All_Students()const;
    //获取学生认输
    std::size_t size()const;
private:
    bool isValidScore(double score);//判断成绩是否合理
    std::unordered_map<int,std::unique_ptr<Student>> students_;//学生管理系统
};