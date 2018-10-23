#include "helpers.h"
using namespace std;

// Constants.
const int MaxCols = 1e5;
const int WordLength = 30;

// Global values.
ll Pells[WordLength];
string Sequence[MaxCols];
bitset < MaxCols > HankelRow;
vector < pair < int, bitset < MaxCols > > > UniqueRows;
map < int, vector < int > > EquivalenceClasses;

// Denotes that in the representation of a number in Pell adder base,
// digits from 0 to DigitBase - 1 will be used.
// This will serve as the base for representing the triplet projection
// of x, y, z.
const int DigitBase = 3;

// Denotes the base for representation of states.
// States are triplets in base DigitBase. Hence StateBase is always the
// cube of DigitBase.
const int StateBase = 27;

// Initialize Fibo and Pell values.
void Initialize()
{
    // Fibo and Pell numbers.
    Pells[0] = 1;
    Pells[1] = 2;
    for(int i = 2; i < WordLength; i++)
    {
        Pells[i] = 2 * Pells[i - 1] + Pells[i - 2];
    }
}

// Create a sequence of state words for the said adder base.
void CreateSequence()
{
    // This string represents the column number in given base.
    string scol = "";
    scol += chr(0);

    for (int i = 0; i < MaxCols; i++)
    {
        Sequence[i] = scol;
        scol = GetSuccessor(scol, StateBase);
    }
}

// Fill HankelRow with the matrix entries for given scenario.
// HankelRow is a bitset, hence the 0th member is the LSD.
void FillHankelRow(int row)
{
    string leftWord = Sequence[row];
    string s;

    for (int col = 0; col < MaxCols; col++)
    {

        // Sequence[col] is the rightWord.
        s = leftWord + Sequence[col];
        int n = s.length();

        // cout << "s is: " << s << "\n";
        string triplet;
        ProblemInstance xyz = {0, 0, 0};

        int j = 0;

        // prev0[i] tells if triplet[i] was a 0 previously. We reject inputs where we don't have
        // a 0 after every 2 that is present.
        bool prev0[3] = {false, false, false};

        // We are scanning in reverse, LSD.
        for (int i = n-1; i >= 0; i--)
        {
            triplet = GetTriplet(ord(s[i]), DigitBase);

            // If there's a non-0 after a 2, reject.
            if (((!prev0[0]) && ord(triplet[0]) == 2) ||
                ((!prev0[1]) && ord(triplet[1]) == 2) ||
                ((!prev0[2]) && ord(triplet[2]) == 2) ||
                (i == n-1 && (ord(triplet[0]) == 2 || ord(triplet[1]) == 2 || ord(triplet[2]) == 2)))
            {
                xyz.x = xyz.y = xyz.z = 1;
                break;
            }

            // Update prev0.
            prev0[0] = (ord(triplet[0]) == 0);
            prev0[1] = (ord(triplet[1]) == 0);
            prev0[2] = (ord(triplet[2]) == 0);

            xyz.x += ord(triplet[0]) * Pells[j];
            xyz.y += ord(triplet[1]) * Pells[j];
            xyz.z += ord(triplet[2]) * Pells[j];
            j++;
        }

        if (row == 828 && col == 414)
        {
            cout << ord(s[0]) << " ";
            cout << ord(s[1]) << " ";
            cout << ord(s[2]) << " ";
            cout << ord(s[3]) << " ";
            cout << ord(s[4]) << " ";
            cout << " XYZ: " << xyz.x << " " << xyz.y << " " << xyz.z << " -- " << col << "\n";
        }
        if (xyz.x + xyz.y == xyz.z)
        {
            // Set the corresponding bit to 1 for this matrix row.
            HankelRow.set(col);
        }
    }
}

int main(int argc, char* argv[])
{
    Initialize();

    CreateSequence();
    int rowStart = 0, rowEnd = MaxCols;

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
