#include "helpers.h"
using namespace std;

const int MAX = 1e8;
const int WordLength = 40;
ll Fibos[WordLength];
ll Pells[WordLength];

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

int main()
{
    Initialize();
    mt19937 rng;
    uniform_int_distribution<mt19937::result_type> dist8(0, MAX);
    int a = 10;
    while(a--)
    {
        rng.seed(random_device()());
        int x = dist8(rng);
        int y = dist8(rng);
        int z = dist8(rng);

        cout << x << " " << y << " " << z <<"\n";
        string sx, sy, sz;
        sx = BasePell(x);
        sy = BasePell(y);
        sz = BasePell(z);
        cout << sx << " " << sy << " " << sz <<"\n";

        string ts = GetTripletString(sx, sy, sz);
        cout << ts << "\n";
    }
}
