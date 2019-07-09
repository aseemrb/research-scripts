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
#define ord(x) ((int)(x) - 48)
#define chr(x) ((char)(x + 48))
using namespace std;
typedef long long ll;

// Constants.
const int MAXN = 5e3; // This has to be >= max(MaxRows, MaxCols).
const int MaxRows = 5e3;
const int MaxCols = 5e3;
const int MaxPlace = 50;

// Global values.
string Sequence;
string MatrixIndex[MAXN];
vector <char> HankelRow;
vector < pair <string, vector <char> > > UniqueRows;
map <string, set <int> > EquivalenceClasses;

// Example:
// If CF of alpha = [0, 1, 3, 1, 2, 2, ...] then D_alpha = {0, 1, 3, 1, 2} and RepeatIdx = 4.
vector < int > D_alpha;
int RepeatIdx;
ll PlaceValue[MaxPlace];

// Helper functions.
template<typename T>
void PrintVector(const T& v, ofstream& fs)
{
    copy(v.cbegin(), v.cend(), ostream_iterator<typename T::value_type>(fs, " "));
}

// This is required so that we can relax the restriction on input validity.
template<typename T>
bool VectorEqualHankel(std::vector<T> const &v1, std::vector<T> const &v2)
{
    int n = v1.size();
    if (v2.size() != n) return false;
    for (int i = 0; i < n; i++)
    {
        if ((v1[i] != v2[i]) && (v1[i] != '*') && (v2[i] != '*'))
        {
            return false;
        }
    }

    return true;
}

void Init();
void InitMatrix();
void FillHankelRow(int row);
bool IsValidOstRep(string rep);
int IntegerFromOstRep(string rep);

int main()
{
    Init();
    InitMatrix();
    int rowStart = 1, rowEnd = MaxRows;

    // Open file stream.
    ofstream hankel;
    hankel.open("hankel.txt", ofstream::trunc);

    for (int row = rowStart; row < rowEnd; row++)
    {
        HankelRow.clear();
        FillHankelRow(row);

        bool seen = 0;
        for (auto it = UniqueRows.begin(); it != UniqueRows.end(); it++)
        {
            if (VectorEqualHankel((it->second), HankelRow))
            {
                EquivalenceClasses[it->first].insert(IntegerFromOstRep(MatrixIndex[row]));
                seen = 1;
                break;
            }
        }

        if (!seen)
        {
            hankel << row << ": ";
            PrintVector(HankelRow, hankel);
            hankel << "\n";
            UniqueRows.push_back(make_pair(MatrixIndex[row], HankelRow));
            EquivalenceClasses[MatrixIndex[row]] = {IntegerFromOstRep(MatrixIndex[row])};
        }
    }

    cout << "Equivalence classes written in 'hankel.txt'.\n";
    cout << "Total unique rows found: " << UniqueRows.size() << "\n";
    hankel << "\n------------------------------\n";
    hankel << "Equivalence Classes:\n";

    for (auto it = EquivalenceClasses.begin(); it != EquivalenceClasses.end(); it++)
    {
        hankel << it->first << ": ";
        PrintVector(it->second, hankel);
        hankel << "\n";
    }

    hankel.close();
    return 0;
}

void Init()
{
    cout << "Reading continued fraction of alpha.\n";
    cout << "CF: ";
    ifstream alpha;
    alpha.open("alpha.cf");
    int d;
    while (1)
    {
        alpha >> d;
        if (d == -1)
        {
            // Input for D_alpha ends.
            break;
        }

        D_alpha.push_back(d);
        cout << d << " ";
    }

    alpha >> RepeatIdx;


    cout << "\n";
    cout << "RI: " << RepeatIdx << "\n\n";
    alpha.close();

    // At least two elements required in D_alpha.
    int sz_d = D_alpha.size();
    assert(sz_d >= 2);

    // Fill up the place values of the number system.
    PlaceValue[0] = 1;
    PlaceValue[1] = D_alpha[1];

    int k = 2;
    // if (D_alpha[1] == 1)
    // {
    //     // D_alpha[1] = 1 means that we will have two 1's as place values.
    //     // So the CF must have something after [0, 1, ...].
    //     assert(sz_d >= 3);
    //     PlaceValue[1] = D_alpha[2] + 1;
    //     k = 3;
    // }

    for(int i = 2; i < MaxPlace; i++, k++)
    {
        if (k == sz_d) k = RepeatIdx;

        // Abort if overflow is detected.
        if ((PlaceValue[i] > LLONG_MAX/D_alpha[k]) ||
            (D_alpha[k] * PlaceValue[i - 1] > LLONG_MAX - PlaceValue[i-2]))
        {
            cout << "Abort: Place values will overflow.\n";
            exit(0);
        }

        PlaceValue[i] = D_alpha[k] * PlaceValue[i - 1] + PlaceValue[i - 2];
    }
}

void InitMatrix()
{
    ifstream rep("ost-rep.txt");
    ifstream seq("sequence.txt");
    getline(seq, Sequence);
    seq.close();

    MatrixIndex[0] = "";
    int i = 1;
    while (getline(rep, MatrixIndex[i++]))
    {
        if (i == MAXN) break;
    }

    rep.close();
}

bool IsValidOstRep(string rep)
{
    if (rep == "") return false;
    int n = rep.length();
    if(ord(rep[n-1]) >= D_alpha[1]) return false;
    int k = 2;
    for (int i = 2; i <= n; i++,k++)
    {
        if(k == D_alpha.size()) k = RepeatIdx;
        if(ord(rep[n-i]) > D_alpha[k])
        {
            return false;
        }
        else if (ord(rep[n-i]) == D_alpha[k] && ord(rep[n-i+1]) > 0)
        {
            return false;
        }
    }

    return true;
}

int IntegerFromOstRep(string rep)
{
    int value = 0, n = rep.length();
    if (n > MaxPlace)
    {
        cout << "Representation out of bounds.\n";
        cout << "Current threshold: " << MaxPlace << " digits.\n";
        exit(0);
    }

    for (int i = n - 1; i >= 0; i--)
    {
        value += ord(rep[i])*PlaceValue[n-1-i];
    }

    return value;
}

// Fill HankelRow with the matrix entries for given scenario.
void FillHankelRow(int row)
{
    string leftWord = MatrixIndex[row];
    string s;

    for (int col = 0; col < MaxCols; col++)
    {
        // MatrixIndex[col] is the rightWord.
        s = leftWord + MatrixIndex[col];
        if (IsValidOstRep(s))
        {
            HankelRow.push_back(Sequence[IntegerFromOstRep(s)]);
        }
        else
        {
            // cout << "Invalid: " << s << "\n";
            // Relaxation character. Equates to everything.
            HankelRow.push_back('-');
        }
    }
}
