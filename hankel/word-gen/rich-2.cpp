#include <bits/stdc++.h>
#define ord(x) ((int)(x)-48)
using namespace std;

const int MAXN = 1e6;

string B;
string phi[3] = {"01", "02", "022"};
string tau[3] = {"0", "01", "011"};

int main()
{
    queue<char> s;
    int c = 1;
    s.push('1');
    cout << 0;
    for(int i = 0; i < MAXN; i++)
    {
        char next = s.front();
        if((c++) == MAXN)
        {
            c = 0; cout << "\n";
        }
        cout << tau[ord(next)];
        string img = phi[ord(next)];
        for (int j = 0; j < img.length(); j++)
            s.push(img[j]);
        s.pop();
    }

    while (!s.empty())
    {
        cout << tau[ord(s.front())];
        s.pop();
    }

    return 0;
}
