#include "Template.h"
#include "tinyxml2.h"
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <dirent.h>

using namespace std;

int createNewFile(string &rFileName)
{
    rFileName += ".xml";
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
            if (entry->d_type == DT_REG && std::strstr(entry->d_name, ".xml") != nullptr)
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
            tinyxml2::XMLDocument doc;
            if (doc.LoadFile(rFileName.c_str()) == tinyxml2::XML_SUCCESS)
            {
                tinyxml2::XMLElement *root = doc.FirstChildElement("Root");
                if (root)
                {
                    for (tinyxml2::XMLElement *empElement = root->FirstChildElement("Employee"); empElement; empElement = empElement->NextSiblingElement("Employee"))
                    {
                        tinyxml2::XMLElement *idElement = empElement->FirstChildElement("ID");
                        tinyxml2::XMLElement *nameElement = empElement->FirstChildElement("Name");
                        tinyxml2::XMLElement *projectList = empElement->FirstChildElement("ProjectsList");

                        if (idElement && nameElement)
                        {
                            const char *id = idElement->GetText();
                            const char *name = nameElement->GetText();

                            if (id && name)
                            {
                                Employee *empNode = rEmpList->addEmpAtBeg(id, name);
                                for (tinyxml2::XMLElement *project = projectList->FirstChildElement("Project"); project; project = project->NextSiblingElement("Project"))
                                {
                                    tinyxml2::XMLElement *pName = project->FirstChildElement("Name");
                                    tinyxml2::XMLElement *pDesc = project->FirstChildElement("Description");
                                    tinyxml2::XMLElement *pstatus = project->FirstChildElement("Status");
                                    const char *proName = pName->GetText();
                                    const char *proDesc = pDesc->GetText();
                                    const char *proStatus = pstatus->GetText();
                                    rEmpList->addProject(proName, proDesc, proStatus, empNode);
                                }
                            }
                        }
                    }
                    return 1;
                }
                else
                {
                    std::cerr << "Root element not found in XML." << std::endl;
                    return 0;
                }
            }
            else
            {
                std::cerr << "Failed to load XML file: " << rFileName << std::endl;
                return 0;
            }
        }
        else
        {
            cout << "Its not a valid input";
            return 0;
        }
    }
}
void saveToFile(string &rFileName, EmpList *rEmpList)
{
    Employee *currentEmp = rEmpList->head;
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement *root = doc.NewElement("Root");
    doc.InsertFirstChild(root);
    while (currentEmp)
    {
        tinyxml2::XMLElement *employee = doc.NewElement("Employee");
        tinyxml2::XMLElement *id = doc.NewElement("ID");
        tinyxml2::XMLElement *name = doc.NewElement("Name");
        id->SetText(currentEmp->empId.c_str());
        name->SetText(currentEmp->empName.c_str());

        tinyxml2::XMLElement *projectsList = doc.NewElement("ProjectsList");

        for (auto project : currentEmp->projects)
        {
            tinyxml2::XMLElement *projectTag = doc.NewElement("Project");
            tinyxml2::XMLElement *nameTag = doc.NewElement("Name");
            tinyxml2::XMLElement *descTag = doc.NewElement("Description");
            tinyxml2::XMLElement *statusTag = doc.NewElement("Status");
            nameTag->SetText(project.proName.c_str());
            descTag->SetText(project.proDesc.c_str());
            statusTag->SetText(project.proStatus.c_str());
            projectTag->InsertFirstChild(statusTag);
            projectTag->InsertFirstChild(descTag);
            projectTag->InsertFirstChild(nameTag);
            projectsList->InsertFirstChild(projectTag);
        }
        employee->InsertFirstChild(projectsList);
        employee->InsertFirstChild(name);
        employee->InsertFirstChild(id);
        root->InsertFirstChild(employee);
        Employee *employeeToDelete = currentEmp;
        currentEmp = currentEmp->next;
        delete employeeToDelete;
    }
    if (doc.SaveFile(rFileName.c_str()) == tinyxml2::XML_SUCCESS)
    {
        std::cout << "Successfull saved to :" << rFileName << std::endl;
    }
    else
    {
        std::cerr << "Error saving XML file :" << std::endl;
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
