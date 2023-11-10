#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

#include "CipherMode.hpp"


#include <cstddef>
#include <string>
#include <vector>

class PlayfairCipher {
    public:
        /**
         * \brief Create a PlayfairCipher with the given key
         * 
         * \param key the key that will be used in the setKey function
        */
        explicit PlayfairCipher(const std::string& key);

        /**
         * 
         * 
        */
        void setKey(const std::string& key);

        /**
         * 
         * 
        */
        std::string applyCipher(const std::string& inputText, const CipherMode cipherMode) const;

    private:

        std::string key_{""};

        const std::vector<char> alphabet_{
            'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
            'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
        
        const std::size_t alphabetSize_{alphabet_.size()};

};

#endif