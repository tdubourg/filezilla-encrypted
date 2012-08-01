#ifndef __CRYPTO_H__
#define __CRYPTO_H__

#include "string"

class CCrypto
{
public:
	static std::string Decrypt(wxString m_pass);
	static std::string Encrypt(wxString m_pass);
	static wxString GetMasterPassword();
	static void SetMasterPassword(wxString pass);
	static std::string DecryptFromFormerThenEncryptWithNewMasterPassword(wxString m_pass);
	
	static const std::string HEXSALT;
	static const std::string HEXIV;
protected:
	static wxString masterPassword;
};


#endif //__CRYPTO_H__
