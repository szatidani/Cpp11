#pragma once
#include <vector>
#include <string>
#include <map>
#include <set>

using wordlist = std::vector<std::string>;
using charset = std::set<char>;
using wordmap = std::map<std::string, std::vector<std::string>>;

class WordHandler {
public:
    WordHandler(int life): life{life}{}
    ~WordHandler() = default;
    void play();
    int getDictionary();
    bool loadWordList(int length);
    void calculateSolution();
    std::string createPattern(std::string word);
    void setSolution(wordmap& wmap);
    bool evaluateWinningCondition();
    bool evaluateLosingCondition();
    bool heckConditions();
    void printStatus();
    void chooseWord();
    char getCharacter();
    bool evaluateTipp(char c);
    bool checkConditions();

private:
    wordlist current_words;
    charset guessed_letters;
    std::string secret_word;
    std::string secret_pattern;
    int life;
};
