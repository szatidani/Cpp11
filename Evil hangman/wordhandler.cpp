#include "wordhandler.hpp"
#include <algorithm>
#include <iostream>
#include <stdlib.h>
#include <fstream>

void WordHandler::play(){
    int wsize;
    do {
        wsize = getDictionary();
    } while (!loadWordList(wsize));

    chooseWord();
    while (true)
    {
        char guess;
        do {
            printStatus();
            guess = getCharacter();
        } while (!evaluateTipp(guess));
        if (checkConditions())
            break;
    }
}
std::string WordHandler::createPattern(std::string word){
    std::string pattern;
    for(auto c : word)
    {
        if (guessed_letters.find(c) == guessed_letters.end())
        {
            pattern += '_';
        }
        else
        {
            pattern += c;
        }
    }

    return pattern;
}
void WordHandler::setSolution(wordmap &wmap){
    unsigned int max_size = 0;
    std::string max_index;

    for(auto record : wmap)
    {
        if (max_size < record.second.size())
        {
            max_size = record.second.size();

            max_index = record.first;
        }
    }

    if (secret_pattern.compare(max_index) == 0)
    {
        life--;
    }

    current_words = wmap[max_index];
    secret_pattern = max_index;
    chooseWord();
}
void WordHandler::calculateSolution(){
    if (current_words.empty())
    {
        std::cout << "Empty wordlist!";
        return;
    }

    wordmap wmap;
    std::string pattern;

    for(auto word : current_words)
    {
        pattern = createPattern(word);
        auto it = wmap.find(pattern);
        //if pattern already exists in map
        if(it != wmap.end())
        {
            it->second.push_back(word);
        }
        else
        {
            wordlist wlist;
            wlist.push_back(word);
            wmap[pattern] = wlist;
        }
    }

    setSolution(wmap);

    return;
}
bool WordHandler::evaluateWinningCondition(){
    if (secret_word.compare(secret_pattern) == 0)
    {
        return true;
    }

    return false;
}
bool WordHandler::evaluateLosingCondition(){
    if (life == 0)
    {
        return true;
    }
    return false;
}
void WordHandler::printStatus(){
    //hide solution if not debugging
    std::cout << secret_pattern << "(" << secret_word << ") "<< current_words.size() << "\tRemaining guesses: " << life << std::endl;
    std::cout << "Used letters: ";
    for (auto it : guessed_letters)
    {
        std::cout << it << " ";
    }
    std::cout << std::endl;
}
bool WordHandler::checkConditions(){
    if (evaluateWinningCondition())
    {
        std::cout << std::endl << "YOU WIN!" << std::endl;
        return true;
    }
    if (evaluateLosingCondition())
    {
        std::cout << std::endl << "GAME OVER! Solution: " << secret_word << std::endl;
        return true;
    }
    return false;
}
char WordHandler::getCharacter(){
    char guess;
    std::cout << "Make a guess: ";
    std::cin >> guess;

    if (isalpha(guess))
    {
        return tolower(guess);
    }
    else
    {
        std::cout << std::endl << "Invalid character!" << std::endl << std::endl;
        return '1';
    }
}
bool WordHandler::evaluateTipp(char c){
    if (c == '1') return false;
    if (guessed_letters.find(c) != guessed_letters.end())
    {
        std::cout << std::endl << "You've already used this!" << std::endl << std::endl;
        return false;
    }
    else
    {
        guessed_letters.insert(c);
        calculateSolution();
        return true;
    }
}
void WordHandler::chooseWord(){
    int idx;
    if (current_words.size() - 1 > 0)
    {
        idx = rand() % (current_words.size() -1);
    }
    else
    {
        idx = 0;
    }

    secret_word = current_words.at(idx);
}
bool WordHandler::loadWordList(int wsize){
    if (wsize == -1) return false;

    std::ifstream dictionary ("dictionary.txt");
    std::string line;
    current_words.clear();
    if (dictionary.is_open())
    {
        while (dictionary.good())
        {
          std::getline(dictionary, line);
          if (line.size() == static_cast<unsigned>(wsize))
          {
              current_words.push_back(line);
          }
        }
        dictionary.close();
        return true;
    }
    else
    {
        std::cout << "Unable to open file"<< std::endl;
        return false;
    }
}
int WordHandler::getDictionary(){
    unsigned int wsize;
    unsigned int wmin = 3;
    unsigned int wmax = 22; //todo set from corpus
    std::cout << "Set word length (" << wmin << " - " <<  wmax << "): ";
    std::cin >> wsize;
    if((wsize <= wmax) && (wsize >= wmin)){
        for(unsigned int i = 0; i<wsize; i++) secret_pattern += "_";
        return wsize;
    }
    else{
        std::cout << "Invalid length!" << std::endl;
        return -1;
    }
}
