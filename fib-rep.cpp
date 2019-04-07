#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Constants.
const int MAXN = 1e5;
const int WordLength = 50;

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

string GetFibRep(ll n)
{
    if (n == 0) return "0";

    bool leading = 1;
    string s = "";
    for (int i = WordLength-1; i >= 0; i--)
    {
        if(Fibs[i] <= n)
        {
            s += '1';
            n -= Fibs[i];
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

    // cout << GetFibRep(Fibs[WordLength-1]) << "\n";
    // return 0;

    for(int i = 0; i <= 1e5; i++)
    {
        cout << GetFibRep(i) << "\n";
    }

    return 0;
}
