#include <bits/stdc++.h>
#define chr(x) ((char)(x + 48))
#define ord(x) ((int)(x) - 48)
using namespace std;
typedef long long ll;

// Constants.
const int MAXN = 1e5;
const int MaxPlace = 50;

// Example:
// If CF of alpha = [0, 1, 3, 1, 2, 2, ...] then D_alpha = {0, 1, 3, 1, 2} and RepeatIdx = 4.
vector < int > D_alpha;
int RepeatIdx;
ll PlaceValue[MaxPlace];


void Init()
{
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
    }

    alpha >> RepeatIdx;
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

string GetOstRep(ll n)
{
    // We want to only deal with integers < max PlaceValue.
    assert(n < PlaceValue[MaxPlace - 1]);
    if (n == 0) return "0";

    bool leading = 1;
    string s = "";
    for (int i = MaxPlace-2; i >= 0; i--)
    {
        int coefficient = n / PlaceValue[i];
        if (coefficient == 0 && (!leading))
        {
            s += '0';
        }
        else if (coefficient > 0)
        {
            s += chr(coefficient);
            n -= coefficient*PlaceValue[i];
            leading = 0;
        }
    }

    return s;
}

int main()
{
    Init();
    ofstream ostrep;
    ostrep.open("ost-rep.txt", ofstream::trunc);
    for(int i = 0; i <= 1e9; i++)
    {
        ostrep << GetOstRep(i) << "\n";
    }

    ostrep.close();
    return 0;
}
