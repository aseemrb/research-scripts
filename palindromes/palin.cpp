#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

#define chr(x) (char)(x+48)
#define ord(x) ((int)(x)-48)

char dum = 0;
const int MAXK = 10;

// Critical exponent threshold.
double CE = 2;

// Default alphabet size and the alphabet (overwritten with input).
int K = 2;
string ALPH = "";

// String related.
string S = "";
string MAXS = "";
int maxlen = 1;
int lastIdx = -1;

const int MAXN = 10000005;
int len;

struct Palindrome
{
    int envelope[MAXK];
    int renvelope[MAXK];
    int len;
    int lspIndex;
};


// Palindrome 1 - The imaginary one with length -1.
// Palindrome 2 - The empty string.
Palindrome Tree[MAXN];

// Total number of Palindromes (distinct palindromes).
// Also serves as the index of newest Palindrome.
int numPalindromes;

// LSP Palindrome up to processed string.
// Initial value = 2 (the one with empty string).
int curLSPIndex;

// Remove the last character from S.
void RemoveLastChar()
{
    S.erase(S.size() - 1);
}

bool StillRich()
{
    // cout << "Checking richness:\n";
    // cin >> dum;
    // if (lastIdx > 100) return false;

    // cout << "\n-- IDX: ";
    // for (int i = 1; i <= numPalindromes; i++)
    // {
    //     cout << i << "\t";
    // }
    // cout << "\n-- LEN: ";
    // for (int i = 1; i <= numPalindromes; i++)
    // {
    //     cout << Tree[i].len << "\t";
    // }
    // cout << "\n-- LSP: ";
    // for (int i = 1; i <= numPalindromes; i++)
    // {
    //     cout << Tree[i].lspIndex << "\t";
    // }
    // cout << "\n CURRENT LSP INDEX: " << curLSPIndex << "\n\n";

    int pos = lastIdx;
    int candidateX = curLSPIndex;
    int lenOfX;
    int nextChar = ord(S[pos]);

    // Go through suffix links to find the candidateX.
    // It is guaranteed that we will find one.
    while (true)
    {
        lenOfX = Tree[candidateX].len;
        // char blah;
        // cin >> blah;
        // cout << S << " " << curLSPIndex << " " << lenOfX << " " << candidateX << "\n";
        // cout << Tree[1].len << " " << Tree[2].len << " " << Tree[3].len << " " << Tree[4].len << " " << Tree[5].len << "\n";
        if (pos - 1 - lenOfX >= 0 && S[pos - 1 - lenOfX] == S[pos])
        {
            // Break if this is the right X.
            break;
        }

        // If this was not the right X, go to its LSP.
        candidateX = Tree[candidateX].lspIndex;
    }

    // If an envelope of nextChar takes candidateX to some other Palindrome,
    // then that other palindrome's index becomes the new index for our current LSP.
    if (Tree[candidateX].envelope[nextChar] != 0)
    {
        // curLSPIndex = Tree[candidateX].envelope[nextChar];
        // False denotes that no new Palindrome was created.
        return false;
    }

    // Else, we have a new Palindrome.
    numPalindromes++;
    curLSPIndex = numPalindromes;
    Tree[numPalindromes].len = Tree[candidateX].len + 2;

    // Set the envelope to go from candidateX to this new Palindrome.
    Tree[candidateX].envelope[nextChar] = numPalindromes;
    Tree[numPalindromes].renvelope[nextChar] = candidateX;

    // Set the lspIndex of this new Palindrome.
    if (Tree[numPalindromes].len == 1)
    {
        Tree[numPalindromes].lspIndex = 2;
        // cout << "\n-- IDX: ";
        // for (int i = 1; i <= numPalindromes; i++)
        // {
        //     cout << i << "\t";
        // }
        // cout << "\n-- LEN: ";
        // for (int i = 1; i <= numPalindromes; i++)
        // {
        //     cout << Tree[i].len << "\t";
        // }
        // cout << "\n-- LSP: ";
        // for (int i = 1; i <= numPalindromes; i++)
        // {
        //     cout << Tree[i].lspIndex << "\t";
        // }
        // cout << "\n CURRENT LSP INDEX: " << curLSPIndex << "\n\n";

        return true;
    }

    // Find the candidateY.
    // Just reusing candidateX variable here. Don't get confused.
    while (true)
    {
        candidateX = Tree[candidateX].lspIndex;
        lenOfX = Tree[candidateX].len;

        // Set the suffix link of new Palindrome to the first candidateY found.
        if (pos - 1 - lenOfX >= 0 && S[pos - 1 - lenOfX] == S[pos])
        {
            Tree[numPalindromes].lspIndex = Tree[candidateX].envelope[nextChar];
            break;
        }
    }
    // cout << "\n-- IDX: ";
    // for (int i = 1; i <= numPalindromes; i++)
    // {
    //     cout << i << "\t";
    // }
    // cout << "\n-- LEN: ";
    // for (int i = 1; i <= numPalindromes; i++)
    // {
    //     cout << Tree[i].len << "\t";
    // }
    // cout << "\n-- LSP: ";
    // for (int i = 1; i <= numPalindromes; i++)
    // {
    //     cout << Tree[i].lspIndex << "\t";
    // }
    // cout << "\n CURRENT LSP INDEX: " << curLSPIndex << "\n\n";

    return true;
}

void RewindPalTree(int env)
{
    // cout << "Rewinding:\n";
//     cin >> dum;
    Tree[curLSPIndex].len = 0;
    Tree[curLSPIndex].lspIndex = 0;
    Tree[Tree[curLSPIndex].renvelope[env]].envelope[env] = 0;

    for (int i = 0; i < K; i++)
        Tree[curLSPIndex].renvelope[i] = 0;
    curLSPIndex--;
    numPalindromes--;
}

bool WithinCE()
{
    double tce = 0;
    int n = S.length();
    for (int i = 0; i < n; i++)
    {
        for (int p = 1; p < n; p++)
        {
            int j = i;
            while (j + p < n)
            {
                if (S[j] != S[j+p])
                {
                    break;
                }

                j++;
            }

            tce = max(tce, (double)(j+p-i)/(double)(p));
        }
    }

    // cout << S << " " << tce << "\n";
    return tce < CE;
}

// Check if we should consider this word.
bool Validate()
{
    // cout << "Validating " << S << "\n";
    // cin >> dum;
    int ch = ord(S[0]);
    for (int i = 1; i <= lastIdx; i++)
    {
        if (ord(S[i]) > ch)
        {
            if (ord(S[i]) - ch > 1) return false;
            ch = ord(S[i]);
            if (ch == K-1) break;
        }
    }

    return
        WithinCE() &&
        StillRich();
}

void Initialize()
{
    ALPH = "";
    for (int i = 0; i < K; i++)
    {
        ALPH += chr(i);
    }

    numPalindromes = 2; curLSPIndex = 2;
    Tree[1].len = -1; Tree[1].lspIndex = 1;
    Tree[2].len = 0; Tree[2].lspIndex = 1;
}

int main()
{
    // assert(freopen("palin.in", "r", stdin));
    // assert(freopen("palin.out", "w", stdout));

    // cin >> S;
    len = S.length();
    int ans = 0;


    cout << "Input alphabet size (k) and critical exponent (c): ";
    cin >> K >> CE;
    Initialize();

    int i = 0;
    // int cnter = 0;
    while(1)
    {
        // cnter++;
        // cout << cnter << ":\n";
        // if (cnter == 1e5)
        // {
        //     cout << "\n--- CHECKPOINT S: " << S << "\n";
        //     cnter = 0;
        //     // break;
        // }

        S += ALPH[i];
        lastIdx++;

        if(Validate())
        {
            // cout << "Valid: " << S << ", lastIdx: " << lastIdx << ", i: " << i << "\n";
            i = 0;
            if (lastIdx >= maxlen)
            {
                // if (lastIdx >= maxlen)
                // {
                    maxlen = lastIdx + 1;
                    MAXS = S;
                    cout << "New Length: " << lastIdx + 1 << "\r";
                // }
                // cout << "String: " << S << "\n\n";
            }
        }
        else
        {
            // cout << "Invalid: " << S << ", lastIdx: " << lastIdx << ", i: " << i << "\n";

            // Remove the invalid symbol.
            lastIdx--;

            if (lastIdx >= 0) RemoveLastChar();

            // Look at next symbol.
            i++;
            if (i >= K) // Exhausted all possible symbols.
            {
                // Remove last character till something incrementable is found.
                while (lastIdx > 0 && ord(S[lastIdx]) == K - 1)
                {
                    RewindPalTree(ord(S[lastIdx]));
                    RemoveLastChar();
                    lastIdx--;
                }

                if (lastIdx == 0)
                {
                    // Exhausted everything.
                    cout << "\nFinal maximum length: " << maxlen << "\n";
                    cout << "The string: " << MAXS << "\n";
                    break;
                }

                // replace last character with the next symbol.
                i = ord(S[lastIdx]) + 1;
                RewindPalTree(i - 1);
                RemoveLastChar();
                lastIdx--;
            }
        }
    }

    return 0;
}
