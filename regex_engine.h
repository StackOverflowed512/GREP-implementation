#ifndef REGEX_ENGINE_H
#define REGEX_ENGINE_H

#include <string>

/**
 * @brief Searches for a regular expression pattern within a text.
 *
 * @param pattern The regular expression pattern.
 * @param text The text to search within.
 * @param case_insensitive Whether the search should be case-insensitive.
 * @return true if the pattern is found, false otherwise.
 */
bool custom_regex_search(const std::string &pattern, const std::string &text, bool case_insensitive);

#endif // REGEX_ENGINE_H