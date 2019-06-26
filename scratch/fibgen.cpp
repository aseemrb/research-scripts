#include <bits/stdc++.h>
using namespace std;

string s1 = "0";
string s2 = "01";
string s;
int main()
{
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        s = s2 + s1;
        s1 = s2;
        s2 = s;
    }

    cout << s << "\n";
    return 0;
}
