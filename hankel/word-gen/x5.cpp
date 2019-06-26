#include "../helpers.h"
using namespace std;

// Length of generated sequence is 5741 for 9 iterations.
const int iterations = 9;
const int MAXN = 6000;
const int WordLength = 30;
const int MaxStates = 500;

ll pnums[WordLength];
int X5trans[MaxStates][3];
int InitState = 1;
int CurDeadState = 400;

string pell, pellm1, pellm2;
int SaveState[MAXN];

void init()
{
    pellm1 = "01", pellm2 = "0";
    pnums[0] = 1;
    pnums[1] = 2;
    for(int i = 2; i < WordLength; i++)
    {
        pnums[i] = 2 * pnums[i - 1] + pnums[i - 2];
    }

    for (int i = 0; i < MaxStates; i++)
    {
        X5trans[i][0] = -1;
        X5trans[i][1] = -1;
        X5trans[i][2] = -1;
    }
}

string GetPellBaseStr(int n)
{
    if (n == 0) return "0";
    bool leading = true;
    string ans = "";
    for (int i = WordLength - 1; i >= 0; i--)
    {
        if (2*pnums[i] <= n)
        {
            ans += "2";
            n -= 2*pnums[i];
            leading = false;
        }
        else if (pnums[i] <= n)
        {
            ans += "1";
            n -= pnums[i];
            leading = false;
        }
        else if (!leading)
        {
            ans += "0";
        }
    }

    return ans;
}

int main()
{
    init();
    for (int i = 0; i < iterations; i++)
    {
        pell = pellm1 + pellm1 + pellm2;
        pellm2 = pellm1;
        pellm1 = pell;
    }

    int n = pell.length();
    int e, m1 = 0, m0 = 0;
    for (int i = 0; i < n; i++)
    {
        if (pell[i] == '0')
        {
            e = 0;
            m0 = (m0 + 1) % 4;
        }
        else
        {
            e = 1;
            m1 = m1 ^ 1;
        }

        SaveState[i] = 16*e + 4*m1 + m0;
    }

    for (int i = 0; i < n; i++)
    {
        int state = InitState;
        string pellstr = GetPellBaseStr(i);
        int k = pellstr.length();
        // cout << pellstr << "\n";

        for (int j = 0; j < k; j++)
        {
            int jj = ord(pellstr[j]);
            if (X5trans[state][jj] != -1) state = X5trans[state][jj];
            else if (jj == 2)
            {
                X5trans[state][jj] = CurDeadState++;
                state = X5trans[state][jj];
                continue;
            }
            else
            {
                X5trans[state][jj] = SaveState[i];
            }
        }
    }

    for (int i = 0; i < MaxStates; i++)
    {
        int c;
        e = i/16;
        m1 = (i % 16) / 4;
        m0 = (i % 4);

        if (e == 1)
        {
            if (m1 == 0) c = 4;
            if (m1 == 1) c = 3;
        }
        else if (e == 0)
        {
            if (m0 == 0) c = 2;
            if (m0 == 1) c = 0;
            if (m0 == 2) c = 1;
            if (m0 == 3) c = 0;
        }

        if (X5trans[i][0] == -1 && X5trans[i][1] == -1 && X5trans[i][2] == -1)
            continue;
        cout << "State: " << i << " " << c << " (" << e << m1 << m0 << ")\n";

        for (int j = 0; j < 3; j++)
        {
            if (X5trans[i][j] != -1)
                cout << j << " -> " << X5trans[i][j] << "\n";
        }
    }
}
