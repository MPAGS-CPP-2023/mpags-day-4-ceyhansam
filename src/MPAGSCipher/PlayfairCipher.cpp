#include "PlayfairCipher.hpp"

#include <string>
#include <iostream>
#include <algorithm>
#include <map>

PlayfairCipher::PlayfairCipher (const std::string& key) {
    this->setKey(key);
}

void PlayfairCipher::setKey(const std::string& key) {
    // store the original key
    key_ = key;

    // Append the alphabet
    key_ += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    // Make sure the key is uppercase
    std::transform(std::begin(key_), std::end(key_), std::begin(key_), ::toupper);

    // Remove non-alpha chars
    auto iter = std::remove_if(std::begin(key_), std::end(key_), [] (char x) {return !std::isalpha(x); });

    key_.erase(iter, std::end(key_));

    // Change J -> I
    std::transform(std::begin(key_), std::end(key_), std::begin(key_), [] (char x) {return (x == 'J') ? 'I' : x;});

    // Remove duplicate letters
    std::string foundChar{};

    auto dupeChar = [&] (char x) {if (std::string::npos == foundChar.find(x)) {
        foundChar+=x;
        return false;
    } else {
        return true;
    }}; 

    auto iter2 = std::remove_if(std::begin(key_), std::end(key_), dupeChar);

    key_.erase(iter2, std::end(key_));

    // Store the coords of each letter
    using pfPairs = std::map<std::string, std::pair<int, int>>;

    pfPairs keyMatrix;

    char keyChar = 'x';

    while (key_ >> keyChar) {

    }

    std::pair<std::string, std::pair<int, int>> p0{"A", {0,0}};

    keyMatrix.insert(p0);

    auto iter3 = keyMatrix.find("A");
    std::cout << (*iter3).first << ": " << (*iter3).second.first << (*iter3).second.second << std::endl;

    // Store the playfair cipher key map 
}

std::string PlayfairCipher::applyCipher(const std::string& inputText, const CipherMode cipherMode) const {
    std::cout << "applyCipher has been called with " << inputText << std::endl;
    std::cout << "key is " << key_ << std::endl;
    switch (cipherMode) {
        case CipherMode::Encrypt:
            std::cout << "Encrypt" << std::endl;
            break;

        case CipherMode::Decrypt:
            std::cout << "Decrypt" << std::endl;
            break;
    }
    return 0;
    // Change J → I
 
    // If repeated chars in a digraph add an X or Q if XX
    
    // if the size of input is odd, add a trailing Z
    
    // Loop over the input in Digraphs
    
    // - Find the coords in the grid for each digraph

    // - Apply the rules to these coords to get 'new' coords

    // - Find the letter associated with the new coords

    // return the text
}