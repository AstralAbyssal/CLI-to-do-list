#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>
#include "objs.h"

using namespace std;

taskList list("Task List"); // declare list

void commandsList()
{
    cout << "1->Add Task" << "\n2->Delete Task" << "\n3->Mark Task" << "\n4->Edit Task" << "\n5->View Tasks"
         << "\n6->Clear List" << "\n\n0->Exit App" << endl;
}

void welcomePanel()
{
    cout << "Welcome to CLI TO-DO\n";

    list.viewList();

    cout << "Type the number of the command you want to make:-\n";
    commandsList();
    cout << "-->";
    int choice = getValidInt();
    int index;

    while (!checkIntBounds(choice, 6, 0))
    {
        cout << "Error! number out of bounds please type a number from 0 to 6 ->";
        choice = getValidInt();
    }
    switch (choice)
    {

    case 1:
        list.addTask();
        list.saveList();
        welcomePanel();

        break;
    case 2:
        list.viewList();
        cout << "please type the index of the list you want to remove ->";
        list.removeTask(getValidInt());
        list.saveList();
        welcomePanel();

        break;
    case 3:
        list.viewList();
        cout << "please type the index of the list you want to mark ->";
        list.markTask(getValidInt());
        list.saveList();
        welcomePanel();

        break;
    case 4:
        list.viewList();
        cout << "please type the index of the list you want to edit ->";
        list.editTask(getValidInt());
        list.saveList();
        welcomePanel();

        break;
    case 5:
        list.viewList();
        welcomePanel();

    case 6:
        cout << "Type 1 if you are sure you want to clear the list ->";
        if (getValidInt() == 1)
        {
            list.listVec.clear();
            list.saveList();
            cout << "LIST CLEARED" << endl;
        }
        welcomePanel();

    case 0:
        list.saveList();
        exit;
        break;
    default:
        welcomePanel();
        break;
    }
}

int main()
{
    filesystem::create_directory("AppData/"); // declare AppData directory
    welcomePanel();
    return 0;
}

// make sure the list is always visible for user
// make the code more readable and scalable