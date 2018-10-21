#include <bits/stdc++.h>
using namespace std;
const int MAX = 1e5;
int state[MAX];
int main()
{
    fstream fin;
    fstream fout;
    int z, x;
    fin.open("total", fstream::in);
    for (int i = 0; i < 16; i++)
    {
        fin >> z;
        while (1)
        {
            fin >> x;
            if (x == -1) break;
            state[x] = z;
        }
    }
    fin.close();

    while (1)
    {
        cin >> x;
        for (int i = x; i < x + 27; i++)
        {
            if (state[i] == -1) cout << "D ";
            else cout << state[i] << " ";
        }

        cout << "\n";
    }

    return 0;
}
