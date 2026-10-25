#include "StudentService.h"
#include<memory>
#include<algorithm>
bool StudentService::isValidScore(double score){
    return score>=0.0 &&score<=100.0;
}

    //添加
    bool StudentService::Add_Student(int id,const std::string& name,double score){
        if(id<=0||name.empty()||!isValidScore(score))return false;
        if(students_.find(id)!=students_.end())return false;
        students_[id]=std::make_unique<Student>(id,name,score);
        return true;
    }
    //删除
    bool StudentService::Remove_Student(int id){
        return students_.erase(id)>0;
    }
    //改
    bool StudentService::Update_Student(int id,const std::string& newName,double newScore){
        if(newName.empty()||!isValidScore(newScore))return false;
        Student* student=Find_By_Id(id);
        if(student==nullptr){
            return false;
        }
        student->setName(newName);
        student->setScore(newScore);
        return true;
    }
    //查学号
    Student* StudentService:: Find_By_Id(int id)const{
        auto it=students_.find(id);
        if(it==students_.end()){
            return nullptr;
        }
        return it->second.get();
    }
    //查姓名，允许同名，vector
    std::vector<Student*> StudentService:: Find_By_Name(const std::string name)const{
        std::vector<Student*> result;
        for(const auto& pair:students_){
            const Student* student=pair.second.get();
            if(student->getName()==name){
                result.push_back(const_cast<Student*>(student));
            }
        }

        std::sort(result.begin(),result.end(),[](const Student* a,const Student* b){return a->getId()>b->getId();});
        return result;
    }
    //查成绩，允许相同成绩
    std::vector<Student*> StudentService:: Find_By_Score(double score)const{
        std::vector<Student*> result;
        for(const auto& pair:students_){
            const Student* student=pair.second.get();
            if(student->getScore()==score){
                result.push_back(const_cast<Student*>(student));
            }
        }

        std::sort(result.begin(),result.end(),[](const Student*a,const Student*b){return a->getId()>b->getId();});
        return result;
    }
    //获取全部学生
    std::vector<Student*> StudentService::Get_All_Students()const{
        std::vector<Student*>result;
        for(const auto& pair:students_){
            const Student* student=pair.second.get();
            result.push_back(const_cast<Student*>(student));
        }
        std::sort(result.begin(),result.end(),[](const Student*a,const Student*b){return a->getId()>b->getId();});
        return result;
    }
    //获取学生认输
    std::size_t StudentService::size()const{
        return students_.size();
    }