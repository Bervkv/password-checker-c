# Password Strength Checker (C)

A command-line tool, written in C, that evaluates password strength using
composition rules, entropy calculation, a common-password wordlist check,
and predictable-pattern detection.

## What it checks

1. Composition rules — length, uppercase, lowercase, digits, symbols
2. Entropy — length x log2(pool_size)
3. Common password lookup against a 10,000-entry wordlist (SecLists)
4. Leetspeak normalization (@ -> a, 3 -> e, 1 -> i, 0 -> o, $/5 -> s)
   re-checked against the wordlist
5. Repetition detection (e.g. aaaa)
6. Sequence detection (ascending/descending runs, e.g. abc, 123, cba)

## Build & run

    gcc checker.c -o checker -lm
    ./checker

common_passwords.txt must be in the same directory as the compiled binary.

## What I learned

- Bounded string functions (fgets/strncpy-style) vs unbounded (gets/strcpy)
- The classic = vs == bug in C conditionals
- Manual memory ownership: allocating and tracking a dynamically loaded
  wordlist, unlike a garbage-collected Python set

## Known limitations

- Sequence detection catches alphabetic/numeric runs but not physical
  keyboard-row sequences like qwerty
- Wordlist lookup is a linear scan, not a hash table
