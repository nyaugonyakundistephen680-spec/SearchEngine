#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <cctype>
using namespace std;

// ------------------ TRIE STRUCTURE ------------------
struct TrieNode
{
    unordered_map<char, TrieNode *> children;
    bool isEndOfWord = false;
};

class Trie
{
public:
    TrieNode *root;
    Trie() { root = new TrieNode(); }

    void insert(const string &word)
    {
        TrieNode *node = root;
        for (char c : word)
        {
            if (!node->children[c])
            {
                node->children[c] = new TrieNode();
            }
            node = node->children[c];
        }
        node->isEndOfWord = true;
    }

    bool search(const string &word)
    {
        TrieNode *node = root;
        for (char c : word)
        {
            if (!node->children[c])
                return false;
            node = node->children[c];
        }
        return node->isEndOfWord;
    }

    bool startsWith(const string &prefix)
    {
        TrieNode *node = root;
        for (char c : prefix)
        {
            if (!node->children[c])
                return false;
            node = node->children[c];
        }
        return true;
    }
};

// ------------------ HELPER FUNCTIONS ------------------
string normalizeWord(string word)
{
    string result;
    for (char c : word)
    {
        if (!ispunct(c))
            result += tolower(c);
    }
    return result;
}

vector<string> readFileWords(const string &filename)
{
    ifstream file(filename);
    vector<string> words;
    if (!file.is_open())
    {
        cerr << "Error: Could not open file." << endl;
        return words;
    }
    string line, word;
    while (getline(file, line))
    {
        stringstream ss(line);
        while (ss >> word)
        {
            word = normalizeWord(word);
            if (!word.empty())
                words.push_back(word);
        }
    }
    return words;
}

// ------------------ ALGORITHMS ------------------
void linearSearch(const vector<string> &words, const string &target)
{
    cout << "[Linear Search] Scanning file word by word..." << endl;
    int count = 0;
    for (size_t i = 0; i < words.size(); i++)
    {
        if (words[i] == target)
        {
            cout << "Found '" << target << "' at position " << i << endl;
            count++;
        }
    }
    cout << "Total occurrences: " << count << endl;
}

void hashMapSearch(const vector<string> &words, const string &target)
{
    cout << "[Hash Map] Building frequency table..." << endl;
    unordered_map<string, int> freq;
    for (const string &w : words)
    {
        freq[w]++;
    }
    cout << "Lookup for '" << target << "'..." << endl;
    if (freq.find(target) != freq.end())
    {
        cout << "Word found with frequency: " << freq[target] << endl;
    }
    else
    {
        cout << "Word not found." << endl;
    }
}

void trieSearch(const vector<string> &words, const string &target)
{
    cout << "[Trie] Inserting words into Trie..." << endl;
    Trie trie;
    for (const string &w : words)
    {
        trie.insert(w);
    }
    cout << "Searching for exact word '" << target << "'..." << endl;
    if (trie.search(target))
    {
        cout << "Word found in Trie!" << endl;
    }
    else
    {
        cout << "Word not found in Trie." << endl;
    }
    cout << "Checking prefix '" << target << "'..." << endl;
    if (trie.startsWith(target))
    {
        cout << "There are words starting with '" << target << "'." << endl;
    }
    else
    {
        cout << "No words start with '" << target << "'." << endl;
    }
}

// ------------------ MAIN ------------------
int main()
{
    string filename, target;
    int choice;

    cout << "Enter filename: ";
    cin >> filename;
    cout << "Enter word to search: ";
    cin >> target;
    target = normalizeWord(target);

    vector<string> words = readFileWords(filename);
    if (words.empty())
        return 1;

    cout << "\nChoose algorithm:\n";
    cout << "1. Linear Search\n";
    cout << "2. Hash Map Search\n";
    cout << "3. Trie Search\n";
    cout << "Enter choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        linearSearch(words, target);
        break;
    case 2:
        hashMapSearch(words, target);
        break;
    case 3:
        trieSearch(words, target);
        break;
    default:
        cout << "Invalid choice." << endl;
    }

    return 0;
}
