#include <bits/stdc++.h>
using namespace std;

// Returns (CritExp, (Len, Period)) for the finite word s.
pair<double, pair<int, int> > ComputeCritExp(string &s)
{
    double tce = 1;
    double ex = 1;
    pair<int, int> len_period = make_pair(1, 1);

    int n = s.length();
    for (int i = 0; i < n; i++)
    {
        for (int p = 1; p < n; p++)
        {
            int j = i;
            while (j + p < n)
            {
                if (s[j] != s[j+p])
                {
                    break;
                }

                j++;
            }

            ex = (double)(j+p-i)/(double)(p);
            if (ex > tce)
            {
                tce = ex;
                len_period.first = j+p-i;
                len_period.second = p;
            }
        }
    }

    return make_pair(tce, len_period);
}

int main()
{
    int n;
    string f, test;
    ifstream fib("f.txt");
    getline(fib, f);
    int sz = f.length();

    while (true)
    {
        cin >> n;
        if (n <= 0) return 0;

        double max_ce = 0;
        double min_ce = DBL_MAX;
        int len = 0, period = 0;
        for (int i = 0; i+n < sz; i++)
        {
            test = f.substr(i, n);
            pair<double, pair<int, int> > pr = ComputeCritExp(test);

            // if (pr.first > max_ce)
            if (pr.first < min_ce)
            {
                // max_ce = pr.first;
                min_ce = pr.first;
                len = pr.second.first;
                period = pr.second.second;
            }
        }

        // cout << "Max CE: " << max_ce << "\n";
        cout << "Min CE: " << min_ce << "\n";
        cout << "Length: " << len << "\n";
        cout << "Period: " << period << "\n";
    }

    return 0;
}
