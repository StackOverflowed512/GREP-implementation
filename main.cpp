#include <bits/stdc++.h>
#include "kmp.h"
#include "utils.h"
using namespace std;

int main(int argc, char *argv[])
{
    bool caseInsensitive = false;
    bool countOnly = false;
    string filename, pat;

    if (argc == 4)
    {
        string option = argv[1];
        if (option == "-i")
        {
            caseInsensitive = true;
        }
        else if (option == "-c")
        {
            countOnly = true;
        }
        filename = argv[2];
        pat = argv[3];
    }
    else if (argc == 5)
    {
        string option1 = argv[1];
        string option2 = argv[2];

        if ((option1 == "-i" && option2 == "-c") || (option1 == "-c" && option2 == "-i"))
        {
            caseInsensitive = true;
            countOnly = true;
        }
        filename = argv[3];
        pat = argv[4];
    }
    else if (argc == 3)
    {
        filename = argv[1];
        pat = argv[2];
    }
    else
    {
        cerr << "Usage: " << argv[0] << " [-i] [-c] <filename> <pattern>\n";
        cerr << "Options:\n";
        cerr << "  -i  Case insensitive search\n";
        cerr << "  -c  Count only (print only count of matching lines)\n";
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
    int matchCount = 0;

    while (getline(file, line))
    {
        lineNumber++;

        string tempLine = line;
        if (caseInsensitive)
            tempLine = toLowerCase(tempLine);

        vector<int> res = search(pat, tempLine);

        if (!res.empty())
        {
            matchCount++;
            if (!countOnly)
            {
                cout << "Pattern found in line " << lineNumber << endl;
            }
        }
    }

    if (countOnly)
    {
        cout << matchCount << endl;
    }
    else if (matchCount == 0)
    {
        cout << "Pattern not found.\n";
    }

    file.close();
    return 0;
}