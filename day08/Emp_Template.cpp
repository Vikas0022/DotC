#include <iostream>
#include "Template.h"

using namespace std;
Project::Project(std::string name, std::string desc, std::string status)
{
    proName = name;
    proDesc = desc;
    proStatus = status;
}
Employee::Employee(std::string id, std::string name)
{
    empId = id;
    empName = name;
    prev = nullptr;
    next = nullptr;
}

EmpList::EmpList()
{
    head = nullptr;
    tail = nullptr;
}

void EmpList::addProject(std::string name, std::string desc, std::string status, Employee *empProject)
{
    Project p(name, desc, status);
    empProject->projects.push_back(p);
}
void EmpList::addProjectWithId(std::string rId, std::string newproName, std::string newproDesc, std::string newProStatus, EmpList *empList)
{
    Employee *currentEmp = head;
    while (currentEmp)
    {
        if (currentEmp->empId == rId)
        {
            empList->addProject(newproName, newproDesc, newProStatus, currentEmp);
            return;
        }
        currentEmp = currentEmp->next;
    }
}

Employee *EmpList::addEmpAtBeg(std::string newEmpId, std::string newEmpName)
{
    Employee *newEmployee = new Employee(newEmpId, newEmpName);
    if (head == nullptr)
    {
        return head = tail = newEmployee;
    }
    else
    {
        newEmployee->next = head;
        head->prev = newEmployee;
        return head = newEmployee;
    }
}
bool EmpList::updateProjectStatus(std::string rId, std::string rName, std::string newStatus)
{
    Employee *currentEmp = head;
    while (currentEmp)
    {
        if (currentEmp->empId == rId)
        {
            for (Project &empProjects : currentEmp->projects)
            {
                if (empProjects.proName == rName)
                {
                    empProjects.proStatus = newStatus;
                    return 1;
                }
            }
        }
        currentEmp = currentEmp->next;
    }
    return 0;
}
void EmpList::removeLastEmp()
{

    if ((tail == head) && (tail == nullptr))
    {
        cout << "Employees List is Empty." << endl;
        return;
    }
    else
    {
        Employee *lastEmployee = tail;
        if (tail->prev != nullptr)
        {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else
        {
            head = tail = nullptr;
        }
        delete lastEmployee;
        cout << "Last employee removed." << endl;
    }
}
void EmpList::deleteEmp(string id, string name, bool flag)
{

    Employee *currentEmp = head;
    if (head == nullptr && tail == nullptr)
    {
        cout << "Employee List Is Empty" << endl;
        return;
    }
    while (currentEmp)
    {
        if (flag && currentEmp->empId == id)
        {
            universalDelete(currentEmp);
            return;
        }
        else if (!flag && currentEmp->empName == name)
        {
            universalDelete(currentEmp);
            return;
        }
        currentEmp = currentEmp->next;
    }
    cout << "Employee Not Found" << endl;
}

void EmpList::universalDelete(Employee *currentEmp)
{
    if (currentEmp->prev)
    {
        currentEmp->prev->next = currentEmp->next;
    }
    else
    {
        head = currentEmp->next;
    }
    if (currentEmp->next)
    {
        currentEmp->next->prev = currentEmp->prev;
    }
    else
    {
        tail = currentEmp->prev;
    }

    delete currentEmp;
    cout << "Employee Deleted" << endl;
    return;
}
void EmpList::updateEmp(string id, string newName)
{
    Employee *currentEmp = head;
    while (currentEmp != nullptr)
    {
        if (currentEmp->empId == id)
        {
            currentEmp->empName = newName;
            cout << "Employee with empId " << id << " updated." << endl;
            return;
        }
        currentEmp = currentEmp->next;
    }
    cout << "Employee with empId " << id << " not found." << endl;
}

void EmpList::display()
{
    Employee *currentEmp = head;
    if (currentEmp != nullptr)
    {
        cout << "Employees Details From Forward are :" << endl;
    }
    else
    {
        cout << "List Is Empty" << endl;
        return;
    }
    while (currentEmp)
    {
        cout << "EmpId: " << currentEmp->empId << ", EmpName: " << currentEmp->empName << endl;
        cout << "Projects are :" << endl;
        for (Project i : currentEmp->projects)
        {
            cout << i.proName << " " << i.proDesc << " " << i.proStatus << endl;
        }
        currentEmp = currentEmp->next;
    }
    cout << endl;
}
