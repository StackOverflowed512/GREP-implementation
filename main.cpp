#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "kmp.h"
#include "utils.h"
#include "regex_engine.h" // Include the custom regex engine
using namespace std;

int main(int argc, char *argv[])
{
    bool caseInsensitive = false;
    bool countOnly = false;
    bool useRegex = false;
    string filename, pat;

    // Parse command line arguments
    if (argc >= 3)
    {
        for (int i = 1; i < argc - 2; i++)
        {
            string option = argv[i];
            if (option == "-i")
            {
                caseInsensitive = true;
            }
            else if (option == "-c")
            {
                countOnly = true;
            }
            else if (option == "-E")
            {
                useRegex = true;
            }
        }

        filename = argv[argc - 2];
        pat = argv[argc - 1];
    }
    else
    {
        cerr << "Usage: " << argv[0] << " [-i] [-c] [-E] <filename> <pattern>\n";
        cerr << "Options:\n";
        cerr << "  -i  Case insensitive search\n";
        cerr << "  -c  Count only (print only count of matching lines)\n";
        cerr << "  -E  Use regular expression pattern\n";
        return 1;
    }

    ifstream file(filename);
    if (!file)
    {
        cerr << "Unable to open file.\n";
        return 1;
    }

    string line;
    int lineNumber = 0;
    int matchCount = 0;

    if (!useRegex && caseInsensitive)
    {
        pat = toLowerCase(pat);
    }

    while (getline(file, line))
    {
        lineNumber++;

        bool patternFound = false;

        if (useRegex)
        {
            // Use custom regex matching function
            if (custom_regex_search(pat, line, caseInsensitive))
            {
                patternFound = true;
            }
        }
        else
        {
            // Use KMP matching
            string tempLine = line;
            if (caseInsensitive)
                tempLine = toLowerCase(tempLine);

            vector<int> res = search(pat, tempLine);
            patternFound = !res.empty();
        }

        if (patternFound)
        {
            matchCount++;
            if (!countOnly)
            {
                cout << "Pattern found in line number: " << lineNumber << endl;
            }
        }
    }

    if (countOnly)
    {
        cout << "Total matches found: " << matchCount << endl;
    }
    else if (matchCount == 0)
    {
        cout << "Pattern not found.\n";
    }

    file.close();
    return 0;
}