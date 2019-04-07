#include <bits/stdc++.h>
#define ord(x) ((int)(x)-48)
using namespace std;
typedef long long ll;

// Constants.
const int MaxRows = 1e3;
const int MaxCols = 100;
const int WordLength = 40;

// Global values.
string R2;
string Sequence[MaxRows+10];
bitset < MaxCols > HankelRow;
vector < pair < int, bitset < MaxCols > > > UniqueRows;
map < int, vector < int > > EquivalenceClasses;

// Global values.
ll Fibs[WordLength];

void Init()
{
    Fibs[0] = 1;
    Fibs[1] = 2;
    for(int i = 2; i < WordLength; i++)
    {
        Fibs[i] = Fibs[i - 1] + Fibs[i - 2];
    }
}

// Create a sequence of state words for the said adder base.
void CreateSequence()
{
    ifstream prep("frep.txt");
    ifstream r2("afib.txt");
    string line;
    while(getline(r2, line))
    {
        R2 = line;
        break;
    }
    r2.close();

    Sequence[0] = "";
    int i = 1;
    while (getline(prep, Sequence[i++]))
    {
        if (i == MaxRows) break;
    }

    prep.close();
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
    string leftWord = Sequence[row+1];
    string s;

    for (int col = 0; col < MaxCols; col++)
    {

        // Sequence[col] is the rightWord.
        s = leftWord + Sequence[col];
        int idx = IntegerFromFibRep(s);
        if ((row == 0 || row == 1) && col == 0)
            cout << s << " " << idx << "\n";
        if (R2[idx] == '1')
        {
            // if (idx == 10)
            //     cout << idx << " " << s << "\n";
            // Set the corresponding bit to 1 for this matrix row.
            HankelRow.set(col);
        }
    }

    // if (row == 0 || row == 1) cout << row << ": " << HankelRow << "\n";
}

int main(int argc, char* argv[])
{
    Init();
    CreateSequence();
    // cout << R2.length() << "\n";
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
