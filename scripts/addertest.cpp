#include "../helpers.h"
using namespace std;

const int MAX = 1e8;
const int WordLength = 45;
ll Pells[WordLength];

// Define the automaton here.
// States
int states[7] = { 0, 1, 2, 3, 4, 5, 6 };

// Initial and final states
const int q0 = 0;
int qf[3] = {0, 3, 5};

// Transition table
map<int, int> transition[18] =
{
    // state 0
    {
        {0, 0},
        {1, 1}
    },
    // state 1
    {
        {-1, 2},
        {-2, 3},
        {-3, 4}
    },
    // state 2
    {
        {-4, 4},
        {-3, 3},
        {-2, 2}
    },
    // state 3
    {
        {-1, 0},
        {0, 1}
    },
    // state 4
    {
        {1, 5},
        {2, 6}
    },
    // state 5
    {
        {1, 0},
        {2, 1}
    },
    // state 6
    {
        {-2, 4},
        {-1, 3},
        {0, 2}
    }
};

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

int IsAccepted(vector<int> &s)
{
    int state = q0;
    for (auto &it : s)
    {
        if (transition[state].find(it) == transition[state].end())
        {
            cout << "STATE: " << state << ", SYMBOL: " << it << "\n";
            return false;
        }
        state = transition[state][it];
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
        // string ts = GetTripletString(sx, sy, sz);
        // string tseq = GetTripletString(sx, sy, szeq);

        vector<int> rr;
        reverse(sx.begin(), sx.end());
        reverse(sy.begin(), sy.end());
        reverse(szeq.begin(), szeq.end());
        for(int i = 0; i < szeq.length(); i++)
        {
            int ax = 0, ay = 0, az = 0;
            if(i < sx.length()) ax = ord(sx[i]);
            if(i < sy.length()) ay = ord(sy[i]);
            az = ord(szeq[i]);
            rr.push_back(az - ax - ay);
        }

        reverse(rr.begin(), rr.end());
        reverse(sx.begin(), sx.end());
        reverse(sy.begin(), sy.end());
        reverse(szeq.begin(), szeq.end());

        if (!IsAccepted(rr))
        {
            for(auto &it : rr)
                cout << it << ", ";
            cout << sx << " " << sy << " " << szeq << "\n";
        }
    }
}
