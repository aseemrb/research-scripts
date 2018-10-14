#include <bits/stdc++.h>
#define chr(x) ((char)(x + 48))
#define ord(x) ((int)(x) - 48)
typedef long long ll;
using namespace std;

// X, Y, Z to be fed to the adder to check if X + Y = Z.
struct ProblemInstance
{
    ll x;
    ll y;
    ll z;
};

// Get the successor of s (representation in given base).
string GetSuccessor(string s, int base)
{
    int l = s.length();
    int c = 1;
    for (int i = l-1; i >= 0; i--)
    {
        if (ord(s[i]) + c == base)
        {
            s[i] = chr(0);
        }
        else
        {
            s[i] = chr(ord(s[i]) + 1);
            return s;
        }
    }

    s.insert(0, 1, chr(1));
    return s;
}

// Get the string representation of n in given base.
// Number n is provided in base 10.
string GetStringInBase(int n, int base)
{
    string s = "";
    s += chr(0);
    while (n--)
    {
        s = GetSuccessor(s, base);
    }

    return s;
}

// Get the triplet string for n in base system.
// Examples:
// For states of fibonacci adder: base is 2, alphabet size is 8.
// For states of super_fibonacci adder: base is 3, alphabet size is 27.
// Input expected is any number from 0 to alphabet size for given base.
// The returned triplet will serve as positional bits of x, y, z in the adder
// where we are going to verify if x + y = z.
string GetTriplet(int n, int base)
{
    string s = "";
    while (n > 0)
    {
        s.insert(0, 1, chr(n % base));
        n /= base;
    }

    // Make sure the final string is a triplet. Pad if required.
    while (s.length() < 3)
    {
        s.insert(0, 1, chr(0));
    }

    return s;
}
