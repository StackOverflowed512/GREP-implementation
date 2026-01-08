#include <iostream>
#include <fstream>
#include <string>
#include <mutex>
#include <atomic>

#include "utils.h"
#include "kmp.h"
#include "regex_engine.h"
#include "ThreadPool.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        cout << "Usage: ./grep <options> <filename> <pattern>\n";
        return 1;
    }

    bool caseInsensitive = false;
    bool countOnly = false;
    bool useRegex = false;

    string filename;
    string pat;

    int argIndex = 1;
    while (argIndex < argc && argv[argIndex][0] == '-')
    {
        string opt = argv[argIndex];

        if (opt == "-i")
            caseInsensitive = true;
        else if (opt == "-c")
            countOnly = true;
        else if (opt == "-E")
            useRegex = true;

        argIndex++;
    }

    filename = argv[argIndex++];
    pat = argv[argIndex];

    if (caseInsensitive)
        pat = toLower(pat);

    ifstream file(filename);
    if (!file.is_open())
    {
        cout << "Could not open file.\n";
        return 1;
    }

    string line;
    int lineNumber = 0;

    atomic<int> matchCount{0};
    mutex printMutex;

    {
        ThreadPool pool(thread::hardware_concurrency());

        while (getline(file, line))
        {
            int currentLine = ++lineNumber;
            string copy = line;
            string patternCopy = pat;

            pool.enqueue([=, &matchCount, &printMutex, &caseInsensitive, &useRegex, &countOnly]() mutable
                         {

                if (caseInsensitive)
                    copy = toLower(copy);

                bool patternFound = false;

                if (useRegex)
                {
                    patternFound =
                        custom_regex_search(patternCopy, copy, caseInsensitive);
                }
                else
                {
                    patternFound =
                        (kmpSearch(copy, patternCopy) != -1);
                }

                if (patternFound)
                {
                    matchCount++;

                    if (!countOnly)
                    {
                        lock_guard<mutex> lock(printMutex);
                        cout << "Pattern found in line number: "
                             << currentLine << endl;
                    }
                } });
        }
    }

    if (countOnly)
        cout << "Total matches found: " << matchCount << endl;
    else if (matchCount == 0)
        cout << "Pattern not found.\n";

    return 0;
}
