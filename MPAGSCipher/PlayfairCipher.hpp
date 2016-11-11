#ifndef MPAGSCIPHER_PLAYFAIRCIPHER_HPP
#define MPAGSCIPHER_PLAYFAIRCIPHER_HPP

// Standard library includes
#include <string>
#include <vector>
#include <map>

// Our project headers
#include "CipherMode.hpp"

/**
 * \file PlayfairCipher.hpp
 * \brief Contains the declaration of the PlayfairCipher class
 */

/**
 * \class PlayfairCipher
 * \brief Encrypt or decrypt text using the Playfair cipher with the given key
 */
class PlayfairCipher {
  public:
    /**
     * Create a new PlayfairCipher with the given key
     *
     * \param key the key to use in the cipher
     */
    PlayfairCipher( const std::string& key );

	void setKey( const std::string& key );
	
	std::string applyCipher( const std::string& inputText, const CipherMode cipherMode ) const;
	
	private:
	
	std::string key_ = "";
	
	using Char2PairMap = std::map<char, std::pair<int,int>>;
	Char2PairMap char2PairMap_;
	
	using Pair2CharMap = std::map<std::pair<int,int>, char>;
	Pair2CharMap pair2CharMap_;
	
};

#endif
