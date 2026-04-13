#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

ofstream writeFile("list.txt", ios::app);
ifstream readFile("list.txt");

int charToInt(char x)
{
    switch (x)
    {
    case '0':
        return 0;
        break;

    case '1':
        return 1;
        break;

    case '2':
        return 2;
        break;

    case '3':
        return 3;
        break;

    case '4':
        return 4;
        break;

    case '5':
        return 5;
        break;

    case '6':
        return 6;
        break;

    case '7':
        return 7;
        break;

    case '8':
        return 8;
        break;

    case '9':
        return 9;
        break;

    default:
        return -1;
        break;
    }
}

int checkUserInput(string errorMessage = "ERROR!")
{
    string userInput;

    while (getline(cin, userInput, '\n') && (userInput.empty() || charToInt(userInput[0]) > 5 || charToInt(userInput[0]) == -1))
    {
        cout << errorMessage;
    }
    return charToInt(userInput[0]);
}

string getValidString(string errorMessage = "ERROR!")
{
    string userInput;

    while (getline(cin, userInput, '\n') && userInput.empty())
    {
        cout << errorMessage;
    }
    return userInput;
}

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
    void removeTask(int ind)
    {
        listVec.erase(listVec.begin() + (ind - 1));
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
        while (getline(readFile, temp))
            ;
        return !(temp.empty());
    }

    string serialize(task tempTask, int i)
    {
        string x;
        string tempString = tempTask.getContents();
        x = to_string(tempString.size()) + ':' + tempString + ':' + to_string(tempTask.getCompletion());
        return x;
    }

    // task deserialize(int lineIndex)
    //{
    //
    // }

    //  taskList loadList() {}

    void saveList(taskList list)
    {
        int vecSize = list.listVec.size();
        for (int i = 0; i < vecSize; i++)
        {
            writeFile << serialize(list.listVec[i], i) << endl;
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
             << "\n\n0->Exit App" << endl;
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
        int deletedTaskIndex;

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
            cout << "please type the index of the task you want to remove \'!0\' to go back to the welcome panel\n-->";
            cin.ignore();
            while (!(cin >> deletedTaskIndex))
            {
                cout << "Invalid input! please choose a valid index\n-->";
                cin.clear();
                cin.ignore(1000, '\n');
            }
        default:
            break;
        }
    }
    CLI()
    {
        // mainList = loadList();
        checkSaveFile("list.txt");
        welcomePanel();
    }
    ~CLI()
    {
        saveList(mainList);
    }
};

int main()
{
    CLI cli;
    return 0;
}