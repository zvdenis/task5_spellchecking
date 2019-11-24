#include <iostream>
#include <fstream>
#include <string>
#include "dictionary.h"


Dictionary::Dictionary(string filename) {

    /*
     * Код взят из ДЗ 3 файл journal_net_activity.hpp
     * Все совпадения случайны!
     * */

    std::ifstream fin(filename);
    if(!fin)
        throw std::invalid_argument("Check the file path");

    while (fin){
        string word;
        fin >> word;
        this->insert(word);
    }
}
