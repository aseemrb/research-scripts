#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

static void TrimLeading0s(string& s)
{
    s.erase(0, min(s.find_first_not_of('0'), s.size()-1));
}

// List of fibonacci numbers in LL range.
vector<ll> CreateFibos(int n)
{
    vector<ll> fibos;
    fibos.push_back(1);
    fibos.push_back(2);
    for(int i = 0; i < n; i++)
    {
        fibos.push_back(fibos[i] + fibos[i+1]);
    }

    return fibos;
}

// More than 80 might exceed the long long limit.
vector<ll> fibos = CreateFibos(80);
int k = fibos.size();

string GetFibonacciRep(ll n)
{
    if (n < 0 || n > fibos[k - 1])
        return "Error: Number not in range.\n";

    string fiborep = "";
    bool prev1 = false;
    for (int i = k-1; i >= 0; i--)
    {
        if (fibos[i] <= n && (!prev1))
        {
            fiborep += "1";
            n -= fibos[i];
            prev1 = true;
        }
        else
        {
            fiborep += "0";
            prev1 = false;
        }
    }

    TrimLeading0s(fiborep);
    return fiborep;
}

// Get the sequence of triplets to feed the automaton for
// given x, y, z. The automaton is to check whether x + y = z.
vector<string> GetFibTriplets(ll x, ll y, ll z)
{
    string
        sx = GetFibonacciRep(x),
        sy = GetFibonacciRep(y),
        sz = GetFibonacciRep(z);

    int len = max(max(sx.size(), sy.size()), sz.size());

    while(sx.size() < len) sx = "0" + sx;
    while(sy.size() < len) sy = "0" + sy;
    while(sz.size() < len) sz = "0" + sz;

    vector<string> triplets(len);

    for (int i = 0; i < len; i++)
    {
        triplets[i] = "";
        triplets[i] += sx[i];
        triplets[i] += sy[i];
        triplets[i] += sz[i];
    }

    return triplets;
}

// This is the inverse of GetFibTriplets. But here the triplets
// parameter is LSD first.
vector<int> GetFiboXYZ(vector<string> triplets)
{
    vector<int> result = {0, 0, 0};
    for (int i = 0; i < triplets.size(); i++)
    {
        result[0] += (triplets[i][0] - 48) * fibos[i];
        result[1] += (triplets[i][1] - 48) * fibos[i];
        result[2] += (triplets[i][2] - 48) * fibos[i];
    }

    return result;
}

char GetFibCharFromTriplet(string triplet)
{
    return
        (char)
        (4 * (triplet[0]-48) + 2 * (triplet[1] - 48) + (triplet[2] - 48) + 48);
}

string GetFibTripletFromChar(char chr)
{
    int c = (int) chr - 48;
    string triplet = "";
    triplet += (char)(((c >> 2) % 2) + 48);
    triplet += (char)(((c >> 1) % 2) + 48);
    triplet += (char)((c % 2) + 48);
    return triplet;
}
