#include <bits/stdc++.h>
#include "adder.h"
#define ord(x) ((int)x - 48)
#define chr(x) ((char)(x + 48))
typedef long long ll;
using namespace std;

string InputLine;

// Alpha.
vector <int> Alpha;
int RepeatIdx;

// Operands.
vector <int> X;
vector <int> Y;

// Sum.
vector <int> S;

// Keeps track of the length of S.
int Len;

template<typename T>
void PrintVector(const T& v, ostream &fs)
{
    for (auto it:v)
    {
        fs << it << " ";
    }
    fs << "\n";
}

int main()
{
    Init();
    ReadInputs();
    PadOperands();
    assert(X.size() == Y.size());
    Len = X.size();

    // Compute the initial S.
    for (int i = 0; i < Len; i++)
    {
        S.push_back(X[i] + Y[i]);
    }

    S.push_back(0);
    Len++;
    PassOne();
    PassTwoThree();

    reverse(S.begin(), S.end());
    ofstream ofs("output.out");
    // cout << "S: ";
    PrintVector(S, ofs);
    ofs.close();
}

void Init()
{
    // Clear everything.
    Alpha.clear();
    X.clear();
    Y.clear();
    S.clear();
    Len = 0;
    InputLine.clear();
}

void ReadInputs()
{
    ifstream inp("input.in");

    // Read the continued fraction of alpha.
    cout << "CF: ";
    getline(inp, InputLine);
    stringstream parse(InputLine);
    int d;

    // Read the 0.
    parse >> d;

    while (parse >> d)
    {
        Alpha.push_back(d);
        cout << d << " ";
    }

    cout << "\n";

    // Read the index post which the CF repeats.
    getline(inp, InputLine);
    parse.clear();
    parse.str(InputLine);
    parse >> RepeatIdx;
    cout << "RI: " << RepeatIdx << "\n";
    RepeatIdx--;

    // At least one element required in Alpha.
    // To ensure Alpha <= 1, we only provide as input the part after the
    // semicolon in the CF representation = [a0; a1, a2, a3, ...].
    int sz_d = Alpha.size();
    assert(sz_d >= 1);

    // Uncomment the below line to only consider alpha < 0.5.
    // assert(Alpha[0] >= 2);


    // Read the operands in the ostrowski representation.
    getline(inp, InputLine);
    parse.clear();
    parse.str(InputLine);
    while (parse >> d)
    {
        X.push_back(d);
    }

    getline(inp, InputLine);
    parse.clear();
    parse.str(InputLine);
    while (parse >> d)
    {
        Y.push_back(d);
    }

    inp.close();

    cout << "X: ";
    PrintVector(X, cout);
    cout << "Y: ";
    PrintVector(Y, cout);

    reverse(X.begin(), X.end());
    reverse(Y.begin(), Y.end());
}

void PadOperands()
{
    if (X.size() != Y.size())
    {
        while (X.size() < Y.size())
        {
            X.push_back(0);
        }

        while (Y.size() < X.size())
        {
            Y.push_back(0);
        }
    }

    Len = X.size();
    for (int i = 0; i < Len + 5; i++)
    {
        Alpha.push_back(Alpha[RepeatIdx + i]);
    }
}

void PassOne()
{
    Len = S.size();
    for (int k = Len-1; k > 2; k--)
    {
        // Look at the window of size 4.
        if (S[k] < Alpha[k] && S[k-1] > Alpha[k-1] && S[k-2] == 0)
        {
            S[k]++;
            S[k-1] -= Alpha[k-1] - 1;
            S[k-2] = Alpha[k-2] - 1;
            S[k-3]++;
        }
        else if (S[k] < Alpha[k] &&
                S[k-1] >= Alpha[k-1] &&
                S[k-1] <= 2*Alpha[k-1] &&
                S[k-2] > 0)
        {
            S[k]++;
            S[k-1] -= Alpha[k-1];
            S[k-2]--;
        }
        // Else leave the window unchanged.
    }

    // Work on the tail (of size 3).
    if (S[2] < Alpha[2] && S[1] > Alpha[1] && S[0] == 0)
    {
        S[2]++;
        S[1] -= Alpha[1] + 1;
        S[0] = Alpha[0] - 1;
    }
    else if (S[2] < Alpha[2] &&
            S[1] >= Alpha[1] &&
            S[0] <= Alpha[0] &&
            S[0] > 0)
    {
        S[2]++;
        S[1] -= Alpha[1];
        S[0]--;
    }
    else if (S[2] < Alpha[2] &&
            S[1] >= Alpha[1] &&
            S[0] > Alpha[0])
    {
        S[2]++;
        S[1] -= Alpha[1] - 1;
        S[0] -= Alpha[0] + 1;
    }
    else if (S[1] < Alpha[1] && S[0] >= Alpha[0])
    {
        S[1]++;
        S[0] -= Alpha[0];
    }
    // Else leave unchanged.
}

void PassTwoThree()
{
    S.push_back(0);
    Len++;

    for (int k = 2; k < Len; k++)
    {
        if (S[k] < Alpha[k] && S[k-1] == Alpha[k-1] && S[k-2] > 0)
        {
            S[k]++;
            S[k-1] = 0;
            S[k-2]--;
        }
        // Else leave unchanged.
    }

    S.push_back(0);
    Len++;
    for (int k = Len-1; k >= 2; k--)
    {
        if (S[k] < Alpha[k] && S[k-1] == Alpha[k-1] && S[k-2] > 0)
        {
            S[k]++;
            S[k-1] = 0;
            S[k-2]--;
        }
    }
}
