#include <bits/stdc++.h>
#include "fibo-rep.h"
typedef long long ll;

using namespace std;

const int MX_MAT_SIZE = 2000;
const int MX_DEPTH = 6;
const string EMPTY_STRING = "";
const string LEADING_0_TRIPLET = "000";
const string FIBO_ALPHABET = "01234567";
const string SUPERFIBO_ALPHABET = "0123456789ABCDEFGHIJKLMNOPQ";

int HankelMatrix[MX_MAT_SIZE][MX_MAT_SIZE];
string Sequence[MX_MAT_SIZE];

// Generate a lexicographical sequence with words of given
// size len using characters from the given alphabet.
void GenLexSeq(
    string base,
    string const& alphabet,
    int len,
    vector<string>& sequence)
{
    if (base.length() == len)
    {
        TrimLeading0s(base);
        sequence.push_back(base);
        return;
    }

    int n = alphabet.length();
    for (int i = 0; i < n; i++)
    {
        stringstream ss;
        ss << alphabet[i];
        GenLexSeq(base + ss.str(), alphabet, len, sequence);
    }
}

// Create a Hankel Matrix with the given alphabet and size.
// First this will generate a lexicographical sequence of words
// and then check if the word (Row-Col) satisfies the automaton.
// If satisfied, put 1, else put 0 in the matrix at (Row, Col).
void CreateHankelMatrix(string alphabet, int len, int matrixSize)
{
    vector<string> seq;

    GenLexSeq(EMPTY_STRING, alphabet, len, seq);
    string s;

    for (int i = 0; i < matrixSize; i++)
    {
        Sequence[i] = seq[i];
        for (int j = 0; j < matrixSize; j++)
        {
            s = seq[i] + seq[j];
            if (seq[i] == "0" && seq[j] == "0") TrimLeading0s(s);


            // Get the triplets according to the word sequence.
            // The triplets start with the least significant digit.
            vector<string> triplets;
            for (int idx = s.size() - 1; idx >= 0;  idx--)
            {
                string triplet = GetFibTripletFromChar(s[idx]);
                triplets.push_back(triplet);
            }

            vector<int> xyz = GetFiboXYZ(triplets);
            int x = xyz[0], y = xyz[1], z = xyz[2];
            HankelMatrix[i][j] = (x + y == z) ? 1 : 0;

            // cout << seq[i] << " " << seq[j] << "\n";
            // cout << xyz[0] << " " << xyz[1] << " " << xyz[2] <<"\n";
        }
    }
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        cerr << "Provide a size for the matrix.\n";
        return -1;
    }

    int matrixSize = atoi(argv[1]);
    CreateHankelMatrix(FIBO_ALPHABET, MX_DEPTH, matrixSize);

    for (int i = 0; i < matrixSize; i++)
    {
        // cout << Sequence[i] << "\t";
        for (int j = 0; j < matrixSize; j++)
        {
            cout << HankelMatrix[i][j];
        }

        cout << "\n";
    }

    return 0;
}