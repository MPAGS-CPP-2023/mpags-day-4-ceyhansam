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

    std::cout << "Inside setKey" << std::endl;
    int j = 0;
    int k = 0;
    int keySize = key_.size();
    std::cout << "keySize = " << keySize << std::endl;
    for (int i = 0; i < keySize; i++) {
        if (j < 5) {
            std::pair<char, std::pair<int, int>> charCoord{key_[i], {k,j}};
            std::pair<std::pair<int, int>, char> coordChar{{k,j}, key_[i]};
            keyMatrix.insert(charCoord);
            coordMatrix.insert(coordChar);
            j++;
        } else {
            j = 0;
            k++;
            std::pair<char, std::pair<int, int>> charCoord{key_[i], {k,j}};
            std::pair<std::pair<int, int>, char> coordChar{{k,j}, key_[i]};
            keyMatrix.insert(charCoord);
            coordMatrix.insert(coordChar);
            j++;
        }
    }

    std::for_each(key_.begin(), key_.end(), [&](char& x) {auto iter3 = keyMatrix.find(x); 
                                                        std::cout << (*iter3).first << ": {" << (*iter3).second.first 
                                                        << (*iter3).second.second << "}" << std::endl;});
    std::cout << "Exiting setKey" << std::endl;

    // Store the playfair cipher key map 
}

std::string PlayfairCipher::applyCipher(const std::string& inputText, const CipherMode cipherMode) const {

    std::string cipherText = inputText;
    int cipherSize = cipherText.size();
    std::cout << cipherSize << std::endl;
    std::cout << "applyCipher has been called with " << inputText << std::endl;
    std::cout << "key is " << key_ << std::endl;
    switch (cipherMode) {
        case CipherMode::Encrypt:
                    // Change J → I
            std::transform(std::begin(cipherText), std::end(cipherText), std::begin(cipherText), [] (char x) {return (x == 'J') ? 'I' : x;});
        
            // If repeated chars in a digraph add an X or Q if XX
            for(int i=1; i<cipherSize;) {
                if (cipherText[i-1] == 'X' && cipherText[i] == 'X') {
                    cipherText.insert(i, 1, 'Q');
                    i+=2;
                } else if (cipherText[i-1] == cipherText[i]) {
                    cipherText.insert(i, 1, 'X');
                    i+=2;
                } else {i+=2;}
            }

            // if the size of input is odd, add a trailing Z
            if (cipherText.size() % 2 != 0) {
                cipherText+='Z';
            }
            
            // Loop over the input in Digraphs
            
            // - Find the coords in the grid for each digraph

            // - Apply the rules to these coords to get 'new' coords

            // - Find the letter associated with the new coords
            cipherSize = cipherText.size();
            for(int i=1; i<cipherSize; i+=2) {
                auto charCoord1 = (*keyMatrix.find(cipherText[i-1])).second;
                auto charCoord2 = (*keyMatrix.find(cipherText[i])).second;
                if (charCoord1.first == charCoord2.first) { //Checking if Rows are Equal
                    charCoord1 = charCoord2;
                    if (charCoord2.second == 4) {
                        charCoord2 = std::pair<int, int>{charCoord2.first, charCoord2.second % 4};
                    } else {
                        charCoord2 = std::pair<int, int>{charCoord2.first, charCoord2.second + 1};
                    }

                    cipherText[i-1] = (*coordMatrix.find(charCoord1)).second;
                    cipherText[i] = (*coordMatrix.find(charCoord2)).second;
                } else if (charCoord1.second == charCoord2.second) {
                    charCoord1 = charCoord2;
                    if (charCoord2.first == 4) {
                        charCoord2 = std::pair<int, int>{charCoord2.first % 4, charCoord2.second};
                    } else {
                        charCoord2 = std::pair<int, int>{charCoord2.first + 1, charCoord2.second};
                    } 
                    
                    cipherText[i-1] = (*coordMatrix.find(charCoord1)).second;
                    cipherText[i] = (*coordMatrix.find(charCoord2)).second;
                } else {
                    auto tempCoord = charCoord1.second;
                    charCoord1.second = charCoord2.second;
                    charCoord2.second = tempCoord;
                    
                    cipherText[i-1] = (*coordMatrix.find(charCoord1)).second;
                    cipherText[i] = (*coordMatrix.find(charCoord2)).second;
                }
            }
            break;

        case CipherMode::Decrypt:
            std::cout << "Decrypt" << std::endl;
            break;
    }
    // return the text
    return cipherText;
}