#ifndef MPAGSCIPHER_CIPHERTYPE_HPP
#define MPAGSCIPHER_CIPHERTYPE_HPP

/**
 * \file CipherType.hpp
 * \brief Contains the declaration of the CipherType enumeration
 */

/**
 * \enum CipherType
 * \brief Enumeration to define the types of ciphers used
 */
enum class CipherType {
  Caesar, ///< Apply cipher in caesar type
  Playfair  ///< Apply cipher in playfair type
};

#endif // MPAGSCIPHER_CIPHERTYPE_HPP 
