#include<iostream>
#include<iomanip>
#include<vector>
#include<limits>
#include"Student.h"
#include"StudentService.h"

//=============学生成绩管理系统===========
/*
1. 添加学生
2. 删除学生
3. 按学号查询
4. 按姓名查询
5. 按成绩查询
6. 修改学生
7. 显示全部学生
0. 退出
请选择：
学生暂时只有三个属性：
属性 	类型 	说明 
学号	int	唯一标识，不允许重复
姓名	string	学生姓名
成绩	double	暂定为 0～100 分

项目结构
├── CMakeLists.txt
├── Student.h
├── StudentService.h
├── StudentService.cpp
└── main.cpp

Student.h：学生数据模型；
StudentService：处理增删查改，不负责菜单输入输出；
main.cpp：负责显示菜单、读取输入、打印结果；
学生对象由 unique_ptr 自动释放，不需要手动 delete。
*/

void  showMenu(){//显示菜单
    std::cout << "\n====== 学生成绩管理系统 ======\n";
    std::cout << "1. 添加学生\n";
    std::cout << "2. 删除学生\n";
    std::cout << "3. 按学号查询\n";
    std::cout << "4. 按姓名查询\n";
    std::cout << "5. 按成绩查询\n";
    std::cout << "6. 修改学生\n";
    std::cout << "7. 显示全部学生\n";
    std::cout << "0. 退出\n";
    std::cout << "请选择：";
}


int readInt(const std::string& prompt){//读取学号
    int value;

    while(true){
        std::cout<<prompt;
        if(std::cin>>value){
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            return value;
        }

        std::cout<<"输入无效，请重新输入整数：\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');

    }
}

double readScore(const std::string& prompt){//读取成绩
    double score;

    while(true){
        std::cout<<prompt;
        if(std::cin>>score){
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            if(score>=0.0&&score<=100.0){
                return score;
            }
            std::cout<<"成绩必须在0~100之间。\n";
            continue;
        }
        std::cout<<"输入无效，请输入数字。\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    }

}

std::string readName(const std::string& prompt){
    std::string name;
    while(true){
        std::cout<<prompt;
        std::getline(std::cin,name);
        if(!name.empty()){
            return name;
        }
        std::cout<<"姓名不能为空。\n";
    }
}

void printStudent(const Student& student){
    std::cout<<std::left
            <<std::setw(12)<<student.getId()
            <<std::setw(20)<<student.getName()
            <<std::fixed<<std::setprecision(1)
            <<student.getScore()<<"\n";
}

void printStudentList(const std::vector<Student*>& students){
    if(students.empty()){
        std::cout<<"没用符合条件的学生。\n";
        return;
    }

    std::cout<<std::left
            <<std::setw(12)<<"学号"
            <<std::setw(20)<<"姓名"
            <<"成绩\n";
    std::cout<<"-----------------------------------\n";

    for(const Student* student:students){
        printStudent(*student);
    }
}

void addStudent(StudentService& service){
    int id=readInt("请输入学号");
    if(service.Find_By_Id(id)!=nullptr){
        std::cout<<"添加失败：该学号已纯在！\n";
        return;
    }

    std::string name=readName("请输入姓名:");
    double score=readScore("请输入成绩：");

    if(service.Add_Student(id,name,score)){
        std::cout<<"添加成功\n";
    }
    else{
        std::cout<<"添加失败：请检查学号，姓名，成绩是否合法。\n";
    }
}

void removeStudent(StudentService&service){
    int id=readInt("请输入要删除的学号：");

    if(service.Remove_Student(id)){
        std::cout<<"删除成功\n";
    }
    else{
        std::cout<<"删除失败：没用找到该学生。\n";
    }
}

void findStudentById(const StudentService&service){
    int id=readInt("请输入要查询的id：");
    Student* student=service.Find_By_Id(id);
    if(student==nullptr){
        std::cout<<"没有找到该学生\n";
        return;
    }
    printStudentList({student});
}

void findStudentByName(const StudentService&service){
    std::string name=readName("请输入要查询的name：");
    const std::vector<Student*> student=service.Find_By_Name(name);
    if(student.empty()){
        std::cout<<"没有找到该学生\n";
        return;
    }
    printStudentList(student);
}

void findStudentByScore(const StudentService&service){
    double score=readScore("请输入要查询的score：");
    const std::vector<Student*>student=service.Find_By_Score(score);
    if(student.empty()){
        std::cout<<"没有找到该学生\n";
        return;
    }
    printStudentList(student);
}

void showAllStudents(const StudentService&service){
    std::cout<<"当前共有："<<service.size()<<" 名学生。\n";
    printStudentList(service.Get_All_Students());
}

void updateStudent(StudentService& service) {
    int id = readInt("请输入要修改的学号：");

    if (service.Find_By_Id(id) == nullptr) {
        std::cout << "修改失败：没有找到该学生。\n";
        return;
    }

    std::string newName = readName("请输入新姓名：");
    double newScore = readScore("请输入新成绩：");

    if (service.Update_Student(id, newName, newScore)) {
        std::cout << "修改成功。\n";
    } else {
        std::cout << "修改失败：输入数据不合法。\n";
    }
}



int main(){
   StudentService service;

    // 与当前业务层命名保持一致
    service.Add_Student(1002, "李四", 92.0);
    service.Add_Student(1001, "张三", 86.5);

    while (true) {
        showMenu();

        int choice = readInt("");

        switch (choice) {
            case 1:
                addStudent(service);
                break;
            case 2:
                removeStudent(service);
                break;
            case 3:
                findStudentById(service);
                break;
            case 4:
                findStudentByName(service);
                break;
            case 5:
                findStudentByScore(service);
                break;
            case 6:
                updateStudent(service);
                break;
            case 7:
                showAllStudents(service);
                break;
            case 0:
                std::cout << "程序已退出。\n";
                return 0;
            default:
                std::cout << "没有该选项，请重新选择。\n";
                break;
        }
    }

    return 0;
}