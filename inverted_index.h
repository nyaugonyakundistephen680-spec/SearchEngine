#ifndef INVERTED_INDEX_H
#define INVERTED_INDEX_H
#include <unordered_map>
#include <vector>
#include <string>
class InvertedIndex {
   
    public:
    // Add a document to the inverted index
    // documentID: Unique identifier for the document
    // content: The text content of the document
    private:
        void addDocument(int documentID, const std::string& content) {
        //seeach for documents containing all worrds in the query
        //query: Space-separated list of words to search for
        //Returns vector of document IDS sorted by relevance (most relevant first)  
        std::vector<int> search(const std::string& query);

        std::unordered_map<std::string, std::vector<int>> index; // Map from word to list of document IDs    // Helper function to tokenize the content into words
        std::vector<std::string> tokenize(const std::string& content);

        // Helper function to find intetsection of multiple sorted vectors of document IDs
        std::vector<int> intersect(const std::vector<std::vector<int>>& lists);
        }
};

#endif // INVERTED_INDEX_H

