#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Constants.
const int MAXN = 1e5;
const int WordLength = 20;

// Global values.
ll Pells[WordLength];

void Init()
{
    Pells[0] = 1;
    Pells[1] = 2;
    for(int i = 2; i < WordLength; i++)
    {
        Pells[i] = 2 * Pells[i - 1] + Pells[i - 2];
    }
}

string GetPellRep(ll n)
{
    if (n == 0) return "0";

    bool leading = 1;
    string s = "";
    for (int i = WordLength-1; i >= 0; i--)
    {
        if((Pells[i]<<1) <= n)
        {
            s += '2';
            n -= (Pells[i]<<1);
            leading = 0;
        }
        else if(Pells[i] <= n)
        {
            s += '1';
            n -= Pells[i];
            leading = 0;
        }
        else
        {
            if(!leading) s += '0';
        }
    }

    return s;
}

int main()
{
    Init();

    // cout << GetPellRep(Pells[WordLength-1]) << "\n";
    // return 0;

    for(int i = 0; i <= 1e7; i++)
    {
        cout << GetPellRep(i) << "\n";
    }

    return 0;
}
