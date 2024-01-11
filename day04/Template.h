#include <string>
#include <vector>
using namespace std;
class Employee
{
public:
    std::string empId;
    std::string empName;
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
    void addEmpAtBeg(std::string id, std::string name);
    void removeLastEmp();
    void deleteEmp(std::string id, std::string name, bool flag);
    void universalDelete(Employee *current);
    void updateEmp(std::string id, std::string newName);
    void display();
    std::vector<std::string> dataInList();
};
