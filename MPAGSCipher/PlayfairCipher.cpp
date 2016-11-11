
// Standard library includes
#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

// Out project headers
#include "PlayfairCipher.hpp"

PlayfairCipher::PlayfairCipher( const std::string& key )
  : key_{""}
{
	setKey(key);
}

void PlayfairCipher::setKey( const std::string& key) {
	// store the original key
	key_ = key;
	std::cout << key_ << std::endl;
	
	// Append the alphabet
	key_ += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::cout << key_ << std::endl;
	
	// Make sure the key is upper case
	std::transform(key_.begin(), key_.end(), key_.begin(), toupper );
	std::cout << key_ << std::endl;
	
	// Remove non-alpha characters
	key_.erase(std::remove_if( key_.begin(), key_.end(), [] (char c) { return !std::isalpha(c); } ),key_.end());
	std::cout << key_ << std::endl;
	
	// Change J -> I	
	std::transform(key_.begin(), key_.end(), key_.begin(), [] (char c) { if (c == 'J') return 'I'; else return c;} );
	std::cout << key_ << std::endl;
	
	// Remove duplicated letters
	std::string encChar{""};
	key_.erase(std::remove_if(key_.begin(),key_.end(), [&encChar] (char c) { std::size_t found = encChar.find(c) ; if ( found!=std::string::npos ) return true; else { encChar += c ; return false; } } ),key_.end());
	std::cout << key_ << std::endl;	
	
	// Store the coords of each letter
	int x{0}, y{0};
	for ( auto elem : key_ ) {
		auto coord = std::make_pair(x,y);
		char2PairMap_[elem] = coord; // Stores cipher key map
		pair2CharMap_[coord] = elem; // Stores cipher key map
		
		if (y < 4) y++;
		else {
			x++;
			y = 0;
		}
	}
	
	/*
	for ( auto elem : char2PairMap_ ) {
		std::cout << elem.first << " : " << elem.second.first << " : " << elem.second.second << std::endl;
	}
	*/
}

std::string PlayfairCipher::applyCipher( const std::string& inputText, const CipherMode cipherMode ) const
{
	// Change J -> I
	
	// Find repeated chars and add an X
	
	// If the size of input is odd, add a trailing Z
	
	// Loop over the input in Digraphs
	
	// 	- Find the coords in the grid for each digraph
	
	// 	- Apply the rules to these coords to get 'new' coords
	
	// 	- Find the letter associated with the new coords
	
	// return the text
	
	std::string outputText{inputText};
	
	CipherMode temp = cipherMode;
	
	temp = temp;

	outputText = "Testing_playfair";
	
	return outputText;
}
