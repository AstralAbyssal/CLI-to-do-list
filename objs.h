#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "usefulFuncs.h"

using namespace std;

struct task
{
private:
    string contents{""};
    short completion{0};
    string deadline{"DD/MM/YYYY"};

public:
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

    // contents setter and getter
    string getContents()
    {
        return contents;
    }
    void setContents(string conts = "")
    {
        contents = conts;
    }

    // completion mark setter and getter
    void setCompletion(bool comp = 0)
    {
        completion = comp;
    }
    short getCompletion()
    {
        return completion;
    }

    // deadline setter and getter
    void setDeadLine(string dl)
    {
        deadline = dl;
    }
    string getDeadline()
    {
        return deadline;
    }
};

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

struct taskList
{
    vector<task> listVec;

    void addTask(string conts = "", int comp = 0, string dl = "DD/MM/YYYY")
    {
        task temp(conts, comp, dl);
        listVec.push_back(temp);
    }
    void addTask(task tempTask)
    {
        listVec.push_back(tempTask);
    }
    void removeTask(int ind)
    {
        listVec.erase(listVec.begin() + (ind - 1));
    }
    void markTask(int index, bool setCompletionMark)
    {
        listVec[index].setCompletion(setCompletionMark);
    }
    void viewList()
    {
        for (int i = 0; i < listVec.size(); i++)
        {
            listVec[i].viewTask();
            cout << endl;
        }
    }
};

struct CLI
{
    taskList mainList;

    bool checkSaveFile(string fileName)
    {
        ifstream readFile;
        readFile.open(fileName);
        string temp;
        getline(readFile, temp);
        return !(temp.empty());
    }

    string serialize(task tempTask)
    {
        string x;
        string tempString = tempTask.getContents();
        x = to_string(tempString.size()) + ':' + tempString + ':' + to_string(tempTask.getCompletion());
        return x;
    }

    taskList loadList(bool listExists)
    {
        taskList tempList;
        if (listExists)
        {
            for (int i = 1; i <= getNumberOfLines("list.txt"); i++)
            {
                tempList.addTask(parse("list.txt", i));
            }
        }
        return tempList;
    }

    void saveList(taskList list)
    {
        ofstream wrf("list.txt");
        int vecSize = list.listVec.size();
        for (int i = 0; i < vecSize; i++)
        {
            wrf << serialize(list.listVec[i]) << endl;
        }
    }

    task parse(string fileName, int lineIndex)
    {
        ifstream readFile(fileName);
        string lineString;

        bool comp = 0;
        string conts = "";

        string readNumber = "";
        int currentCharIndex = 0;
        int totalNumberOfLines = getNumberOfLines(fileName);
        if (lineIndex > totalNumberOfLines)
        {
            lineIndex = getNumberOfLines(fileName);
        }
        for (int i = 1; i <= lineIndex; i++) // search for the line
        {
            getline(readFile, lineString);
            if (i == lineIndex)
            {
                while (lineString[currentCharIndex] != ':') // get number
                {
                    readNumber += lineString[currentCharIndex];
                    currentCharIndex++;
                }
                for (int i = currentCharIndex + 1; i <= stoi(readNumber) + currentCharIndex; i++)
                {
                    conts += lineString[i];
                    if (lineString[i + 1] == ':')
                    {
                        comp = (lineString[i + 2] == '1');
                    }
                }
            }
        }
        task tempTask(conts, comp);
        return tempTask;
    }

    void commandsList()
    {
        cout << "1->Add Task" << "\n2->Delete Task" << "\n3->Mark Task" << "\n4->Edit Task" << "\n5->View Tasks"
             << "\n6->Clear List" << "\n\n0->Exit App" << endl;
    }

    void welcomePanel()
    {
        cout << "Welcome to CLI TO-DO\n";
        cout << "Type the number of the command you want to make:-\n";
        commandsList();
        cout << "-->";
        int commandNumber = checkUserInput("Invalid input! please choose a valid number from the list\n->");
        performCommand(commandNumber);
    }
    void performCommand(int commandNumber)
    {
        string addedTaskContents;
        int chosenIndex;
        bool comp;
        string x;
        char confirm;

        switch (commandNumber)
        {
        case 0:
            exit;
            break;
        case 1:
            cout << "please type something into your new task's contents or type \'!0\' to go back to the welcome panel\n-->";
            addedTaskContents = getValidString("contents cant be empty!\n-->");
            if (addedTaskContents == "!0")
            {
                welcomePanel();
                break;
            }
            mainList.addTask(addedTaskContents);
            welcomePanel();
            break;
        case 2:
            cout << "please type the index of the task you want to remove \'0\' to go back to the welcome panel\n-->";
            chosenIndex = stringToInt(getValidString("index cant be empty!\n-->"));
            if (chosenIndex == 0)
            {
                welcomePanel();
                break;
            }
            if (chosenIndex > mainList.listVec.size())
            {
                mainList.removeTask(mainList.listVec.size());
                welcomePanel();
                break;
            }
            mainList.removeTask(chosenIndex);
            welcomePanel();
            break;
        case 3:
            cout << "please type the index of the task you want to mark \'0\' to go back to the welcome panel\n-->";
            chosenIndex = stringToInt(getValidString("index cant be empty!\n-->"));
            cout << "Set the completion to-> ";
            cin >> comp;
            mainList.listVec[chosenIndex - 1].setCompletion(comp);
            cin.ignore(1000, '\n');
            welcomePanel();
            break;
        case 4:
            cout << "please type the index of the task you want to edit \'0\' to go back to the welcome panel\n-->";
            chosenIndex = stringToInt(getValidString("index cant be empty!\n-->"));
            if (chosenIndex == 0)
            {
                welcomePanel();
                break;
            }

            cout << "please type something into your edited task's contents or type \'!0\' to go back to the welcome panel\n-->";
            addedTaskContents = getValidString("contents cant be empty!\n-->");
            if (addedTaskContents == "!0")
            {
                welcomePanel();
                break;
            }
            mainList.listVec[chosenIndex - 1].setContents(addedTaskContents);
            welcomePanel();
            break;
        case 5:

            cout << "-----------------------------" << endl;
            if (mainList.listVec.size() == 0)
            {
                cout << "Nothing to show! list is empty" << endl;
            }
            mainList.viewList();
            cout << "-----------------------------" << endl;

            cout << endl
                 << "press enter to go back to welcome panel";
            getline(cin, x);
            welcomePanel();
            break;
        case 6:
            cout << "are you sure you want to clear the list? press y/n for confirmation ->";
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y')
            {
                mainList.listVec.clear();
            }
            cin.ignore(1000, '\n');
            welcomePanel();
            break;
        default:
            cout << "Unknown Error!\n";
            welcomePanel();
            break;
        }
    }
    CLI()
    {
        mainList = loadList(checkSaveFile("list.txt"));
        welcomePanel();
    }
    ~CLI()
    {
        saveList(mainList);
    }
};
