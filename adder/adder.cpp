#include <bits/stdc++.h>
#define ord(x) ((int)x - 48)
#define chr(x) ((char)(x + 48))
typedef long long ll;
using namespace std;

string InputLine;
vector < int > Alpha;
int RepeatIdx;

// Helper functions.
template<typename T>
void PrintVector(const T& v, ofstream& fs)
{
    copy(v.cbegin(), v.cend(), ostream_iterator<typename T::value_type>(fs, " "));
}

int main()
{
    ReadInputs();
}

void ReadInputs()
{
    // Read the continued fraction of alpha.
    cout << "Reading continued fraction of alpha.\n";
    cout << "CF: ";
    ifstream inp("input.in");
    getline(inp, InputLine);

    // Parse the read line to populate Alpha.
    stringstream parse(InputLine);
    int d;
    while (parse >> d)
    {
        Alpha.push_back(d);
    }

    while (1)
    {
        inp >> d;
        if (d == -1)
        {
            // Input for Alpha ends.
            break;
        }

        Alpha.push_back(d);
        cout << d << " ";
    }

    inp >> RepeatIdx;
    cout << "\n";
    cout << "RI: " << RepeatIdx << "\n\n";

    // At least two elements required in Alpha.
    int sz_d = Alpha.size();
    assert(sz_d >= 2);

    // Uncomment this line to only consider alpha < 0.5.
    // assert(Alpha[1] >= 2);

    // Read the first input.

    inp.close();
}
