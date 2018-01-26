#include <iostream>
#include "wordhandler.hpp"
#include <time.h>
#include <stdlib.h>
/*
Felhasznalt irodalom: https://www.cs.duke.edu/courses/compsci101/cps006/spring11/assign/evilhang/howto.html
File olvasas forrasa: http://stackoverflow.com/questions/6399822/reading-a-text-file-fopen-vs-ifstream
*/

int main()
{
    srand (time(NULL));
    unsigned int n_guess = 15; //number of guesses
    WordHandler wh(n_guess);
    std::cout << "Evil Hangman" << std::endl;
    std::cout << "You have " << n_guess << " guesses, good luck!" << std::endl;
    wh.play();
    return 0;
}
