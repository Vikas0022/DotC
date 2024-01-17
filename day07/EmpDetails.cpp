#include "Template.h"
#include "json.hpp"
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <dirent.h>

using namespace std;

int showFilesInFolder(string &rFileName, EmpList *rEmpList)
{
    map<int, string> map;
    const char *directoryPath = "."; // current dir
    DIR *directory = opendir(directoryPath);

    if (directory != nullptr)
    {
        dirent *entry;
        int i = 0;
        while ((entry = readdir(directory)) != nullptr)
        {
            if (entry->d_type == DT_REG && std::strstr(entry->d_name, ".json") != nullptr)
            {
                map[i++] = entry->d_name;
            }
        }
        for (auto i : map)
        {
            cout << i.first << "->" << i.second << endl;
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
            rFileName = map[key];
            using json = nlohmann::json;
            std::ifstream inputFile(rFileName);
            if (inputFile.is_open())
            {
                json JsonData;
                inputFile >> JsonData;
                inputFile.close();

                for (auto EmpData : JsonData)
                {
                    Employee *EmpNode = rEmpList->addEmpAtBeg(EmpData["id"], EmpData["name"]);
                    for (auto project : EmpData["Projects"])
                    {
                        std::string pname = project["Name"];
                        std::string pdesc = project["Description"];
                        std::string pstatus = project["Status"];
                        rEmpList->addProject(pname, pdesc, pstatus, EmpNode);
                    }
                }
            }
            else
            {
                std::cerr << "Error opening the input file" << std::endl;
            }
        }
        else
        {
            cout << "Its not a valid input";
            return 0;
        }
    }
}
int createNewFile(string &rFileName)
{
    rFileName += ".json";
    ofstream outputFile(rFileName);

    if (!outputFile.is_open())
    {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }
    outputFile.close();

    std::cout << "File created successfully!" << std::endl;
    return 0;
}
void saveToFile(string &rFileName, EmpList *rEmpList)
{
    using json = nlohmann::ordered_json;
    json JsonData;

    Employee *currentEmp = rEmpList->head;
    while (currentEmp)
    {
        json EmpData;
        json projectArray;
        EmpData["name"] = currentEmp->empName;
        EmpData["id"] = currentEmp->empId;
        for (auto project : currentEmp->projects)
        {
            json EmpProject;
            EmpProject["Name"] = project.proName;
            EmpProject["Description"] = project.proDesc;
            EmpProject["Status"] = project.proStatus;
            projectArray.push_back(EmpProject);
        }
        EmpData["Projects"] = projectArray;
        JsonData.push_back(EmpData);
        currentEmp = currentEmp->next;
    }

    std::ofstream outputFile(rFileName);

    if (outputFile.is_open())
    {
        outputFile << JsonData.dump(4);
        outputFile.close();

        std::cout << "Data successfully written to :" << rFileName << std::endl;
    }
    else
    {
        std::cerr << "Error opening the output file" << std::endl;
    }
}
int main()
{
    EmpList *empList = new EmpList();
    int readInput;
    string fileName = "";
    cout << "Press 0 To Create New File :" << endl;
    cout << "Press 1 for Use Existing File :";
    cin >> readInput;
    if (readInput == 1)
    {
        int exitFromIt = showFilesInFolder(fileName, empList);
        if (exitFromIt == 0)
            return 0;
    }
    else if (readInput == 0)
    {
        cout << "Enter File Name :";
        cin >> fileName;
        int exitFromIt = createNewFile(fileName);
        if (exitFromIt)
            return 0;
    }
    else
    {
        cout << "Not a Valid input";
        return 0;
    }
    while (true)
    {
        cout << endl;
        cout << "Options :" << endl;
        cout << "1.Add Employee :" << endl;
        cout << "2.Remove Employee :" << endl;
        cout << "3.Remove Employee By Id or Name:" << endl;
        cout << "4.Update By Id:" << endl;
        cout << "5.Add Projects to Employee :" << endl;
        cout << "6.Update Status of Project :" << endl;
        cout << "7.Display :" << endl;
        cout << "8.save:" << endl;
        cout << "9.exit :" << endl;
        cout << "enter your Options {1,2,....9} :";
        int val;
        cin >> val;
        if (val == 1)
        {
            string id;
            string name;
            cout << "enter Id of the employee to be added (string):";
            cin >> id;

            // Consume the newline character left in the buffer
            cin.ignore();

            cout << "enter Name of the employee (string) :";
            getline(cin, name);

            Employee *empNode = empList->addEmpAtBeg(id, name); // Add employee only once

            int numProjects;
            cout << "Enter Number of Projects";
            cin >> numProjects;

            for (int i = 0; i < numProjects; i++)
            {
                string pName, pDesc, pStatus;
                cout << "Enter Name of the Project :";
                getline(cin >> ws, pName);
                cout << "Enter Description of the Projects :";
                getline(cin >> ws, pDesc);
                cout << "Enter Status of the Project :";
                getline(cin >> ws, pStatus);
                empList->addProject(pName, pDesc, pStatus, empNode);
            }

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
                getline(cin >> ws, nameToDelete);
                empList->deleteEmp("", nameToDelete, false);
            }
            else
            {
                cout << "invalid input";
                return 0;
            }
        }
        else if (val == 4)
        {
            string id;
            string name;
            cout << "enter id of the employee :";
            cin >> id;
            cout << "enter name to be updated :";
            getline(cin >> ws, name);
            empList->updateEmp(id, name);
        }
        else if (val == 5)
        {
            std::string rId, newproName, newproDesc, newProStatus;
            cout << "Enter Id of the Employee :";
            getline(cin >> ws, rId);
            cout << "Enter New Project Name :";
            getline(cin >> ws, newproName);
            cout << "Enter New Project Description :";
            getline(cin >> ws, newproDesc);
            cout << "Enter New Project Status :";
            getline(cin >> ws, newProStatus);
            empList->addProjectWithId(rId, newproName, newproDesc, newProStatus, empList);
        }
        else if (val == 6)
        {
            string refId, refName, newStatus;
            cout << "Enter Id of the Employee :";
            getline(cin >> ws, refId);
            cout << "Enter Name of the Project :";
            getline(cin >> ws, refName);
            cout << "Enter the new Status of the Project :";
            getline(cin >> ws, newStatus);
            cout << refId << " " << refName << " " << newStatus << endl;
            bool statusCode = empList->updateProjectStatus(refId, refName, newStatus);
            if (!statusCode)
            {
                cout << "failed To Update";
                return 0;
            }
            cout << "Updated Successfully :";
        }
        else if (val == 7)
        {
            empList->display();
        }
        else if (val == 8)
        {
            saveToFile(fileName, empList);
            return 0;
        }
        else
        {
            return 0;
        }
    }

    return 0;
}
