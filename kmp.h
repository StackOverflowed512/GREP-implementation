#ifndef KMP_H
#define KMP_H

#include <string>
#include <vector>

void constructLps(std::string &pat, std::vector<int> &lps);
std::vector<int> search(std::string &pat, std::string &txt);

// wrapper used by main()
int kmpSearch(const std::string &text, const std::string &pattern);

#endif
