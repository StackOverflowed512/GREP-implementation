#include "utils.h"
#include <algorithm>
using namespace std;

string toLowerCase(string s)
{
    transform(s.begin(), s.end(), s.begin(), ::tolower);
    return s;
}
