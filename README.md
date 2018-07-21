# c

A number of little C programs created to learn the language. Most of them are portable but some require GCC and Linux.

Folders prefixed with `osu_` are related to the game [osu!](osu.ppy.sh/).

Folders prefixed with `win_` rely in the Windows API, anything else can be compiled with [MinGW](http://mingw.org/) or regular GCC.

Some of the folders contain solved exercises from the book "The C Programming Language" by K&R, these are listed below. Some of them have been altered slightly.

### fold_lines

**Exercise 1-22**

Contains two functions: `void fold_line_char(char *line, int max)` and `void fold_line_word(char *line, int max)`. Both take a null terminated string as their first argument and a maxium as their second. The maximum is the amount of characters or words (depending on the function) after which to 'fold' the line with a newline character.

A word is defined as a string of n characters surrounded by one or more blank characters.

### strip_comments

**Exercise 1-23**

Strips a code file passed through stdin of comments, passing it to stdout as it is processed. Works with all languages which follow Cs comment syntax (C++, JS & co, Java, ...).

### check_syntax

**Exercise 1-24**

Checks a C code file for rudimentary syntax errors like unmatched parentheses, brackets and braces.

Since the checks are performed at such a basic level, this will work for a number of languages with syntax similar to C.

### find_substr

**Exercise 2-5**

Relevant function: `int any(char *base, char *sub)`. Returns the index of the string `sub` within `base`, or -1 if it was not found.

### basic_calculator

**Chapter 4.3**

Simple calculator using reverse Polish notation.

### check_pid

Checks if a process with an ID given through the `-p` flag exists.