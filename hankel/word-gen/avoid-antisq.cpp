#include <bits/stdc++.h>
#define ord(x) ((int)(x)-48)
#define chr(x) ((char)(x + 48))
using namespace std;

const int MAXN = 20;

string phi[2] = {"001", "01"};
string tau[2] = {"0001", "01"};
// string f[10] = {"01", "2", "34", "56", "7", "28", "0", "96", "5", "28"};
// string g[10] = {"0", "0", "0", "1", "0", "1", "0", "0", "1", "0"};

string apply(string* m, string s)
{
    string r = "";
    int n = s.length();
    for (int i = 0; i < n; i++)
    {
        r += m[ord(s[i])];
    }

    return r;
}

int main()
{
    string s = "0";
    for (int i = 1; i < MAXN; i++)
    {
        s = apply(phi, s);
    }
    cout << apply(tau, s) << "\n";

    // string s = "2";
    // cout << "0: " << apply(g, s) << "\n";
    // for (int i = 1; i < 10; i++)
    // {
    //     s = apply(f, s);
    //     cout << i << ": " << apply(g, s) << "\n";
    // }

    return 0;
}
