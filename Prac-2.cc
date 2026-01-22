#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int numOfInputSymbols, numOfStates, numOfAccepting;
    int initialState;

    cout << "Number of input symbols : ";
    cin >> numOfInputSymbols;

    vector<char> inputSymbol(numOfInputSymbols);
    cout << "Input symbols : ";
    for (int i = 0; i < numOfInputSymbols; i++)
    {
        cin >> inputSymbol[i];
    }

    cout << "Enter number of states : ";
    cin >> numOfStates;

    cout << "Initial state : ";
    cin >> initialState;

    cout << "Number of accepting states : ";
    cin >> numOfAccepting;

    vector<int> acceptingStates(numOfAccepting);
    cout << "Accepting states : ";
    for (int i = 0; i < numOfAccepting; i++)
    {
        cin >> acceptingStates[i];
    }

    vector<vector<int>> transitionTable(numOfStates + 1, vector<int>(numOfInputSymbols));

    cout << "Transition table :" << endl;
    for (int i = 1; i <= numOfStates; i++)
    {
        for (int j = 0; j < numOfInputSymbols; j++)
        {
            cout << i << " to " << inputSymbol[j] << " -> ";
            cin >> transitionTable[i][j];
        }
    }

    string inputString;
    cout << "Input string : ";
    cin >> inputString;

    int currentState = initialState;

    for (int i = 0; i < inputString.length(); i++)
    {
        for (int j = 0; j < numOfInputSymbols; j++)
        {
            if (inputString[i] == inputSymbol[j])
            {
                currentState = transitionTable[currentState][j];
                break;
            }
        }
    }

    bool isAccepted = false;
    for (int i = 0; i < numOfAccepting; i++)
    {
        if (currentState == acceptingStates[i])
        {
            isAccepted = true;
            break;
        }
    }

    if (isAccepted)
        cout << "Valid String";
    else
        cout << "Invalid String";

    return 0;
}