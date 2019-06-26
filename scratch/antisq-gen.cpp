#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

bool print;

int M = 1000;
int N, INDEXC, INDEXS;
// bitset<M> B;
double CE = 3.61803398875; // 2 + phi
string S, HP, GHP;
string FIBWORD;
// set<string> HPSet;

const regex H11("0001");
const regex H12("01");
const regex H3("2");
const regex H4("3");
const regex H21("1110");
const regex H22("10");
const regex G1("001");
const regex G2("01");
const regex SIDES("(0|1)");

int LCS[10000][1000];

bool IsValid()
{
    if (S[0] == '1')
    {
        INDEXC = N;
    }

    int zeros = count(S.begin(), S.end(), '0');

    // Check if first symbol is 0 and #zeros >= #ones.
    return (S[0] == '0') && ((zeros<<1) >= N);
}

bool WithinCE()
{
    double tce = 0;
    for (int i = 0; i < N; i++)
    {
        for (int p = 1; p < N; p++)
        {
            int j = i;
            while (j + p < N)
            {
                tce = (double)(j+p-i)/(double)(p);
                if (tce >= CE)
                {
                    INDEXC = N-j-p;
                    // cout << "--- CE_Culprit: " << S << " " << INDEXC << "\n";
                    return false;
                }

                if (S[j] != S[j+p])
                {
                    break;
                }

                j++;
            }

            tce = (double)(j+p-i)/(double)(p);
            if (tce >= CE)
            {
                INDEXC = N-j-p;
                // cout << "--- CE_Culprit: " << S << " " << INDEXC << "\n";
                return false;
            }
        }
    }

    return true;
}

bool NoAntiSq()
{
    for (int i = 0; i < N-3; i++)
    {
        for (int j = 2; i + 2*j <= N; j++)
        {
            bool as = true;
            int k;
            for (k = 0; k < j; k++)
            {
                if (S[i+k] == S[i+j+k])
                {
                    as = false;
                    break;
                }
            }

            if (as)
            {
                INDEXS = N-(i+j+k);
                // cout << "--- AS_Culprit: " << S.substr(i, 2*j) << " " << INDEXS << "\n";
                return false;
            }
        }
    }

    return true;
}

// Apply H-1 on S to get HP, the preimage of S under morphism H.
void ApplyHInv()
{
    smatch m;
    // if(regex_search (S,m,H11))
    // {
        HP = regex_replace(S, H11, "2");
        HP = regex_replace(HP, H12, "3");
        HP = regex_replace(HP, SIDES, "-");
        HP = regex_replace(HP, H3, "0");
        HP = regex_replace(HP, H4, "1");
    // }
    // else
    // {
    //     HP = regex_replace(S, H21, "2");
    //     HP = regex_replace(HP, H22, "3");
    //     HP = regex_replace(HP, SIDES, "-");
    //     HP = regex_replace(HP, H3, "0");
    //     HP = regex_replace(HP, H4, "1");
    // }
}

// Apply H-1 on HP to get GHP, the preimage of HP under morphism G.
void ApplyGInv()
{
    GHP = regex_replace(HP, G1, "2");
    GHP = regex_replace(GHP, G2, "3");
    GHP = regex_replace(GHP, SIDES, "*");
    GHP = regex_replace(GHP, H3, "0");
    GHP = regex_replace(GHP, H4, "1");
}

int ComputeLCS()
{
    int result = 0;
    int n = HP.length();
    for (int i = 0; i <= n; i++)
    {
        for (int j = 0; j <= M; j++)
        {

            // The first row and first column
            // entries have no logical meaning,
            // they are used only for simplicity
            // of program
            if (i == 0 || j == 0 || (FIBWORD[j-1] != HP[i-1]))
            {
                LCS[i][j] = 0;
            }
            else
            {
                LCS[i][j] = LCS[i-1][j-1] + 1;
                result = max(result, LCS[i][j]);
            }
        }
    }
    return result;
}

int main()
{
    ifstream fibword("fib.word");
    getline(fibword, FIBWORD);
    fibword.close();

    while (1)
    {
        // cout << "Input N: ";
        cin >> N;
        // cin >> print;
        if (N == 0) break;

        S = "";
        for (int i = 0; i < N; i++)
        {
            S += "0";
        }

        // B.reset();
        // HPSet.clear();
        int c = 0;

        while(1)
        {
            // S = B.to_string().substr(M-N);
            INDEXC = INDEXS = 0;
            if (
                IsValid() &&
                WithinCE() &&
                NoAntiSq())
            {
                ApplyHInv(); // Populates HP.
                // ApplyGInv(); // Populates GHP.
                // if (print)
                // {
                    cout << S << " " << HP << " " << HP.length() - ComputeLCS() << "\n";
                //     cout << S << "\n";
                // }
                c++;
            }

            /*
            else
            {
                if (!WithinCE())
                {
                    cout << "FAIL_CE: " << S << "\n";
                }
                else if (!NoAntiSq())
                {
                    cout << "FAIL_AS: " << S << "\n";
                }
            }*/

            int INDEX = N-1-max(INDEXC, INDEXS);
            while (INDEX >= 0 && S[INDEX] == '1')
            {
                INDEX--;
            }

            // if (B.to_ullong() >= (1LL << N))
            if (INDEX <= 0)
            {
                // cout << "Total: ";
                cout << c << "\n";
                break;
            }

            S[INDEX] = '1';
            for (int i = INDEX+1; i < N; i++)
            {
                S[i] = '0';
            }
        }

    }
    return 0;
}
