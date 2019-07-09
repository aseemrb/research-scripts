#include <bits/stdc++.h>
#define chr(x) ((char)(x + 48))
#define ord(x) ((int)(x) - 48)
using namespace std;
typedef long long ll;

// Constants.
const int MAXN = 1e5;
const int ALPHABET_SIZE = 2;

string s = "0";
int idx = 0;

void GenZero(int n)
{
    s = "";
    for (int i = 0; i < n; i++)
    {
        s += '0';
    }
}

void NextString()
{
    int n = s.length();

    while (ord(s[idx]) == ALPHABET_SIZE - 1)
    {
        idx--;
    }

    if (idx < 0)
    {
        GenZero(n+1);
        idx = n;
    }
    else
    {
        s[idx]++;
        for (int i = idx + 1; i < n; i++)
        {
            s[i] = '0';
        }

        idx = n-1;
    }
}

int main()
{
    for (int i = 0; i < MAXN; i++)
    {
        cout << s << "\n";
        NextString();
    }
    return 0;
}
