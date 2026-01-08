#include "regex_engine.h"
#include "utils.h"

using namespace std;

// match pattern starting at text[i], pattern[j]
bool matchHere(const string &p, int j, const string &t, int i)
{
    // pattern finished → success
    if (j == p.size())
        return true;

    // next pattern char is '*'
    if (j + 1 < p.size() && p[j + 1] == '*')
    {
        // try all repetitions of p[j]
        while (i < t.size() && (p[j] == '.' || p[j] == t[i]))
        {
            if (matchHere(p, j + 2, t, i))
                return true;
            i++;
        }
        return matchHere(p, j + 2, t, i);
    }

    // anchor $
    if (p[j] == '$' && j + 1 == p.size())
        return i == t.size();

    // normal char must match then advance
    if (i < t.size() && (p[j] == '.' || p[j] == t[i]))
        return matchHere(p, j + 1, t, i + 1);

    return false;
}

bool custom_regex_search(const string &pattern,
                         const string &text,
                         bool caseInsensitive)
{
    string p = pattern;
    string t = text;

    if (caseInsensitive)
    {
        p = toLower(p);
        t = toLower(t);
    }

    // alternation |
    size_t pos = p.find('|');
    if (pos != string::npos)
        return custom_regex_search(p.substr(0, pos), t, false) ||
               custom_regex_search(p.substr(pos + 1), t, false);

    // anchor ^ (must match from start)
    if (!p.empty() && p[0] == '^')
        return matchHere(p, 1, t, 0);

    // otherwise try match anywhere
    for (int i = 0; i <= (int)t.size(); i++)
        if (matchHere(p, 0, t, i))
            return true;

    return false;
}
