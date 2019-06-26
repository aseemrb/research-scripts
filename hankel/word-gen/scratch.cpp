#include <bits/stdc++.h>
#define chr(x) ((char)(x + 48))
#define ord(x) ((int)(x) - 48)
using namespace std;

const int MAXN = 1e6;

string s1 = "0001";
string s2 = "00010";
string st;

int main()
{
    char c;
    cin >> c;
    int n = 12;
    while (n--)
    {
        st = s2 + s2 + s1;
        s1 = s2;
        s2 = st;
    }

    n = st.length();
    s1.clear();
    s2.clear();
    int i0 = 0;
    int i1 = 0;
    for (int i = 0; i < n; i++)
    {
        if (st[i] == '0')
        {
            i0 = (i0 + 1) % 24;
        }
        else
        {
            i1 = (i1 ^ 1);
        }

        s1 += chr(i0);
        s2 += chr(i1);
    }

    if (c == '0')
        cout << s1 << "\n";
    else
        cout << s2 << "\n";

    return 0;
}
