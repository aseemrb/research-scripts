#include <bits/stdc++.h>
using namespace std;

#define ord(x) (int)(x - '0')
typedef long long ll;

// Alphabet size.
const int K = 2;
const int MAXN = 10000005;
int len;
string S;

struct Palindrome
{
    int envelope[K];
    int len;
    int lspIndex;
};


// Palindrome 1 - The imaginary one with length -1.
// Palindrome 2 - The empty string.
Palindrome arr[MAXN];

// Total number of Palindromes (distinct palindromes).
// Also serves as the index of newest Palindrome.
int numPalindromes;

// LSP Palindrome up to processed string.
// Initial value = 2 (the one with empty string).
int curLSPIndex;

bool ProcessNextLetter(int pos)
{
    int candidateX = curLSPIndex;
    int lenOfX;
    int nextChar = ord(S[pos]);

    // Go through suffix links to find the candidateX.
    // It is guaranteed that we will find one.
    while (true)
    {
        lenOfX = arr[candidateX].len;
        if (pos - 1 - lenOfX >= 0 && S[pos - 1 - lenOfX] == S[pos])
        {
            // Break if this is the right X.
            break;
        }

        // If this was not the right X, go to its LSP.
        candidateX = arr[candidateX].lspIndex;
    }

    // If an envelope of nextChar takes candidateX to some other Palindrome,
    // then that other palindrome's index becomes the new index for our current LSP.
    if (arr[candidateX].envelope[nextChar] != 0)
    {
        curLSPIndex = arr[candidateX].envelope[nextChar];
        // False denotes that no new Palindrome was created.
        return false;
    }

    // Else, we have a new Palindrome.
    numPalindromes++;
    curLSPIndex = numPalindromes;
    arr[numPalindromes].len = arr[candidateX].len + 2;

    // Set the envelope to go from candidateX to this new Palindrome.
    arr[candidateX].envelope[nextChar] = numPalindromes;

    // Set the lspIndex of this new Palindrome.
    if (arr[numPalindromes].len == 1)
    {
        arr[numPalindromes].lspIndex = 2;
        return true;
    }

    // Find the candidateY.
    // Just reusing candidateX variable here. Don't get confused.
    while (true)
    {
        candidateX = arr[candidateX].lspIndex;
        lenOfX = arr[candidateX].len;

        // Set the suffix link of new Palindrome to the first candidateY found.
        if (pos - 1 - lenOfX >= 0 && S[pos - 1 - lenOfX] == S[pos])
        {
            arr[numPalindromes].lspIndex = arr[candidateX].envelope[nextChar];
            break;
        }
    }

    return true;
}

void Initialize()
{
    numPalindromes = 2; curLSPIndex = 2;
    arr[1].len = -1; arr[1].lspIndex = 1;
    arr[2].len = 0; arr[2].lspIndex = 1;
}

int main()
{
    // assert(freopen("palin.in", "r", stdin));
    // assert(freopen("palin.out", "w", stdout));

    cin >> S;
    len = S.length();
    int ans = 0;

    Initialize();

    for (int i = 0; i < len; i++)
    {
        ProcessNextLetter(i);
    }

    cout << numPalindromes - 2 << endl;

    return 0;
}
