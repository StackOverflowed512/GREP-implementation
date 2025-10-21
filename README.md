# CppGrep: A Command-Line Text Search Utility

CppGrep is a powerful and efficient command-line tool for searching plain text and regular expressions in files. It is built in C++ and leverages the highly efficient Knuth-Morris-Pratt (KMP) algorithm for direct string matching, and includes a basic custom regex engine for pattern matching.

## Features

-   **High-performance string searching:** Utilizes the KMP algorithm for fast pattern matching.
-   **Regular Expression Support:** A custom-built regex engine to handle patterns.
-   **Case-Insensitive Search:** Option to perform case-insensitive searches.
-   **Count Occurrences:** A feature to count the number of matching lines.

## How to Compile and Run

To compile and run CppGrep, you will require a C++ compiler (like g++).

1.  **Compilation:**

    Compile the source files together using the following command:

    ```bash
    g++ main.cpp kmp.cpp utils.cpp regex_engine.cpp -o cppgrep
    ```

2.  **Execution:**

    Run the compiled program with the following command structure:

    ```bash
    ./cppgrep [OPTIONS] <filename> <pattern>
    ```

## Usage and Examples

### Basic Search

To find a specific word in a file:

```bash
./cppgrep sample.txt "hello"
```

### Case Insensitive search

Use the -i flag for a case-insensitive search:

```bash
./cppgrep -i sample.txt "hello"
```

### Counting Matches

To count the number of lines containing the pattern, use the -c flag:

```bash
./cppgrep -c sample.txt "world"
```

### Regular Expression Search

For a regex pattern search, use the -E flag:

```bash
./cppgrep -E sample.txt "^start"
```

This will find lines that start with the word "start".

### File Descriptions

main.cpp: The main entry point of the program, responsible for parsing command-line arguments and file processing.
kmp.h / kmp.cpp: Contains the implementation of the Knuth-Morris-Pratt (KMP) string searching algorithm.
utils.h / utils.cpp: Provides utility functions, such as string manipulation.
regex_engine.h / regex_engine.cpp: Implements the custom regular expression engine.

### Algorithm Explanations

## Knuth-Morris-Pratt (KMP) Algorithm

The KMP algorithm is an efficient string searching algorithm that finds occurrences of a pattern within a text. It preprocesses the pattern to create a partial match table, which helps in skipping unnecessary comparisons, making it faster than naive string searching algorithms, especially for large texts.

## Regex Engine

The custom regex engine is a simple, backtracking engine that supports the following special characters:
.: Matches any single character.
\*: Matches the preceding element zero or more times.
^: Matches the beginning of the string.
$: Matches the end of the string.
This engine works by stepping through the regex and the text, and when a token fails to match, it backtracks to a previous position to try a different path.
