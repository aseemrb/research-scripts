#include "../helpers.h"
using namespace std;

const int MAX = 1e8;
const int WordLength = 40;
ll Fibos[WordLength];
ll Pells[WordLength];
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
    // Fibo and SuperFibo numbers.
    Fibos[0] = 1;
    Fibos[1] = 2;
    Pells[0] = 1;
    Pells[1] = 2;
    for(int i = 2; i < WordLength; i++)
    {
        Fibos[i] = Fibos[i - 1] + Fibos[i - 2];
        Pells[i] = 2 * Pells[i - 1] + Pells[i - 2];
    }
}

string BasePell(int n)
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
        if (2*Pells[i] <= n)
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

int main()
{
    Initialize();
    vector<int> v = GetXYZ("1f23d4aa53l4i0q0c0g9e0");
    cout << v[0] << "\n" << v[1] << "\n" << v[2] << "\n";

    mt19937 rng;
    uniform_int_distribution<mt19937::result_type> dist8(0, MAX);
    int a = 10;
    while(a--)
    {
        rng.seed(random_device()());
        int x = dist8(rng);
        int y = dist8(rng);
        int z = x + y;

        // cout << x << " " << y << " " << z <<"\n";
        string sx, sy, sz;
        sx = BasePell(x);
        sy = BasePell(y);
        sz = BasePell(z);
        // cout << sx << " " << sy << " " << sz <<"\n";

        string ts = GetTripletString(sx, sy, sz);
        cout << ts << "\n";
    }
}
