#include "inverted_index.h"
#include <algorithm>   // for std::sort and std::set_intersection
#include <cctype>     // for std::tolower
#include <sstream>    // for std::istringstream
void InvertedIndex::addDocument(int documentID, const std::string& content) {
auto words = tokenize(content);
for (const auto& word : words) {
auto& docList = index[word];
// add document ID to the list if it's not already present(to avoid duplicates)
if (std::find(docList.begin(), docList.end(), documentID) == docList.end()) {
    docList.push_back(documentID);
}
}
// Sort the document lists for efficient intersection later
for (auto& entry : index) {
    std::sort(entry.second.begin(), entry.second.end());
}

::vector<int> InvertedIndex::search(const std::string& query) {
auto queryWords = tokenize(query);
if (queryWords.empty()) {
    return {};
}
std::vector<std::vector<int>> docLists;
for (const auto& word : queryWords) {
    auto it = index.find(word);
    if (it != index.end()) {
        docLists.push_back(it->second);
    } else {
        // If any word is not found, return empty result
        return {};
    }
}
return intersect(docLists);
}
std::vector<std::string> InvertedIndex::tokenize(const std::string& content) {
    std::vector<std::string> tokens;
    std::istringstream iss(content);
    std::string token;
    while (iss >> token) {
        // Convert to lowercase for case-insensitive matching
        std::transform(token.begin(), token.end(), token.begin(), ::tolower);
        tokens.push_back(token);
    }
    return tokens;
}
std::vector<int> InvertedIndex::intersect(const std::vector<std::vector<int>>& lists) {
    if (lists.empty()) {
        return {};
    }
std::vector<int> result = lists[0];
// Intersect with each subsequent list
for(size_t i = 1; i < lists.size(); ++i) {
    std::vector<int> temp;
    std::set_intersection(result.begin(), result.end(), lists[i].begin(), lists[i].end(), std::back_inserter(temp));
    result = std::move(temp);
}
return result;
}