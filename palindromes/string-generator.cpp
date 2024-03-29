#include "../helpers.h"
using namespace std;

const int MAX = 1e8;
const int WordLength = 45;
ll Pells[WordLength];

// Define the automaton here.
// States
int states[18] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17 };

// Initial and final states
const int q0 = 0;
int qf[3] = {0, 6, 13};

// Transition table
map<char, int> transition[18] =
// state 0
{{{'0', 0}
,{'1', 1}
,{'2', 17}
,{'3', 17}
,{'4', 0}
,{'5', 2}
,{'6', 17}
,{'7', 17}
,{'8', 3}
,{'9', 17}
,{'a', 0}
,{'b', 2}
,{'c', 17}
,{'d', 17}
,{'e', 3}
,{'f', 17}
,{'g', 17}
,{'h', 17}
,{'i', 17}
,{'j', 17}
,{'k', 3}
,{'l', 17}
,{'m', 17}
,{'n', 17}
,{'o', 17}
,{'p', 17}
,{'q', 17}}
,
// state 1
{{'0', 17}
,{'1', 17}
,{'2', 17}
,{'3', 4}
,{'4', 17}
,{'5', 17}
,{'6', 5}
,{'7', 17}
,{'8', 17}
,{'9', 4}
,{'a', 17}
,{'b', 17}
,{'c', 6}
,{'d', 4}
,{'e', 17}
,{'f', 7}
,{'g', 5}
,{'h', 17}
,{'i', 8}
,{'j', 17}
,{'k', 17}
,{'l', 7}
,{'m', 8}
,{'n', 17}
,{'o', 17}
,{'p', 7}
,{'q', 15}}
,
// state 2
{{'0', 17}
,{'1', 17}
,{'2', 17}
,{'3', 4}
,{'4', 17}
,{'5', 17}
,{'6', 5}
,{'7', 17}
,{'8', 17}
,{'9', 4}
,{'a', 17}
,{'b', 17}
,{'c', 6}
,{'d', 17}
,{'e', 17}
,{'f', 7}
,{'g', 17}
,{'h', 17}
,{'i', 8}
,{'j', 17}
,{'k', 17}
,{'l', 7}
,{'m', 17}
,{'n', 17}
,{'o', 17}
,{'p', 17}
,{'q', 17}}
,
// state 3
{{'0', 0}
,{'1', 17}
,{'2', 17}
,{'3', 17}
,{'4', 17}
,{'5', 17}
,{'6', 17}
,{'7', 17}
,{'8', 17}
,{'9', 17}
,{'a', 17}
,{'b', 17}
,{'c', 17}
,{'d', 17}
,{'e', 17}
,{'f', 17}
,{'g', 17}
,{'h', 17}
,{'i', 17}
,{'j', 17}
,{'k', 17}
,{'l', 17}
,{'m', 17}
,{'n', 17}
,{'o', 17}
,{'p', 17}
,{'q', 17}}
,
// state 4
{{'0', 17}
,{'1', 17}
,{'2', 17}
,{'3', 17}
,{'4', 17}
,{'5', 17}
,{'6', 17}
,{'7', 17}
,{'8', 17}
,{'9', 17}
,{'a', 17}
,{'b', 17}
,{'c', 4}
,{'d', 17}
,{'e', 17}
,{'f', 5}
,{'g', 17}
,{'h', 17}
,{'i', 17}
,{'j', 17}
,{'k', 17}
,{'l', 8}
,{'m', 17}
,{'n', 17}
,{'o', 7}
,{'p', 16}
,{'q', 17}}
,
// state 5
{{'0', 1}
,{'1', 17}
,{'2', 17}
,{'3', 17}
,{'4', 17}
,{'5', 17}
,{'6', 17}
,{'7', 17}
,{'8', 17}
,{'9', 0}
,{'a', 1}
,{'b', 17}
,{'c', 17}
,{'d', 17}
,{'e', 17}
,{'f', 17}
,{'g', 17}
,{'h', 17}
,{'i', 17}
,{'j', 9}
,{'k', 10}
,{'l', 17}
,{'m', 17}
,{'n', 17}
,{'o', 17}
,{'p', 17}
,{'q', 17}}
,
// state 6
{{'0', 1}
,{'1', 17}
,{'2', 17}
,{'3', 0}
,{'4', 1}
,{'5', 17}
,{'6', 17}
,{'7', 11}
,{'8', 12}
,{'9', 0}
,{'a', 1}
,{'b', 17}
,{'c', 17}
,{'d', 0}
,{'e', 2}
,{'f', 17}
,{'g', 17}
,{'h', 3}
,{'i', 17}
,{'j', 9}
,{'k', 10}
,{'l', 17}
,{'m', 17}
,{'n', 3}
,{'o', 17}
,{'p', 17}
,{'q', 17}}
,
// state 7
{{'0', 17}
,{'1', 13}
,{'2', 14}
,{'3', 17}
,{'4', 17}
,{'5', 17}
,{'6', 17}
,{'7', 17}
,{'8', 17}
,{'9', 17}
,{'a', 17}
,{'b', 17}
,{'c', 17}
,{'d', 17}
,{'e', 17}
,{'f', 17}
,{'g', 17}
,{'h', 17}
,{'i', 17}
,{'j', 17}
,{'k', 17}
,{'l', 17}
,{'m', 17}
,{'n', 17}
,{'o', 17}
,{'p', 17}
,{'q', 17}}
,
// state 8
{{'0', 1}
,{'1', 17}
,{'2', 17}
,{'3', 0}
,{'4', 1}
,{'5', 17}
,{'6', 17}
,{'7', 11}
,{'8', 12}
,{'9', 17}
,{'a', 17}
,{'b', 17}
,{'c', 17}
,{'d', 17}
,{'e', 17}
,{'f', 17}
,{'g', 17}
,{'h', 17}
,{'i', 17}
,{'j', 17}
,{'k', 17}
,{'l', 17}
,{'m', 17}
,{'n', 17}
,{'o', 17}
,{'p', 17}
,{'q', 17}}
,
// state 9
{{'0', 0}
,{'1', 1}
,{'2', 17}
,{'3', 17}
,{'4', 0}
,{'5', 2}
,{'6', 17}
,{'7', 17}
,{'8', 3}
,{'9', 17}
,{'a', 17}
,{'b', 17}
,{'c', 17}
,{'d', 17}
,{'e', 17}
,{'f', 17}
,{'g', 17}
,{'h', 17}
,{'i', 17}
,{'j', 17}
,{'k', 17}
,{'l', 17}
,{'m', 17}
,{'n', 17}
,{'o', 17}
,{'p', 17}
,{'q', 17}}
,
// state 10
{{'0', 17}
,{'1', 17}
,{'2', 17}
,{'3', 4}
,{'4', 17}
,{'5', 17}
,{'6', 5}
,{'7', 17}
,{'8', 17}
,{'9', 17}
,{'a', 17}
,{'b', 17}
,{'c', 17}
,{'d', 17}
,{'e', 17}
,{'f', 17}
,{'g', 17}
,{'h', 17}
,{'i', 17}
,{'j', 17}
,{'k', 17}
,{'l', 17}
,{'m', 17}
,{'n', 17}
,{'o', 17}
,{'p', 17}
,{'q', 17}}
,
// state 11
{{'0', 0}
,{'1', 1}
,{'2', 17}
,{'3', 17}
,{'4', 17}
,{'5', 17}
,{'6', 17}
,{'7', 17}
,{'8', 17}
,{'9', 17}
,{'a', 0}
,{'b', 2}
,{'c', 17}
,{'d', 17}
,{'e', 17}
,{'f', 17}
,{'g', 17}
,{'h', 17}
,{'i', 17}
,{'j', 17}
,{'k', 3}
,{'l', 17}
,{'m', 17}
,{'n', 17}
,{'o', 17}
,{'p', 17}
,{'q', 17}}
,
// state 12
{{'0', 17}
,{'1', 17}
,{'2', 17}
,{'3', 17}
,{'4', 17}
,{'5', 17}
,{'6', 17}
,{'7', 17}
,{'8', 17}
,{'9', 4}
,{'a', 17}
,{'b', 17}
,{'c', 17}
,{'d', 17}
,{'e', 17}
,{'f', 17}
,{'g', 17}
,{'h', 17}
,{'i', 8}
,{'j', 17}
,{'k', 17}
,{'l', 17}
,{'m', 17}
,{'n', 17}
,{'o', 17}
,{'p', 17}
,{'q', 17}}
,
// state 13
{{'0', 17}
,{'1', 0}
,{'2', 2}
,{'3', 17}
,{'4', 17}
,{'5', 3}
,{'6', 17}
,{'7', 17}
,{'8', 17}
,{'9', 17}
,{'a', 17}
,{'b', 3}
,{'c', 17}
,{'d', 17}
,{'e', 17}
,{'f', 17}
,{'g', 17}
,{'h', 17}
,{'i', 17}
,{'j', 17}
,{'k', 17}
,{'l', 17}
,{'m', 17}
,{'n', 17}
,{'o', 17}
,{'p', 17}
,{'q', 17}}
,
// state 14
{{'0', 4}
,{'1', 17}
,{'2', 17}
,{'3', 6}
,{'4', 17}
,{'5', 17}
,{'6', 7}
,{'7', 17}
,{'8', 17}
,{'9', 6}
,{'a', 17}
,{'b', 17}
,{'c', 7}
,{'d', 17}
,{'e', 17}
,{'f', 17}
,{'g', 17}
,{'h', 17}
,{'i', 7}
,{'j', 17}
,{'k', 17}
,{'l', 17}
,{'m', 17}
,{'n', 17}
,{'o', 17}
,{'p', 17}
,{'q', 17}}
,
// state 15
{{'0', 1}
,{'1', 17}
,{'2', 17}
,{'3', 17}
,{'4', 17}
,{'5', 17}
,{'6', 17}
,{'7', 17}
,{'8', 17}
,{'9', 17}
,{'a', 17}
,{'b', 17}
,{'c', 17}
,{'d', 17}
,{'e', 17}
,{'f', 17}
,{'g', 17}
,{'h', 17}
,{'i', 17}
,{'j', 17}
,{'k', 17}
,{'l', 17}
,{'m', 17}
,{'n', 17}
,{'o', 17}
,{'p', 17}
,{'q', 17}}
,
// state 16
{{'0', 1}
,{'1', 17}
,{'2', 17}
,{'3', 17}
,{'4', 17}
,{'5', 17}
,{'6', 17}
,{'7', 17}
,{'8', 17}
,{'9', 17}
,{'a', 17}
,{'b', 17}
,{'c', 17}
,{'d', 17}
,{'e', 17}
,{'f', 17}
,{'g', 17}
,{'h', 17}
,{'i', 17}
,{'j', 17}
,{'k', 17}
,{'l', 17}
,{'m', 17}
,{'n', 17}
,{'o', 17}
,{'p', 17}
,{'q', 17}}
,
// state 17
{{'0', 17}
,{'1', 17}
,{'2', 17}
,{'3', 17}
,{'4', 17}
,{'5', 17}
,{'6', 17}
,{'7', 17}
,{'8', 17}
,{'9', 17}
,{'a', 17}
,{'b', 17}
,{'c', 17}
,{'d', 17}
,{'e', 17}
,{'f', 17}
,{'g', 17}
,{'h', 17}
,{'i', 17}
,{'j', 17}
,{'k', 17}
,{'l', 17}
,{'m', 17}
,{'n', 17}
,{'o', 17}
,{'p', 17}
,{'q', 17}}};

map<char, string> CharIntMap
{
    {'0', "000"},
    {'1', "001"},
    {'2', "002"},
    {'3', "010"},
    {'4', "011"},
    {'5', "012"},
    {'6', "020"},
    {'7', "021"},
    {'8', "022"},
    {'9', "100"},
    {'a', "101"},
    {'b', "102"},
    {'c', "110"},
    {'d', "111"},
    {'e', "112"},
    {'f', "120"},
    {'g', "121"},
    {'h', "122"},
    {'i', "200"},
    {'j', "201"},
    {'k', "202"},
    {'l', "210"},
    {'m', "211"},
    {'n', "212"},
    {'o', "220"},
    {'p', "221"},
    {'q', "222"}
};

// Initialize fibo and superfibo values.
void Initialize()
{
    // Pell numbers.
    Pells[0] = 1;
    Pells[1] = 2;
    for(int i = 2; i < WordLength; i++)
    {
        Pells[i] = 2 * Pells[i - 1] + Pells[i - 2];
    }
}

string BasePell(ll n)
{
    string s = "";
    if (n == 0)
    {
        s += chr(0);
        return s;
    }

    bool leading = true;
    for (int i = WordLength - 1; i >= 0; i--)
    {
        if (2LL*Pells[i] <= n)
        {
            s += chr(2);
            n -= 2*Pells[i];
            leading = false;
        }
        else if (Pells[i] <= n)
        {
            s += chr(1);
            n -= Pells[i];
            leading = false;
        }
        else if (!leading)
        {
            s += chr(0);
        }
    }

    return s;
}

string GetTripletString(string x, string y, string z)
{
    string s = "";
    int k;
    int n = max(x.length(), max(y.length(), z.length()));
    while (x.length() != n) x.insert(0, 1, chr(0));
    while (y.length() != n) y.insert(0, 1, chr(0));
    while (z.length() != n) z.insert(0, 1, chr(0));

    for (int i = 0; i < n; i++)
    {
        k = 9*ord(x[i]) + 3*ord(y[i]) + ord(z[i]);
        if (k < 10) s += chr(k);
        else s += (char)(87 + k);
    }

    return s;
}

int GetNumFromString(string s)
{
    int n = s.length();
    int x = 0;
    int j = 0;
    for (int i = n-1; i >= 0; i--)
    {
        x += ord(s[i])*Pells[j++];
    }

    return x;
}

vector<int> GetXYZ(string ts)
{
    string sx = "", sy = "", sz = "";
    int n = ts.length();
    int k;
    for (int i = 0; i < n; i++)
    {
        string triplet = CharIntMap[ts[i]];
        sx += triplet[0];
        sy += triplet[1];
        sz += triplet[2];
    }

    vector<int> v;
    v.push_back(GetNumFromString(sx));
    v.push_back(GetNumFromString(sy));
    v.push_back(GetNumFromString(sz));

    return v;
}

int IsAccepted(string s)
{
    int state = q0;
    int n = s.length();
    for (int i = 0; i < n; i++)
    {
        state = transition[state][s[i]];
        // cout << i << ": " << state << "\n";
    }

    return (state == qf[0] || state == qf[1] || state == qf[2]);
}

int main()
{
    Initialize();
    // cout << Pells[WordLength - 1] << "\n";

    mt19937 rng;
    uniform_int_distribution<mt19937::result_type> dist8(0, MAX);
    int a;
    cin >> a;
    while(a--)
    {
        rng.seed(random_device()());
        ll a = dist8(rng);
        ll b = dist8(rng);
        ll c = dist8(rng);
        ll d = dist8(rng);
        ll e = dist8(rng);
        ll f = dist8(rng);

        ll x = a*b;
        ll y = c*d;
        ll z = e*f;
        ll zeq = x + y;

        // cout << x << " " << y << " " << z <<"\n";
        string sx, sy, sz, szeq;
        sx = BasePell(x);
        sy = BasePell(y);
        sz = BasePell(z);
        szeq = BasePell(zeq);
        // cout << sx << " " << sy << " " << sz <<"\n";

        string ts = GetTripletString(sx, sy, sz);
        string tseq = GetTripletString(sx, sy, szeq);
        // IsAccepted("13f9bc7aaabc94k0a0aaa");
        if((!IsAccepted(tseq)) || IsAccepted(ts))
        {
            cout << x << " " << y << " " << z << "\n";
            cout << sx << " " << sy << " " << sz << "\n";
            cout << ts << "\n-------------\n";
        }
    }
}
