#include <iostream>
#include <vector>
#include <string>
using namespace std;

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

int stringToInt(string x)
{
    char y;
    for (int i = 0; i < x.size(); i++)
    {
        if (charToInt(x[i]) == -1)
        {
            return -1;
            exit;
        }
    }
    return stoi(x);
}

int checkUserInput(string errorMessage = "ERROR!")
{
    string userInput;

    while (getline(cin, userInput, '\n') && (userInput.empty() || charToInt(userInput[0]) > 6 || charToInt(userInput[0]) == -1))
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
