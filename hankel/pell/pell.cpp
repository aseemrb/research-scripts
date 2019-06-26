/*
Copyright (c) 2018 - Aseem Baranwal

This script attempts to guess the automaton for an infinite sequence of symbols expected to be
Pell-automatic. File pell-rep.cpp is used to generate pell-rep.txt which contains the representation
of integers in the Pell number system. The script uses these representations to guess the automaton
by constructing the corresponding Hankel matrix.

Input   : File "sequence.txt" containing the first few (order of 10^5) symbols of the sequence.
Output  : File(s) "hankel.txt" containing the number of states found in the guessed automaton.
*/

#include <bits/stdc++.h>
#define ord(x) ((int)(x)-48)
using namespace std;
typedef long long ll;

// Constants.
const int MaxRows = 1e2;
const int MaxCols = 1e2;
const int NumPell = 20;

// Global values.
string SEQUENCE;
string MatrixIndex[MaxRows];
bitset < MaxCols > HankelRow;
vector < pair < int, bitset < MaxCols > > > UniqueRows;
map < int, vector < int > > EquivalenceClasses;
ll Pells[NumPell];

// Helper functions.
void Init();
void InitMatrix(string repfile);
void PrintVector(vector<int> &v, fstream& fs);
void FillHankelRow(int row);
int IntegerFromPellRep(string prep);

int main(int argc, char* argv[])
{
    Init();
    InitMatrix("pell-rep.txt");
    int rowStart = 0, rowEnd = MaxRows;

    if (argc == 3)
    {
        rowStart = atoi(argv[1]);
        rowEnd = atoi(argv[2]);
    }

    // Open file stream.
    fstream hankel;
    if (argc == 3)
    {
        hankel.open(
            "hankel-" + string(argv[1]) + "-" + string(argv[2]) + ".txt",
            fstream::in | fstream::out | std::fstream::app);
    }
    else
    {
        hankel.open(
            "hankel.txt",
            fstream::in | fstream::out | std::fstream::app);
    }

    // Set floating point precision.
    cout << fixed << showpoint;
    cout << setprecision(2);

    for (int row = rowStart, i = 0; row < rowEnd; row++, i++)
    {
        if (i == 500)
        {
            cout
                << "\r" << (100.0 * (row - rowStart)) / (rowEnd - rowStart)
                << "% complete " << flush;
            i = 0;
        }

        HankelRow.reset();
        FillHankelRow(row);

        bool seen = 0;
        for (auto it = UniqueRows.begin(); it != UniqueRows.end(); it++)
        {
            bitset<MaxCols> xorWithRow = ((it->second) ^ HankelRow);
            if (xorWithRow.none())
            {
                EquivalenceClasses[it->first].push_back(row);
                seen = 1;
                break;
            }
        }

        if (!seen)
        {
            hankel << row << ": " << HankelRow << "\n";
            UniqueRows.push_back(make_pair(row, HankelRow));
            EquivalenceClasses[row] = {row};
        }
    }

    cout << "\r" << "100.00% complete \n";
    cout << "Total unique rows found: " << UniqueRows.size() << "\n";
    hankel << "\n------------------------------\nEquivalence Classes:\n";

    for (auto it = EquivalenceClasses.begin(); it != EquivalenceClasses.end(); it++)
    {
        hankel << it->first << ": ";
        PrintVector(it->second, hankel);
    }

    hankel.close();
    return 0;
}

void Init()
{
    Pells[0] = 1;
    Pells[1] = 2;
    for(int i = 2; i < NumPell; i++)
    {
        Pells[i] = 2 * Pells[i - 1] + Pells[i - 2];
    }
}

void InitMatrix(string repfile)
{
    ifstream prep(repfile);
    ifstream seq("sequence.txt");
    string line;
    while(getline(seq, line))
    {
        SEQUENCE = line;
        break;
    }
    seq.close();

    int i = 0;
    while (getline(prep, MatrixIndex[i++]))
    {
        if (i == MaxRows) break;
    }
    prep.close();
}

int IntegerFromPellRep(string prep)
{
    int idx = 0, n = prep.length();
    for (int i = n-1; i >= 0; i--)
    {
        idx += ord(prep[i])*Pells[n-1-i];
    }

    return idx;
}

// Print an int vector to file with spaces between elements.
// Newline after the last element.
void PrintVector(vector<int> &v, fstream& fs)
{
    for (auto it = v.begin(); it != v.end(); it++) fs << (*it) << " ";
    fs << "\n";
}

// Fill HankelRow with the matrix entries for given scenario.
// HankelRow is a bitset, hence the 0th member is the LSD.
void FillHankelRow(int row)
{
    string leftWord = MatrixIndex[row];
    string s;

    for (int col = 0; col < MaxCols; col++)
    {
        // MatrixIndex[col] is the rightWord.
        s = leftWord + MatrixIndex[col];
        int idx = IntegerFromPellRep(s);
        if (SEQUENCE[idx] == '1')
        {
            // Set the corresponding bit to 1 for this matrix row.
            HankelRow.set(col);
        }
    }
}
