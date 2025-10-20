#include <bits/stdc++.h>
#include "kmp.h"
#include "utils.h"
using namespace std;

int main(int argc, char *argv[])
{
    bool caseInsensitive = false;
    string filename, pat;

    if (argc == 4 && string(argv[1]) == "-i")
    {
        caseInsensitive = true;
        filename = argv[2];
        pat = argv[3];
    }
    else if (argc == 3)
    {
        filename = argv[1];
        pat = argv[2];
    }
    else
    {
        cerr << "Usage: " << argv[0] << " [-i] <filename> <pattern>\n";
        return 1;
    }

    ifstream file(filename);
    if (!file)
    {
        cerr << "Unable to open file.\n";
        return 1;
    }

    if (caseInsensitive)
        pat = toLowerCase(pat);

    string line;
    int lineNumber = 0;
    bool found = false;

    while (getline(file, line))
    {
        lineNumber++;

        string tempLine = line;
        if (caseInsensitive)
            tempLine = toLowerCase(tempLine);

        vector<int> res = search(pat, tempLine);

        if (!res.empty())
        {
            cout << "Pattern found in line " << lineNumber << endl;
            found = true;
        }
    }

    if (!found)
        cout << "Pattern not found.\n";

    file.close();
    return 0;
}
