//! Unit Tests for MPAGSCipher PlayfairCipher Class
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "PlayfairCipher.hpp"

TEST_CASE ("Playfair Cipher encryption", "[playfair]") {
	PlayfairCipher cipher { "playfairexample" };
	REQUIRE (cipher.applyCipher( "HIDETHEGOLDINTHETREESTUMP", CipherMode::Encrypt ) == "BMODZBXDNABEKUDMUIXMMOUVIF" );
}

TEST_CASE ("Playfair Cipher decryption", "[playfair]") {
	PlayfairCipher cipher { "playfairexample" };
	REQUIRE (cipher.applyCipher( "BMODZBXDNABEKUDMUIXMMOUVIF", CipherMode::Decrypt ) == "HIDETHEGOLDINTHETREXESTUMP" );
}