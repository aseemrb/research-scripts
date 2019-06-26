#include <bits/stdc++.h>
#define ord(x) ((int)(x)-48)
using namespace std;

int T[6][2] =
{
    {0, 1},
    {2, 3},
    {3, 0},
    {4, 2},
    {1, 5},
    {1, -1}
};

int main()
{
    int n = 1e5;
    string s;
    while(n--)
    {
        cin >> s;

        int state = 0;
        for (int i = 0; i < s.length(); i++)
        {
            state = T[state][ord(s[i])];
        }

        if (state == 2 || state == 5)
            cout << 0;
        else
            cout << 1;
    }

    cout << "\n";
    return 0;
}
