#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include <dirent.h>

using namespace std;

class Employee
{
public:
    // creating an employee with id name previous pointer pointing to previous employee and next pointer pointing to next employee
    string empId;
    string empName;
    Employee *prev;
    Employee *next;

    // constructor to initialize the values of the employee
    Employee(string id, string name)
    {
        empId = id;
        empName = name;
        prev = nullptr;
        next = nullptr;
    }
};

class EmpList
{
public:
    // head and tail pointer to point starting and ending employee
    Employee *head;
    Employee *tail;
    EmpList()
    {
        // initially those points to null
        head = nullptr;
        tail = nullptr;
    }

    void addEmpAtBeg(string id, string name)
    {
        Employee *newEmployee = new Employee(id, name); // creating a new employee but haven't pointed to any employee
        if (head == nullptr)
        {
            // no employee in list so starting and ending should be pointed to that newly created employee
            head = tail = newEmployee;
        }
        else
        {
            // list contains some employee so add that employee at first and change the pointers
            // newly created employee next must be head and heads previous should be newly created node
            // and mark newly created employee as the starting of the list that is head is pointed to new employee
            newEmployee->next = head;
            head->prev = newEmployee;
            head = newEmployee;
        }
        // cout << "Added successfully" << endl;
    }
    vector<string> dataInList()
    {
        vector<string> res;
        Employee *current = head;
        while (current)
        {
            string data;
            data = current->empId + " " + current->empName + "\n";
            res.push_back(data);
            current = current->next;
        }
        return res;
    }

    void removeLastEmp()
    {

        // if the list is empty
        if ((tail == head) && (tail == nullptr))
        {
            cout << "Employees List is Empty." << endl;
            return;
        }
        else
        {
            // temporary pointer should points to tail and change pointers accordingly
            Employee *lastEmployee = tail;
            if (tail->prev != nullptr) // if the last employee has previous employee
            {
                tail = tail->prev; // mark previous employee of last employee as last employee
                tail->next = nullptr;
            }
            else
            {
                head = tail = nullptr; // list only has one employee so head and tail should point to null
            }
            delete lastEmployee; // removing the employee from the memory
            cout << "Last employee removed." << endl;
        }
    }
    void deleteEmp(string id, string name, bool flag)
    {

        Employee *current = head; // temparary pointer that points to head
        if (head == nullptr && tail == nullptr)
        {
            cout << "Employee List Is Empty" << endl;
            return;
        }
        while (current) // traverse untill that is not the end employee
        {
            if (flag && current->empId == id) // employee found
            {
                universalDelete(current);
                return;
            }
            else if (!flag && current->empName == name)
            {
                universalDelete(current);
                return;
            }
            current = current->next;
        }
        cout << "Employee Not Found" << endl;
    }
    void universalDelete(Employee *current)
    {
        // if current employee has prev employee
        if (current->prev)
        {
            current->prev->next = current->next;
        }
        else
        {
            // If the employee to be deleted is the head
            head = current->next;
        }
        // if employee is not last employee
        if (current->next)
        {
            current->next->prev = current->prev;
        }
        else
        {
            tail = current->prev; // if the employee is last employee
        }

        delete current; // remove the employee from memory
        cout << "Employee Deleted" << endl;
        return;
    }
    void updateEmp(string id, string newName)
    {
        Employee *current = head;
        while (current != nullptr)
        {
            if (current->empId == id)
            {
                current->empName = newName;
                cout << "Employee with empId " << id << " updated." << endl;
                return;
            }
            current = current->next;
        }
        cout << "Employee with empId " << id << " not found." << endl;
    }

    void displayFront()
    {
        Employee *current = head;
        if (current != nullptr)
        {
            cout << "Employees Details From Forward are :" << endl;
        }
        else
        {
            cout << "List Is Empty" << endl;
            return;
        }
        while (current)
        {
            cout << "EmpId: " << current->empId << ", EmpName: " << current->empName << endl;
            current = current->next;
        }
        cout << endl;
    }
    void displayBack()
    {
        Employee *current = tail;
        if (current != nullptr)
        {
            cout << "Employees Details From Backward are :" << endl;
        }
        else
        {
            cout << "List Is Empty" << endl;
            return;
        }
        while (current)
        {
            cout << "EmpId: " << current->empId << ", EmpName: " << current->empName << endl;
            current = current->prev;
        }
        cout << endl;
    }
};

int main()
{
    EmpList *empList = new EmpList();
    int readInput;
    string fileName = "";
    cout << "Do you Want to Read or Edit exiting Employee Info from File Or create New file:" << endl;
    cout << "Press 1 for use Existing File and 0 for New File creation :";
    cin >> readInput;
    if (readInput == 1)
    {
        const char *directoryPath = ".";         // checking present directory
        DIR *directory = opendir(directoryPath); // opening present directory

        map<int, string> map;
        // if present directory contains some file
        if (directory != nullptr)
        {
            dirent *entry;
            int i = 0;
            while ((entry = readdir(directory)) != nullptr)
            {
                if (entry->d_type == DT_REG && std::strstr(entry->d_name, ".txt") != nullptr)
                {
                    // map the directories
                    map[i++] = entry->d_name;
                }
            }
            for (auto i : map)
            {
                cout << i.first << " " << i.second << endl;
            }

            closedir(directory);
            if (map.size() == 0)
            {
                cout << "NO Files Found" << endl;
                return 0;
            }
            int key;
            cout << "Press the Key of the file :";
            cin >> key;
            if (key < map.size() && map.find(key) != map.end())
            {
                fileName = map[key];
                fstream newfile;
                newfile.open(fileName, ios::in);
                if (newfile.is_open())
                {
                    string tp;
                    string finalstring;
                    while (getline(newfile, tp))
                    {
                        finalstring += tp + "\n";
                    }
                    vector<string> arr;
                    string str;
                    stringstream ss(finalstring);

                    while (getline(ss, str, '\n'))
                    {
                        string empname;
                        string empid;
                        for (int i = 0; i < str.size() - 1; i++)
                        {
                            if (str[i] == ' ')
                            {
                                empid = str.substr(0, i);
                                empname = str.substr(i + 1);
                                break;
                            }
                        }
                        empList->addEmpAtBeg(empid, empname);
                    }
                    cout << "Employee Details :";
                    empList->displayFront();
                    newfile.close();
                }
            }
            else
            {
                cout << "Its not a valid input";
                return 0;
            }
        }
    }
    else if (readInput == 0)
    {
        cout << "enter File Name :";
        cin >> fileName;
        fileName += ".txt";
        ofstream outputFile(fileName);

        if (!outputFile.is_open())
        {
            std::cerr << "Error opening the file!" << std::endl;
            return 1;
        }
        outputFile.close();

        std::cout << "File created successfully!" << std::endl;
    }
    else
    {
        cout << "Not a Valid input";
        return 0;
    }
    while (true)
    {
        cout << endl;
        cout << "enter your Option" << endl;
        cout << "1.Add Employee At Beginning:" << endl;
        cout << "2.Remove Employee At Last :" << endl;
        cout << "3.Remove Employee By Id or Name:" << endl;
        cout << "4.Update By Id:" << endl;
        cout << "5.Display From Front:" << endl;
        cout << "6.Display From Back:" << endl;
        cout << "7.save:" << endl;
        cout << "8.exit :" << endl;
        cout << "enter :";
        int val;
        cin >> val;
        if (val == 1)
        {
            string id;
            string name;
            cout << "enter Id of the employee to be added (string):";
            cin >> id;
            cout << "enter Name of the employee (string) :";
            cin >> name;
            empList->addEmpAtBeg(id, name);
            cout << "Added Successfully" << endl;
        }
        else if (val == 2)
        {
            empList->removeLastEmp();
        }
        else if (val == 3)
        {
            int tempVal;
            cout << "1.Delete Employee By Id :" << endl;
            cout << "2.Delete Employee By Name :" << endl;
            cout << "Option 1 or 2 :";
            cin >> tempVal;
            if (tempVal == 1)
            {
                string idToDelete;
                cout << "enter Id of the Employee to be Deleted :" << endl;
                cin >> idToDelete;
                empList->deleteEmp(idToDelete, "", true);
            }
            else if (tempVal == 2)
            {
                string nameToDelete;
                cout << "enter Name of the Employee to be Deleted :" << endl;
                cin >> nameToDelete;
                empList->deleteEmp("", nameToDelete, false);
            }
        }
        else if (val == 4)
        {
            string id;
            string name;
            cout << "enter id of the employee :";
            cin >> id;
            cout << "enter name to be updated :";
            cin >> name;
            empList->updateEmp(id, name);
        }
        else if (val == 5)
        {
            empList->displayFront();
        }
        else if (val == 6)
        {
            empList->displayBack();
        }
        else if (val == 7)
        {

            ofstream outFile(fileName);
            if (!outFile)
            {
                cerr << "Error opening file for writing" << endl;
                return 0;
            }
            vector<string> employeDetails = empList->dataInList();

            for (int i = 0; i < employeDetails.size(); i++)
            {
                outFile << employeDetails[i];
            }
            outFile.close();
            cout << "saved" << endl;
            return 0;
        }
        else
        {
            return 0;
        }
    }

    return 0;
}
