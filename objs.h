#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "usefulFuncs.h"

using namespace std;

int getNumberOfLines(string fileName)
{
    ifstream readFile(fileName);
    int numberOfLines = 0;
    string temp;
    while (getline(readFile, temp))
    {
        numberOfLines++;
    }
    return numberOfLines;
}

struct task
{
public:
    string contents{""};
    bool completion{0};
    string deadline{"DD/MM/YYYY"};

    // constructor
    task(string conts = "", short comp = 0, string dl = "DD/MM/YYYY")
    {
        contents = conts;
        completion = comp;
        deadline = dl;
    }

    void viewTask()
    {
        cout << contents << " | " << completion << " | " << deadline;
    }

    void setContents(string conts = "")
    {
        contents = conts;
    }
    void setDeadLine(string dl)
    {
        deadline = dl;
    }
    void setCompletion(bool comp = 0)
    {
        completion = comp;
    }

    void toggleCompletion()
    {
        completion = !completion;
    }

    string serialize()
    {
        string serializedTask;
        serializedTask = to_string(contents.size()) + ':' + contents + ':' + to_string(completion);
        return serializedTask;
    }
};

struct taskList
{
    string listName;
    fstream listFile;
    string listFileName;
    vector<task> listVec;
    // constructor
    taskList(string name)
    {
        listName = name;
        listFileName = "AppData/" + listName + ".txt";
        loadList();
    }

    void addTask()
    {
        task temp;
        cout << "please type the contents of the task you want to add -> ";
        temp.contents = getValidString();
        temp.completion = 0;
        cout << "please type the deadLine of the task you want to add -> ";
        temp.deadline = getValidString();
        listVec.push_back(temp);
    }

    void addTask(task tempTask)
    {
        listVec.push_back(tempTask);
    }

    void removeTask(int index)
    {
        int vectorSize = listVec.size();

        if (vectorSize == 0)
        {
            cout << "Error! List is empty" << endl;
            exit;
        }
        else if (index > vectorSize)
        {
            cout << "Error! Index is out of bounds" << endl;
            exit;
        }
        else
        {
            listVec.erase(listVec.begin() + (index - 1));
        }
    }

    void markTask(int index)
    {
        int vectorSize = listVec.size();
        if (vectorSize == 0)
        {
            cout << "Error! List is empty" << endl;
            exit;
        }
        else if (index > vectorSize)
        {
            cout << "Error! Index is out of bounds" << endl;
            exit;
        }
        else
        {
            listVec[index - 1].toggleCompletion();
        }
    }

    void editTask(int index)
    {
        cout << "please type the new contents of the task you want to edit:- ";
        string newContents = getValidString();
        int vectorSize = listVec.size();

        if (vectorSize == 0)
        {
            cout << "Error! List is empty" << endl;
            exit;
        }
        else if (index > vectorSize)
        {
            cout << "Error! Index is out of bounds" << endl;
            exit;
        }
        else
        {
            listVec[index - 1].setContents(newContents);
        }
    }

    void viewList()
    {
        cout << "---------------" << listName << "---------------" << endl;
        if (listVec.size() == 0)
        {
            cout << "Nothing to show! list is empty" << endl;
        }
        for (int i = 0; i < listVec.size(); i++)
        {
            cout << i + 1 << ": ";
            listVec[i].viewTask();
            cout << endl;
        }
        cout << "---------------" << string(listName.size(), '-') << "---------------" << endl;
    }

    string serialize(task tempTask)
    {
        return tempTask.contents + ":" + to_string(tempTask.completion) + ":" + tempTask.deadline;
    }
    task deSerialize(string tempString)
    {
        task tempTask;

        tempTask.contents = splitString(tempString, ':')[0];
        tempTask.completion = stoi(splitString(tempString, ':')[1]);
        tempTask.deadline = splitString(tempString, ':')[2];

        return tempTask;
    }

    void saveList()
    {
        int vectorSize = listVec.size();
        ofstream writeListFile(listFileName);
        if (vectorSize == 0)
        {
            writeListFile.open(listFileName, ios::trunc);
            exit;
        }
        else
        {

            for (int i = 0; i < vectorSize; i++)
            {
                writeListFile << serialize(listVec[i]) << endl;
            }
        }
    }

    void loadList()
    {
        string tempString;
        vector<task> tempVec;
        listFile.open(listFileName);
        while (getline(listFile, tempString))
        {
            listVec.push_back(deSerialize(tempString));
            if (tempString.empty())
            {
                exit;
            }
        }
    }
};
