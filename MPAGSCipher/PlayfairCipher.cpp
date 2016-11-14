
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
	
	
	for ( auto elem : char2PairMap_ ) {
		std::cout << elem.first << " | " << elem.second.first << " : " << elem.second.second << std::endl;
	}
	
}

std::string PlayfairCipher::applyCipher( const std::string& inputText, const CipherMode cipherMode ) const
{
	std::string textToCiph = inputText; // Keep input text in case wanted
	
	// Change J -> I
	std::transform(textToCiph.begin(), textToCiph.end(), textToCiph.begin(), [] (char c) { if (c == 'J') return 'I'; else return c;} );
	std::cout << textToCiph << std::endl;
	
	// Find repeated chars and add an X
	for (auto iter = std::begin(textToCiph); iter != textToCiph.end(); iter+=2) {
		std::cout << *iter << " : " << *(iter+1) << std::endl;
		if ( iter == textToCiph.end()-1 ) {
			if ( *iter == 'Z' ) textToCiph += 'Q'; // Otherwise program breaks if last letter is Z
			else textToCiph += 'Z';
		}
		if ( *iter == *(iter+1) && *iter != 'X') {
			textToCiph.insert(iter+1, 'X');
		}
		else if ( *iter == *(iter+1) && *iter == 'X') {
			textToCiph.insert(iter+1, 'Q');
		}
	}

	std::cout << textToCiph << std::endl;
	
	// If the size of input is odd, add a trailing Z
	//if ( textToCiph.length() %2 != 0 ) {
	//	textToCiph += 'Z';
	//}
	/*
	// Loop over the input in Digraphs
	for (auto iter = std::begin(textToCiph) ; iter != textToCiph.end() ; iter+=2) {
		
	// 	- Find the coords in the grid for each digraph
		auto char1 = *iter;
		auto char1Row = (*char2PairMap_.find(char1)).second.first;
		auto char1Col = (*char2PairMap_.find(char1)).second.second;
		
		auto char2 = *(iter+1);
		auto char2Row = (*char2PairMap_.find(char2)).second.first;
		auto char2Col = (*char2PairMap_.find(char2)).second.second;
		
		std::cout << "iter: " << *iter << " | position: " << char1Row << " : " << char1Col << std::endl;
		std::cout << "iter: " << *(iter+1) << " | position: " << char2Row << " : " << char2Col << std::endl;
		
	// 	- Apply the rules to these coords to get 'new' coords
		int shift = (cipherMode == CipherMode::Encrypt) ? 1 : -1;
		
		if ( char1Row == char2Row ) {
			int char1ColNew = ((char1Col + shift) > -1) ? ( (char1Col + shift) % 5 ) : 4;
			int char2ColNew = ((char2Col + shift) > -1) ? ( (char2Col + shift) % 5 ) : 4;
			char1 = ( *pair2CharMap_.find( std::make_pair( char1Row, char1ColNew) ) ).second;
			char2 = ( *pair2CharMap_.find( std::make_pair( char2Row, char2ColNew) ) ).second;	
		}
	
		else if ( char1Col == char2Col ) {
			int char1RowNew = ((char1Row + shift) > -1) ? ( (char1Row + shift) % 5 ) : 4;
			int char2RowNew = ((char2Row + shift) > -1) ? ( (char2Row + shift) % 5 ) : 4;
			char1 = ( *pair2CharMap_.find( std::make_pair( char1RowNew, char1Col ) ) ).second;
			char2 = ( *pair2CharMap_.find( std::make_pair( char2RowNew, char2Col ) ) ).second;	
		}
		
		else {
			char1 = ( *pair2CharMap_.find( std::make_pair(char1Row,char2Col) ) ).second;
			char2 = ( *pair2CharMap_.find( std::make_pair(char2Row,char1Col) ) ).second;
		}
		
		std::cout << char1 << " : " << char2 << std::endl;
	// 	- Find the letter associated with the new coords
	std::cout << textToCiph << std::endl;	
	}*/

	// return the text
	
	std::string outputText{inputText};
	
	CipherMode temp = cipherMode;
	
	temp = temp;

	outputText = "Testing_playfair";
	
	return outputText;
}
