#include <filezilla.h>
#include "crypto.h"

#include "../interface/Options.h"

#include <string>

#include "cryptlib.h"
#include "osrng.h"
#include "sha.h"
#include "aes.h"
#include "hex.h"
#include "integer.h"
#include "pwdbased.h"
#include "modes.h"

#ifdef TD_DBG
std::ofstream F_LOG("/tmp/FZ.log");
#endif

const std::string CCrypto::HEXSALT = "E5579A8EC1FB90310103718E4DF80495";
const std::string CCrypto::HEXIV = "B56E5AC5D1F2E4873E7F408C51F4ED52";
wxString CCrypto::masterPassword;

using namespace std;

wxString CCrypto::GetMasterPassword() {
	// return wxString("tralala", wxConvUTF8);// @TODO remove that
	return masterPassword;
}

bool CCrypto::IsPassword(wxString passwd) {
	LOG("Entering IsPassword");
	wxString backup = GetMasterPassword();
	SetMasterPassword(passwd);
	wxString decrypt = wxString(Decrypt(COptions::Get()->GetOption(OPTION_MASTER_PASSWORD)).c_str(), wxConvUTF8);
	if (decrypt != passwd)
	{
		SetMasterPassword(backup);
		LOG("Exiting IsPassword (false)");
		return false;
	}
	LOG("Exiting IsPassword (true)");
	return true;
}

string CCrypto::Decrypt(wxString m_pass) {
	LOG("Pouet1");
	
	using namespace std;
	using namespace CryptoPP;
	
	LOG("Pouet2");
	
	string ciphertext = string(m_pass.mb_str());
	
	LOG("ciphertext :");
	LOG(ciphertext)
	
	LOG("Pouet3");
	
	string password = string(GetMasterPassword().mb_str());
	
	LOG("Pouet4. Master password=" << password);
	
	int iterations = COptions::Get()->GetOptionVal(OPTION_ENCRYPT_ITERATIONS);
	
	LOG("Pouet5");
	
	iterations = (iterations > 0) ? iterations : 1;
	
	LOG("Pouet5.5");
	
	SecByteBlock recoveredsalt(AES::DEFAULT_KEYLENGTH);
	
	LOG("Pouet6");
	
	StringSource saltDecoder(HEXSALT,true,new HexDecoder(new ArraySink(recoveredsalt, recoveredsalt.size())));
	
	LOG("Pouet7");
	
	SecByteBlock recoverediv(AES::BLOCKSIZE);
	
	LOG("Pouet8");
	
	StringSource ivDecoder(HEXIV,true,new HexDecoder(new ArraySink(recoverediv, recoverediv.size())));
	
	LOG("Pouet9");
	
	SecByteBlock recoveredkey(AES::DEFAULT_KEYLENGTH);

	LOG("Pouet10");
	
	PKCS5_PBKDF2_HMAC<SHA256> pbkdf;

	
	LOG("Pouet11");
	
	pbkdf.DeriveKey(recoveredkey, recoveredkey.size(), 0x00, (byte *) password.data(), password.size(),
		recoveredsalt, recoveredsalt.size(), iterations);
	
	
	LOG("Pouet12");
	
	CBC_Mode<AES>::Decryption aesdecryption(recoveredkey, recoveredkey.size(), recoverediv);
	
	
	LOG("Pouet13");
	
	string recoveredtext;
	
	LOG("Pouet14");
	
	try {
		StringSource decryptor(ciphertext, true, new HexDecoder(
			new StreamTransformationFilter(aesdecryption, new StringSink(recoveredtext))
			));
	} catch(Exception e) {
		LOG(e.what());
		recoveredtext = "";
	}
	LOG("Pouet15: Recovered text=");
	LOG(recoveredtext);
	
	return recoveredtext;
}

string CCrypto::Encrypt(wxString pass) {
	
	LOG("Tralala1");
	
	using namespace std;
	
	LOG("Tralala2");
	using namespace CryptoPP;
	
	LOG("Tralala3");
	string password = string(GetMasterPassword().mb_str());
	
	LOG("Tralala4. Master password=" << password);
	string message = string(pass.mb_str());
	
	LOG("Tralala5. Message=" << message);
	
	int iterations = COptions::Get()->GetOptionVal(OPTION_ENCRYPT_ITERATIONS);
	
	LOG("Tralala6");
	iterations = (iterations > 0) ? iterations : 1;
	
	
	LOG("Tralala7");
	SecByteBlock recoveredsalt(AES::DEFAULT_KEYLENGTH);
	
	LOG("Tralala8");
	StringSource saltDecoder(HEXSALT,true,new HexDecoder(new ArraySink(recoveredsalt, recoveredsalt.size())));
	
	LOG("Tralala9");
	SecByteBlock recoverediv(AES::BLOCKSIZE);
	
	LOG("Tralala10");
	StringSource ivDecoder(HEXIV,true,new HexDecoder(new ArraySink(recoverediv, recoverediv.size())));
	
	LOG("Tralala11");
	
	SecByteBlock derivedkey(AES::DEFAULT_KEYLENGTH);

	LOG("Tralala12");
	
	PKCS5_PBKDF2_HMAC<SHA256> pbkdf;
	
	LOG("Tralala13");
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

	LOG("Tralala15");
	

	string ciphertext;

	
	LOG("Tralala16");
	
	CBC_Mode<AES>::Encryption aesencryption(derivedkey,derivedkey.size(), recoverediv);
	// encrypt message using key derived above, storing the hex encoded result into ciphertext
	
	LOG("Tralala17");
	try {
		StringSource encryptor(message,true,
			new StreamTransformationFilter(aesencryption, new HexEncoder( new StringSink(ciphertext)))
			);
	} catch(Exception e) {
		LOG(e.what());
		ciphertext = "";
	}

	LOG("Tralala17.5");
	
	return ciphertext;
}

void CCrypto::SetMasterPassword(wxString pass) {
	masterPassword = pass;
	LOG("Setting masterPassword=")
	LOG(pass.mb_str())
}

string DecryptFromFormerThenEncryptWithNewMasterPassword(wxString m_pass) {
	return ""; // @TODO Implement that
}