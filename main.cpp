#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct task
{
private:
    string contents{""};
    short completion{0};
    string deadline{""};

public:
    task(string conts = "", short comp = 0, string dl = "")
    {
        contents = conts;
        completion = comp;
        deadline = dl;
    }
    string getContents()
    {
        return contents;
    }
    short getCompletion()
    {
        return completion;
    }
    string getDeadline()
    {
        return deadline;
    }
};

struct list
{
    vector<task> listVec;
    // string serialize() {}
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
    void saveList()
    {
        ofstream listFile("list.txt", ios::app);

        int vecSize = listVec.size();
        for (int i = 0; i < vecSize; i++)
        {
            listFile << listVec[i].getContents() << endl;
        }
    }

    // string deserialize() {}
    // void loadList() {}
};

struct CLI
{
    list mainList;

    void commandsList()
    {
        cout << "1->Add Task" << "\n2->Delete Task" << "\n3->Mark Task" << "\n4->Edit Task" << "\n5->View Tasks"
             << "\n6->Exit App" << endl;
    }
    short userChoice()
    {
        short x;
        cout << "->";
        while (!(cin >> x))
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
    void performCommand(short commandNumber)
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
        case 6:
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
    CLI cli;
    return 0;
}