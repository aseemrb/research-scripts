#include <bits/stdc++.h>
#define ord(x) ((int)(x)-48)
using namespace std;
typedef long long ll;

// Constants.
const int MaxRows = 1000;
const int MaxCols = 1000;
const int MAXN = max(MaxRows, MaxCols);

// Global values.
string vn;
string Sequence[MAXN];
bitset < MaxCols > HankelRow;
vector < pair < int, bitset < MaxCols > > > UniqueRows;
map < int, vector < int > > EquivalenceClasses;

string NextRadixCandidate(string x)
{
    if (x == "") return "0";
    bool done = 0;
    int l = x.length();
    int i = l;
    while (i--)
    {
        if (x[i] == '0')
        {
            x[i] = '1';
            done = 1;
            break;
        }
    }

    if (i >= 0)
    {
        for (i += 1; i < l; i++)
            x[i] = '0';
    }
    else
    {
        x = "0";
        for (i = 0; i < l; i++)
            x = x + "0";
    }

    return x;
}

// Create a sequence of state words for the said adder base.
void CreateSequence()
{
    ifstream vnf("vn.txt");
    string line;
    getline(vnf, vn);
    vnf.close();
    Sequence[0] = "";
    for (int i = 1; i < max(MaxRows, MaxCols); i++)
    {
        Sequence[i] = NextRadixCandidate(Sequence[i-1]);
        // cout << Sequence[i] << "\n";
    }
}

// Print an int vector to file with spaces between elements.
// Newline after the last element.
void PrintVector(vector<int> &v, fstream& fs)
{
    for (auto it = v.begin(); it != v.end(); it++) fs << (*it) << " ";
    fs << "\n";
}

string IntegerToBinStr(int n)
{
    if (n == 0) return "0";
    string s = "";
    while (n)
    {
        if (n&1) s = "1" + s;
        else s = "0" + s;
        n >>= 1;
    }

    return s;
}

// Fill HankelRow with the matrix entries for given scenario.
// HankelRow is a bitset, hence the 0th member is the LSD.
void FillHankelRow(int row)
{
    string leftWord = IntegerToBinStr(row);
    string s;

    for (int col = 0; col < MaxCols; col++)
    {

        // Sequence[col] is the rightWord.
        s = leftWord + Sequence[col];
        int idx = stoi(s, nullptr, 2);
        // cout << s << "\n";
        // if (row == 0 || row == 4)
        //     cout << row << ": " << s << ": " << vn[idx] << "\n";
        if (vn[idx] == '1')
        {
            // Set the corresponding bit to 1 for this matrix row.
            HankelRow.set(col);
        }
    }
}

int main(int argc, char* argv[])
{
    CreateSequence();
    // cout << vn.length() << "\n";
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
        // int bnum = stoi(Sequence[row], nullptr, 2);
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
