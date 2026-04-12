#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <bits/stdc++.h>
#include <cctype>

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

task parse(string fileName, int lineIndex)
{
    ifstream readFile(fileName);
    string lineString;

    bool comp = 0;
    string conts = "";

    string readNumber = "";
    int currentCharIndex = 0;

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

struct taskList
{
    vector<task> listVec;
    task newTask(string conts = "", short comp = 0, string dl = "")
    {
        task nTask(conts, comp, dl);
        return nTask;
    }

    void addTask(task temp)
    {
        listVec.push_back(temp);
    }
    void removeTask(int ind)
    {
        listVec.erase(listVec.begin() + (ind - 1));
    }

    string serialize(task t, int i)
    {
        string x;
        string tempString = t.getContents();
        x = to_string(tempString.size()) + ':' + tempString + ':' + to_string(t.getCompletion());
        return x;
    }

    void saveList()
    {
        ofstream listFile("list.txt");

        int vecSize = listVec.size();
        for (int i = 0; i < vecSize; i++)
        {
            listFile << serialize(listVec[i], i) << endl;
        }
    }

    // task deserialize(int lineIndex)
    //{
    //
    // }
    //  void loadList() {}
};

struct CLI
{
    taskList mainList;

    void commandsList()
    {
        cout << "1->Add Task" << "\n2->Delete Task" << "\n3->Mark Task" << "\n4->Edit Task" << "\n5->View Tasks"
             << "\n\n0->Exit App" << endl;
    }
    int userChoice()
    {
        int x;
        cout << "->";
        while (!(cin >> x) || x > 5 || x < 0)
        {
            cout << "Invalid input! please choose a valid number from the list\n->";
            cin.clear();
            cin.ignore(1000, '\n');
        }
        return x;
    }
    void welcomePanel()
    {
        cout << "Welcome to CLI TO-DO\n";
        cout << "Type the number of the command you want to make:-\n";
        commandsList();
        performCommand(userChoice());
    }
    void performCommand(int commandNumber)
    {
        string x;

        switch (commandNumber)
        {
        case 1:
            cout << "please type something into your new task's contents or type \'!0\' to go back to the welcome panel\n";

            cout << "--> ";
            cin.ignore();
            getline(cin, x);
            if (x == "!0")
            {
                welcomePanel();
                while (x.empty())
                {
                    cout << "please type something into your new task's contents\n-->";
                    getline(cin, x);
                }
            }
            mainList.addTask(mainList.newTask(x));
            welcomePanel();
            break;
        case 2:
            int x;
            cout << "please type the index of the task you want to remove \'!0\' to go back to the welcome panel\n-->";
            cin.ignore();
            while (!(cin >> x))
            {
                cout << "Invalid input! please choose a valid index\n-->";
                cin.clear();
                cin.ignore(1000, '\n');
            }
            mainList.removeTask(x);
            welcomePanel();
            break;
        case 5:
            cout << "dumbahh";
            welcomePanel();

            break;
        case 0:
            exit;
            break;
        default:
            break;
        }
    }
    CLI()
    {
        welcomePanel();
    }
    ~CLI()
    {
        mainList.saveList();
    }
};

int main()
{
    // CLI cli;
    parse("list.txt", 4).viewTask();
    return 0;
}