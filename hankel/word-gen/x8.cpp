#include <bits/stdc++.h>
#define ord(x) ((int)(x)-48)
using namespace std;

const int MAXN = 1e6;

string s1 = "0001";
string s2 = "00010";
string st;

int main()
{
    int n = 12;
    while (n--)
    {
        st = s2 + s2 + s1;
        s1 = s2;
        s2 = st;
    }

    n = s2.length();
    s1 = "";
    int i0 = 0;
    int i1 = 0;
    for (int i = 0; i < n; i++)
    {
        if (s2[i] == '0')
        {
            if (i0 == 0)
            {
                s1 += '0';
            }
            else
            {
                s1 += '1';
            }

            i0 = i0^1;
        }
        else
        {
            if (i1 % 4 == 0)
            {
                s1 += '2';
            }
            else if ((i1 + 5) % 6 == 0)
            {
                s1 += '3';
            }
            else if ((i1 + 6) % 8 == 0)
            {
                s1 += '4';
            }
            else if ((i1 + 3) % 6 == 0)
            {
                s1 += '5';
            }
            else if ((i1 + 1) % 6 == 0)
            {
                s1 += '6';
            }
            else if ((i1 + 2) % 8 == 0)
            {
                s1 += '7';
            }
            else
            {
                assert(false);
            }

            i1 = (i1 + 1) % 24;
        }
    }

    cout << s1 << "\n";

    return 0;
}
