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

int main()
{
    list l;
    l.addTask(l.newTask("First Task"));
    l.saveList();
    return 0;
}