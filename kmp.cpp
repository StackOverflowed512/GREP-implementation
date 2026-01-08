#include "kmp.h"

using namespace std;

void constructLps(string &pat, vector<int> &lps)
{
    int len = 0;
    lps[0] = 0;
    int i = 1;

    while (i < pat.length())
    {
        if (pat[i] == pat[len])
        {
            len++;
            lps[i] = len;
            i++;
        }
        else
        {
            if (len != 0)
                len = lps[len - 1];
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}

vector<int> search(string &pat, string &txt)
{
    int n = txt.length();
    int m = pat.length();
    vector<int> lps(m);
    vector<int> res;

    constructLps(pat, lps);

    int i = 0, j = 0;
    while (i < n)
    {
        if (txt[i] == pat[j])
        {
            i++;
            j++;
            if (j == m)
            {
                res.push_back(i - j);
                j = lps[j - 1];
            }
        }
        else
        {
            if (j != 0)
                j = lps[j - 1];
            else
                i++;
        }
    }

    return res;
}

// thin wrapper (returns first match index or -1)
int kmpSearch(const string &text, const string &pattern)
{
    string pat = pattern;
    string txt = text;

    auto matches = search(pat, txt);
    return matches.empty() ? -1 : matches[0];
}
