#ifndef __CRYPTO_H__
#define __CRYPTO_H__

#include "string"

// TODO : Really delete that from the header:
#define TD_DBG 1

#ifdef TD_DBG
#include <iostream>
#include <fstream>
extern std::ofstream F_LOG;
#define LOG(a) F_LOG << a << std::endl;
#else
#define LOG(a)  
#endif


class CCrypto
{
public:
	static std::string Decrypt(wxString m_pass);
	static std::string Encrypt(wxString m_pass);
	static wxString GetMasterPassword();
	static void SetMasterPassword(wxString pass);
	static std::string DecryptFromFormerThenEncryptWithNewMasterPassword(wxString m_pass);
	static bool IsPassword(wxString passwd);
	
	static const std::string HEXSALT;
	static const std::string HEXIV;
protected:
	static wxString masterPassword;//# UNENCRYPTED PASSWORD, used for encrypting and decrypting
};


#endif //__CRYPTO_H__
