//* This file is for testing the Crypto++ library and check we are able to use it to do want we want to
#include <string>
#include <iostream>

#include "cryptlib.h"
#include "osrng.h"
#include "sha.h"
#include "aes.h"
#include "hex.h"
#include "integer.h"
#include "pwdbased.h"
#include "modes.h"

// Procedure to do:
// take the user password
// key = sha1(sha1(password))
// stored_password = DES(message=key, key, iv)
// store the stored_password AND the IV

// When checking if the password provided is the right one:
// take the password -> sha1 -> sha1
// try to decrypt the stored_password with this key and the salt
// if stored_password == sha1(sha1(given_password)) => OK, sinon KO

// Then unencrypt things in memory... 

const std::string HEXSALT = "E5579A8EC1FB90310103718E4DF80495";
const std::string HEXIV = "B56E5AC5D1F2E4873E7F408C51F4ED52";

int main(int argc, char * argv[])
{
	using namespace std;
	using namespace CryptoPP;
	string password = "tralala";
	unsigned int iterations = 1;

	// AutoSeededX917RNG<AES> rng;

	// SecByteBlock iv(AES::BLOCKSIZE);
	// rng.GenerateBlock(iv,iv.size());

	// See NIST SP 800-132 for detailed recommendations on length, generation and
	// format of the salt. This test program will just generate a random one. That
	// might not be sufficient for every application.
	// SecByteBlock pwsalt(AES::DEFAULT_KEYLENGTH);
	// rng.GenerateBlock(pwsalt,pwsalt.size());
	
	SecByteBlock recoveredsalt(AES::DEFAULT_KEYLENGTH);
	StringSource saltDecoder(HEXSALT,true,new HexDecoder(new ArraySink(recoveredsalt, recoveredsalt.size())));
	SecByteBlock recoverediv(AES::BLOCKSIZE);
	StringSource ivDecoder(HEXIV,true,new HexDecoder(new ArraySink(recoverediv, recoverediv.size())));
	

	SecByteBlock derivedkey(AES::DEFAULT_KEYLENGTH);
	
	cout << "Password is " << password << endl;
	cout << "Deriving key from password:" << endl;
	PKCS5_PBKDF2_HMAC<SHA256> pbkdf;
	pbkdf.DeriveKey(
		// buffer that holds the derived key
		derivedkey, derivedkey.size(),
		// purpose byte. unused by this PBKDF implementation.
		0x00,
		// password bytes. careful to be consistent with encoding...
		(byte *) password.data(), password.size(),
		// salt bytes
		recoveredsalt, recoveredsalt.size(),
		// iteration count. See SP 800-132 for details. You want this as large as you can tolerate.
		// make sure to use the same iteration count on both sides...
		iterations
		);
	cout << "Done" << endl;


	string message = "tralala";
	string ciphertext;

	CBC_Mode<AES>::Encryption aesencryption(derivedkey,derivedkey.size(), recoverediv);
	// encrypt message using key derived above, storing the hex encoded result into ciphertext
	StringSource encryptor(message,true,
		new StreamTransformationFilter(aesencryption, new HexEncoder( new StringSink(ciphertext)))
		);

	// hex encode salt and IV for "transport"
	// string hexsalt, hexiv;
	// ArraySource saltEncoder(pwsalt,pwsalt.size(), true, new HexEncoder(new StringSink(hexsalt)));
	// ArraySource ivEncoder(iv,iv.size(), true, new HexEncoder(new StringSink(hexiv)));
	cout << "Salt: " << HEXSALT << endl;
	cout << "IV: " << HEXIV << endl;
	cout << "Ciphertext: " << ciphertext << endl;
	
	// now recover the plain text given the password, salt, IV and ciphertext
	SecByteBlock recoveredkey(AES::DEFAULT_KEYLENGTH);
	cout << "Re-deriving encryption key based on encoded values above." << endl;
	pbkdf.DeriveKey(recoveredkey, recoveredkey.size(), 0x00, (byte *) password.data(), password.size(),
		recoveredsalt, recoveredsalt.size(), iterations);
	cout << "Done." << endl;
	
	CBC_Mode<AES>::Decryption aesdecryption(recoveredkey, recoveredkey.size(), recoverediv);
	string recoveredtext;
	ciphertext = "997DE8E6AD76399A1E5D47F5154A5D26";
	try {
		StringSource decryptor(ciphertext, true, new HexDecoder(
			new StreamTransformationFilter(aesdecryption, new StringSink(recoveredtext))
			));
	} catch(Exception e) {
		cerr << "\nException raised: " << e.what() << endl;
	}
	cout << "Recovered plaintext value: " << recoveredtext << endl;

	return 0;

}