#include "../helpers.h"
using namespace std;

// Length of generated sequence is 5741 for 9 iterations.
const int iterations = 9;
const int MAXN = 6000;
const int WordLength = 20;
const int MaxStates = 500;

ll pnums[WordLength];
int X5trans[MaxStates][4];
int InitState = 1;
int CurDeadState = 400;

string pell, pellm1, pellm2;
int SaveState[MAXN];

void init()
{
    pellm1 = "00010", pellm2 = "0001";
    pnums[0] = 1;
    pnums[1] = 4;
    pnums[2] = 5;
    for(int i = 3; i < WordLength; i++)
    {
        pnums[i] = 2 * pnums[i - 1] + pnums[i - 2];
    }

    for (int i = 0; i < MaxStates; i++)
    {
        X5trans[i][0] = -1;
        X5trans[i][1] = -1;
        X5trans[i][2] = -1;
        X5trans[i][3] = -1;
    }
}

string GetOstRep(int n)
{
    assert(n < pnums[WordLength - 1]);
    if (n == 0) return "0";

    bool leading = 1;
    string s = "";
    for (int i = WordLength-2; i >= 0; i--)
    {
        int coefficient = n / pnums[i];
        if (coefficient == 0 && (!leading))
        {
            s += '0';
        }
        else if (coefficient > 0)
        {
            s += chr(coefficient);
            n -= coefficient*pnums[i];
            leading = 0;
        }
    }

    return s;
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

    int n = min((int)pell.length(), MAXN);
    int e, m1 = 0, m0 = 0;
    for (int i = 0; i < n; i++)
    {
        if (pell[i] == '0')
        {
            e = 0;
            m0 = m0 ^ 1;
        }
        else
        {
            e = 1;
            m1 = (m1 + 1) % 24;
        }

        SaveState[i] = 25*e + 5*m1 + m0;
    }

    for (int i = 0; i < n; i++)
    {
        int state = InitState;
        string pellstr = GetOstRep(i);
        int k = pellstr.length();
        // cout << pellstr << "\n";

        for (int j = 0; j < k; j++)
        {
            int jj = ord(pellstr[j]);
            if (X5trans[state][jj] != -1) state = X5trans[state][jj];
            // else if (jj == 2)
            // {
            //     X5trans[state][jj] = CurDeadState++;
            //     state = X5trans[state][jj];
            //     continue;
            // }
            else
            {
                X5trans[state][jj] = SaveState[i];
            }
        }
    }

    for (int i = 0; i < MaxStates; i++)
    {
        int c;
        e = i/25;
        m1 = (i % 25) / 5;
        m0 = (i % 5);

        if (e == 1)
        {
            if (m1 == 1) c = 2;
            else if (m1 == 2) c = 3;
            else if (m1 == 3) c = 4;
            else if (m1 == 4) c = 5;
            else if (m1 == 5) c = 2;
            else if (m1 == 6) c = 6;
            else if (m1 == 7) c = 7;
            else if (m1 == 8) c = 3;
            else if (m1 == 9) c = 2;
            else if (m1 == 10) c = 5;
            else if (m1 == 11) c = 4;
            else if (m1 == 12) c = 6;
            else if (m1 == 13) c = 2;
            else if (m1 == 14) c = 3;
            else if (m1 == 15) c = 7;
            else if (m1 == 16) c = 5;
            else if (m1 == 17) c = 2;
            else if (m1 == 18) c = 6;
            else if (m1 == 19) c = 4;
            else if (m1 == 20) c = 3;
            else if (m1 == 21) c = 2;
            else if (m1 == 22) c = 5;
            else if (m1 == 23) c = 7;
            else if (m1 == 0) c = 6;
        }
        else if (e == 0)
        {
            if (m0 == 1) c = 0;
            else if (m0 == 0) c = 1;
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
