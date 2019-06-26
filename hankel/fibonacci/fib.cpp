/*
Copyright (c) 2018 - Aseem Baranwal

This script attempts to guess the automaton for an infinite sequence of symbols expected to be
Fibonacci-automatic. File fib-rep.cpp is used to generate fib-rep.txt which contains the
representation of integers in the Fibonacci number system. The script uses these representations to
guess the automaton by constructing the corresponding Hankel matrix.

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
const int NumFib = 40;

// Global values.
string SEQUENCE;
string MatrixIndex[MaxRows];
bitset < MaxCols > HankelRow;
vector < pair < int, bitset < MaxCols > > > UniqueRows;
map < int, vector < int > > EquivalenceClasses;
ll Fibs[NumFib];

// Helper functions.
void Init();
void InitMatrix(string repfile);
void PrintVector(vector<int> &v, fstream& fs);
void FillHankelRow(int row);
int IntegerFromFibRep(string frep);

int main(int argc, char* argv[])
{
    Init();
    InitMatrix("fib-rep.txt");
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
    Fibs[0] = 1;
    Fibs[1] = 2;
    for(int i = 2; i < NumFib; i++)
    {
        Fibs[i] = Fibs[i - 1] + Fibs[i - 2];
    }
}

// Create a series of state words for the said adder base.
void InitMatrix(string repfile)
{
    ifstream repr(repfile);
    ifstream seq("sequence.txt");
    string line;
    while(getline(seq, line))
    {
        SEQUENCE = line;
        break;
    }
    seq.close();

    int i = 0;
    while (getline(repr, MatrixIndex[i++]))
    {
        if (i == MaxRows) break;
    }

    repr.close();
}

int IntegerFromFibRep(string frep)
{
    int num = 0, n = frep.length();
    for (int i = n-1; i >= 0; i--)
    {
        num += ord(frep[i])*Fibs[n-1-i];
    }

    return num;
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
        int idx = IntegerFromFibRep(s);
        if (SEQUENCE[idx] == '1')
        {
            // Set the corresponding bit to 1 for this matrix row.
            HankelRow.set(col);
        }
    }
}
