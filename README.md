_The repository will be archived as of the time of this commit._

# c

A number of little C programs created to learn the language. Most of them are portable but some require GCC and Linux.

Folders prefixed with `osu_` are related to the game [osu!](osu.ppy.sh/).

Folders prefixed with `win_` rely on the Windows API.

Folders prefixed with `x11_` rely on a reasonably up to date version of the X Window System.

Some of the folders contain solved exercises from the book "The C Programming Language" by K&R, a non exhaustive list can be found below. Some of them have been altered slightly.

### fold_lines

**Exercise 1-22**

Contains two functions: `void fold_line_char(char *line, int max)` and `void fold_line_word(char *line, int max)`. Both take a C-style string as their first, and a maximum as their second argument. The line will be folded with a newline after `max` characters or words have been encountered.

A word is defined as a sequence of characters surrounded on both ends by one or more whitespace characters which are not considered a part of the word.

### strip_comments

**Exercise 1-23**

Strips a code file passed through `stdin` of comments, passing it to `stdout` as it is processed. Works with all languages which follow C's comment syntax (C++, JS & co, Java, etc.).

### check_syntax

**Exercise 1-24**

Checks a C code file for rudimentary syntax errors like unmatched parentheses, brackets and braces.

Since the checks are performed at such a basic level, this will work for a number of languages with syntax similar to C (see above).

### find_substr

**Exercise 2-5**

Relevant function: `int any(char *base, char *sub)`. Returns the index of the string `sub` within `base`, or -1 if it was not found.

### basic_calculator

**Chapter 4.3**

Simple calculator using reverse Polish notation. Depends on the `math.h` header; compile with `-lm` set if using GCC.
