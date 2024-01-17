#include <string>
#include <vector>
using namespace std;
class Project
{
public:
    std::string proName;
    std::string proDesc;
    std::string proStatus;
    Project(std::string name, std::string desc, std::string status);
};
class Employee
{
public:
    std::string empId;
    std::string empName;
    std::vector<Project> projects;
    Employee *prev;
    Employee *next;

    Employee(std::string id, std::string name);
};
class EmpList
{
public:
    Employee *head;
    Employee *tail;
    EmpList();
    Employee *addEmpAtBeg(std::string id, std::string name);
    void addProject(std::string name, std::string desc, std::string status, Employee *empNode);
    void addProjectWithId(std::string id, std::string name, std::string desc, std::string status, EmpList *empList);
    void removeLastEmp();
    void deleteEmp(std::string id, std::string name, bool flag);
    void universalDelete(Employee *current);
    void updateEmp(std::string id, std::string newName);
    bool updateProjectStatus(std::string EmpId, std::string EmpName, std::string newStatus);

    void display();
};
