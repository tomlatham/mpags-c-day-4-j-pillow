
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
	//std::cout << key_ << std::endl;
	
	// Append the alphabet
	key_ += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	//std::cout << key_ << std::endl;
	
	// Make sure the key is upper case
	std::transform(key_.begin(), key_.end(), key_.begin(), toupper );
	//std::cout << key_ << std::endl;
	
	// Remove non-alpha characters
	key_.erase(std::remove_if( key_.begin(), key_.end(), [] (char c) { return !std::isalpha(c); } ),key_.end());
	//std::cout << key_ << std::endl;
	
	// Change J -> I	
	std::transform(key_.begin(), key_.end(), key_.begin(), [] (char c) { if (c == 'J') return 'I'; else return c;} );
	//std::cout << key_ << std::endl;
	
	// Remove duplicated letters
	std::string encChar{""};
	auto detectDuplicates = [&encChar](char c) {
		if ( encChar.find(c) != std::string::npos ) {
			return true;
		} else {
			encChar += c;
			return false;
		}
	};
	key_.erase(std::remove_if(key_.begin(),key_.end(), detectDuplicates ),key_.end());
	//std::cout << key_ << std::endl;	
	
	// Store the coords of each letter
	int x{0}, y{0};
	for ( auto elem : key_ ) {
		auto coord = std::make_pair(x,y);
		char2PairMap_[elem] = coord; // Stores cipher key map
		pair2CharMap_[coord] = elem; // Stores cipher key map
		
		if (y < 4) {
			y++;
		} else {
			x++;
			y = 0;
		}
	}
	
	/*
	for ( auto elem : char2PairMap_ ) {
		std::cout << elem.first << " | " << elem.second.first << " : " << elem.second.second << std::endl;
	}*/
	
}

std::string PlayfairCipher::applyCipher( const std::string& inputText, const CipherMode cipherMode ) const
{
	std::string textToCiph { inputText }; // Keep input text in case wanted
	
	// Change J -> I
	std::transform(textToCiph.begin(), textToCiph.end(), textToCiph.begin(), [] (char c) { if (c == 'J') return 'I'; else return c;} );
	//std::cout << textToCiph << std::endl;
	
	
	if (cipherMode == CipherMode::Encrypt) {
		// Find repeated chars and add an X
		size_t nTextToCiph = textToCiph.length();				// Set length of the text to cipher to a variable
		for (  size_t i{0} ; i < nTextToCiph ; i+=2 ) { 		// Loop over the text injecting X's next to repeated chars in digraphs with 
			if ( i == nTextToCiph - 1 ) {						// If at last character of string add Z. Done because only reaches last character if lenght is odd  
				if (textToCiph[i] == 'Z') textToCiph +="Q"; // If last char is Z add a Q otherwise it breaks
				else textToCiph+="Z";							// Else, add a Z
			}
			else if ( textToCiph[i] == textToCiph[i+1]  && textToCiph[i] != 'X') { // If both chars of digraph are same then insert X between
				textToCiph.insert(i+1,"X");
				nTextToCiph = textToCiph.length();
			}
			else if ( textToCiph[i] == textToCiph[i+1] && textToCiph[i] == 'X') { // Unless chars are already X then insert Q
				textToCiph.insert(i+1,"Q");
				nTextToCiph = textToCiph.length();
			}
		}
	}
	
	std::string outputText{""};
	const int shift = (cipherMode == CipherMode::Encrypt) ? 1 : -1; // Use to set positive or negative shift dependent on encrypt or decrypt
	
	// Loop over the input in Digraphs
	for (auto iter = std::begin(textToCiph) ; iter != std::end(textToCiph) ; iter+=2) { // Loop over text to cipher with +=2 for digraphs
		
		// 	- Find the coords in the grid for each digraph
		auto char1 = *iter;
		const auto char1Row = (*char2PairMap_.find(char1)).second.first;
		const auto char1Col = (*char2PairMap_.find(char1)).second.second;
		
		auto char2 = *(iter+1);
		const auto char2Row = (*char2PairMap_.find(char2)).second.first;
		const auto char2Col = (*char2PairMap_.find(char2)).second.second;
		
		//std::cout << "iter: " << *iter << " | position: " << char1Row << " : " << char1Col << std::endl;
		//std::cout << "iter: " << *(iter+1) << " | position: " << char2Row << " : " << char2Col << std::endl;
		
		/* 	- Apply the rules to these coords to get 'new' coords
			- Find the Letter associated with the new coords */
		if ( char1Row == char2Row ) {
			// The next two lines just make sure that if decrypting column 0, then it wraps round as % on a -ve number throws an error
			int char1ColNew = (5 + char1Col + shift) % 5; 
			int char2ColNew = (5 + char2Col + shift) % 5;
			char1 = ( *pair2CharMap_.find( std::make_pair( char1Row, char1ColNew) ) ).second;
			char2 = ( *pair2CharMap_.find( std::make_pair( char2Row, char2ColNew) ) ).second;	
		}
	
		else if ( char1Col == char2Col ) {
			// The next two lines just make sure that if decrypting row 0, then it wraps round as % on a -ve number throws an error
			int char1RowNew = (5 + char1Row + shift) % 5; 
			int char2RowNew = (5 + char2Row + shift) % 5;
			char1 = ( *pair2CharMap_.find( std::make_pair( char1RowNew, char1Col ) ) ).second;
			char2 = ( *pair2CharMap_.find( std::make_pair( char2RowNew, char2Col ) ) ).second;	
		}
		
		else {
			// Decryption here is the same as encrypting as just swaps column of each char
			char1 = ( *pair2CharMap_.find( std::make_pair(char1Row,char2Col) ) ).second;
			char2 = ( *pair2CharMap_.find( std::make_pair(char2Row,char1Col) ) ).second;
		}
		outputText += char1;
		outputText += char2;
		//std::cout << char1 << " : " << char2 << std::endl;
		//std::cout << textToCiph << std::endl;	
	}

	// return the text
	return outputText;
}
