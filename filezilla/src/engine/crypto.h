#ifndef __CRYPTO_H__
#define __CRYPTO_H__

class CCrypto
{
public:
	CCrypto(arguments);
	static string Decrypt(wxString m_pass);
	static string Encrypt(wxString m_pass);
	static void SetMasterPassword(wxString pass);
	static string DecryptFromFormerThenEncryptWithNewMasterPassword(wxString m_pass);
	~CCrypto();

protected:
	wxString masterPassword;
};


#endif //__CRYPTO_H__
