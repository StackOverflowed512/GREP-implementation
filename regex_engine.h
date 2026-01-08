#ifndef REGEX_ENGINE_H
#define REGEX_ENGINE_H

#include <string>

bool custom_regex_search(const std::string &pattern,
                         const std::string &text,
                         bool caseInsensitive);

#endif
