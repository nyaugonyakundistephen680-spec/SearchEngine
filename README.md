# SearchEngine

A C++ console project that demonstrates and compares three ways to search words in a text file:

- Linear search over a vector of words
- Hash map frequency lookup
- Trie-based exact and prefix search

The program reads a text file, normalizes all words (lowercase, punctuation removed), and then searches for a target word using a user-selected algorithm.

## What this project does

The executable asks for:

1. A filename to read
2. A target word to search
3. Which algorithm to use

Then it loads the file, tokenizes it into words, normalizes text, and runs one of the following:

- `Linear Search`: scans every word and prints positions where the target appears
- `Hash Map Search`: builds a frequency table and reports total count for the target
- `Trie Search`: builds a trie, checks exact match, and checks if the target is a prefix of any word

## How it works

### 1) Text normalization

Each word is processed by `normalizeWord`:

- Converts characters to lowercase
- Removes punctuation

This means searches are case-insensitive with respect to file content and ignore punctuation around words.

### 2) File reading and tokenization

`readFileWords` opens the input file and reads line by line.
Each line is split into words using a string stream, normalized, and stored in a `vector<string>`.

If the file cannot be opened, the program prints an error and exits.

### 3) Search algorithms

- `linearSearch(words, target)`
  - Time: O(n)
  - Reports every index where the target appears

- `hashMapSearch(words, target)`
  - Build table: O(n)
  - Lookup: average O(1)
  - Reports frequency count

- `trieSearch(words, target)`
  - Build trie: O(total characters)
  - Exact query: O(m)
  - Prefix query: O(m)
  - (`m` = length of target)

## Project structure

- `Main.cpp`: all core logic (normalization, reading, algorithms, menu, trie implementation)
- `data.txt`: sample text file for testing
- `build/`: build output directory (contains executable in your current setup)

## Running instructions

### Option A: Run existing executable (Windows PowerShell)

If `build/Main.exe` already exists:

```powershell
./build/Main.exe
```

When prompted, try:

- Filename: `data.txt`
- Search word: `apple`
- Choice: `1`, `2`, or `3`

### Option B: Build from source and run

### Windows (PowerShell + g++)

1. Build:

```powershell
g++ .\Main.cpp -std=c++17 -O2 -o .\build\Main.exe
```

2. Run:

```powershell
./build/Main.exe
```

### macOS/Linux (bash/zsh + g++)

1. Build:

```bash
g++ ./Main.cpp -std=c++17 -O2 -o ./build/Main
```

2. Run:

```bash
./build/Main
```

## Example with included sample data

`data.txt` contains:

```text
Apple banana apple orange banana apple
```

Searching for `apple` gives:

- Linear search: positions and total occurrences
- Hash map search: frequency of 3
- Trie search: exact match found, prefix check result

## Notes and limitations

- Input filename is currently read as a single token (spaces in path are not supported by `cin >> filename`).
- Trie memory is not manually freed at program end (acceptable for short-lived demo runs, but could be improved with destructors/smart pointers).
- All algorithms rebuild their data structures each run, which is fine for demonstration but not optimized for repeated queries.
