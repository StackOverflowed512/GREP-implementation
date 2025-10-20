#ifndef KMP_H
#define KMP_H

#include <string>
#include <vector>
using namespace std;

void constructLps(string &pat, vector<int> &lps);

vector<int> search(string &pat, string &txt);

#endif
