#include "regex_engine.h"
#include <cctype>
#include <vector>
using namespace std;

// Forward declaration for the recursive helper function
static bool match_here(const char *pattern, const char *text, bool case_insensitive);

/**
 * @brief 
 */
static bool match_char(char p, char t, bool case_insensitive)
{
    if (case_insensitive)
    {
        return tolower(p) == tolower(t);
    }
    return p == t;
}

/**
 * @brief Main recursive function to match a pattern at the beginning of a text.
 *
 * This function implements the core logic of the backtracking regex engine.
 * It supports:
 * - `.`: matches any single character.
 * - `*`: matches the preceding element zero or more times.
 * - `^`: matches the beginning of the string (handled in `custom_regex_search`).
 * - `$`: matches the end of the string.
 */
static bool match_here(const char *pattern, const char *text, bool case_insensitive)
{
    if (pattern[0] == '\0')
    {
        return true;
    }
    if (pattern[1] == '*')
    {
        // Try matching zero instances of the preceding element, then one or more.
        return match_here(pattern + 2, text, case_insensitive) ||
               (*text != '\0' && (pattern[0] == '.' || match_char(pattern[0], *text, case_insensitive)) && match_here(pattern, text + 1, case_insensitive));
    }
    if (pattern[0] == '$' && pattern[1] == '\0')
    {
        return *text == '\0';
    }
    if (*text != '\0' && (pattern[0] == '.' || match_char(pattern[0], *text, case_insensitive)))
    {
        return match_here(pattern + 1, text + 1, case_insensitive);
    }
    return false;
}

/**
 * @brief 
 */
static bool match_alternatives(const string &pattern, const string &text, bool case_insensitive)
{
    
    size_t pipe_pos = pattern.find('|');

    if (pipe_pos == string::npos)
    {
        
        const char *p = pattern.c_str();
        const char *t = text.c_str();

        
        if (p[0] == '^')
        {
            return match_here(p + 1, t, case_insensitive);
        }

        do
        {
            if (match_here(p, t, case_insensitive))
            {
                return true;
            }
        } while (*t++ != '\0');

        return false;
    }

    // Split by pipe and try each alternative
    std::string left = pattern.substr(0, pipe_pos);
    std::string right = pattern.substr(pipe_pos + 1);

    return match_alternatives(left, text, case_insensitive) ||
           match_alternatives(right, text, case_insensitive);
}

bool custom_regex_search(const std::string &pattern, const std::string &text, bool case_insensitive)
{
    if (pattern.empty())
    {
        return true;
    }

    return match_alternatives(pattern, text, case_insensitive);
}