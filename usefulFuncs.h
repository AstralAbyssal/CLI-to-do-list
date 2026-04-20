#include <iostream>
#include <string>
#include <stdexcept>
#include <vector>

using namespace std;

string getValidString()
{
    string input;
    while (getline(cin, input))
    {
        try
        {
            if (input.empty())
            {
                throw invalid_argument("input can't be empty");
                cin.clear();
                cin.ignore(1000, '\n');
            }
            return input;
        }
        catch (invalid_argument)
        {
            cout << "input can't be empty\n";
        }
    }
    return input;
}

int getValidInt()
{
    string input;
    while (getline(cin, input))
    {
        try
        {
            return stoi(input);
            if (input.empty())
            {
                throw invalid_argument("input can't be empty");
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }
        catch (invalid_argument)
        {
            cout << "invalid input, please type a number\n";
        }
        catch (out_of_range)
        {
            cout << "invalid input, please type a feasable number\n";
        }
    }
    return stoi(input);
}

bool checkIntBounds(int input, int upperBound, int lowerBound = 0)
{
    if (input > upperBound || input < lowerBound)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

vector<string> splitString(string temp)
{
    vector<string> tempVector;
    string tempContent = "";
    for (char x : temp)
    {
        if (x != ':')
        {
            tempContent += x;
        }
        else
        {
            tempVector.push_back(tempContent);
            tempContent = "";
        }
    }
    return tempVector;
}