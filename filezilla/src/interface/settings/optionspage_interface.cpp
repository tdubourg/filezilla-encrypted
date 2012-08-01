#include <filezilla.h>
#include "../Options.h"
#include "settingsdialog.h"
#include "optionspage.h"
#include "optionspage_interface.h"
#include "../Mainfrm.h"
#include "../power_management.h"

// Start of @td
#define DEFAULTVALUE "***********"
#include "../engine/crypto.h"
// End of @td

BEGIN_EVENT_TABLE(COptionsPageInterface, COptionsPage)
EVT_CHECKBOX(XRCID("ID_FILEPANESWAP"), COptionsPageInterface::OnLayoutChange)
// Start of @td
EVT_CHECKBOX(XRCID("ID_ENCRYPT_PASSWORDS"), COptionsPageInterface::OnEncryptPasswordsChanged) 
// End of @td
EVT_CHOICE(XRCID("ID_FILEPANELAYOUT"), COptionsPageInterface::OnLayoutChange)
EVT_CHOICE(XRCID("ID_MESSAGELOGPOS"), COptionsPageInterface::OnLayoutChange)
END_EVENT_TABLE()

bool COptionsPageInterface::LoadPage()
{
	bool failure = false;

	SetCheckFromOption(XRCID("ID_FILEPANESWAP"), OPTION_FILEPANE_SWAP, failure);
	SetChoice(XRCID("ID_FILEPANELAYOUT"), m_pOptions->GetOptionVal(OPTION_FILEPANE_LAYOUT), failure);

	SetChoice(XRCID("ID_MESSAGELOGPOS"), m_pOptions->GetOptionVal(OPTION_MESSAGELOG_POSITION), failure);

#ifndef __WXMAC__
	SetCheckFromOption(XRCID("ID_MINIMIZE_TRAY"), OPTION_MINIMIZE_TRAY, failure);
#endif

	SetCheckFromOption(XRCID("ID_PREVENT_IDLESLEEP"), OPTION_PREVENT_IDLESLEEP, failure);
	
	SetCheckFromOption(XRCID("ID_SPEED_DISPLAY"), OPTION_SPEED_DISPLAY, failure);

	if (!CPowerManagement::IsSupported())
		XRCCTRL(*this, "ID_PREVENT_IDLESLEEP", wxCheckBox)->Hide();

	if (m_pOptions->OptionFromFzDefaultsXml(OPTION_DEFAULT_KIOSKMODE) || m_pOptions->GetOptionVal(OPTION_DEFAULT_KIOSKMODE) == 2)
	{
		XRCCTRL(*this, "ID_DONT_SAVE_PASSWORDS", wxCheckBox)->SetValue(true);
		XRCCTRL(*this, "ID_DONT_SAVE_PASSWORDS", wxCheckBox)->Disable();
	}
	else
		SetCheckFromOption(XRCID("ID_DONT_SAVE_PASSWORDS"), OPTION_DEFAULT_KIOSKMODE, failure);

	SetCheckFromOption(XRCID("ID_INTERFACE_SITEMANAGER_ON_STARTUP"), OPTION_INTERFACE_SITEMANAGER_ON_STARTUP, failure);
	
	// Start of @td
	SetCheckFromOption(XRCID("ID_ENCRYPT_PASSWORDS"), OPTION_ENCRYPT_PASSWORDS, failure);
	wxString stars = wxString(DEFAULTVALUE, wxConvUTF8);
	SetText(XRCID("ID_MASTER_PASSWORD"), stars, failure); // @TODO : Better display...
	// End of @td
	
	if (!failure)
	{
		SetCtrlState();
	}

	return !failure;
}

bool COptionsPageInterface::SavePage()
{
	SetOptionFromCheck(XRCID("ID_FILEPANESWAP"), OPTION_FILEPANE_SWAP);
	m_pOptions->SetOption(OPTION_FILEPANE_LAYOUT, GetChoice(XRCID("ID_FILEPANELAYOUT")));

	m_pOptions->SetOption(OPTION_MESSAGELOG_POSITION, GetChoice(XRCID("ID_MESSAGELOGPOS")));

#ifndef __WXMAC__
	SetOptionFromCheck(XRCID("ID_MINIMIZE_TRAY"), OPTION_MINIMIZE_TRAY);
#endif

	SetOptionFromCheck(XRCID("ID_PREVENT_IDLESLEEP"), OPTION_PREVENT_IDLESLEEP);
	
	SetOptionFromCheck(XRCID("ID_SPEED_DISPLAY"), OPTION_SPEED_DISPLAY);
	
	// Start of @td
	SetOptionFromCheck(XRCID("ID_ENCRYPT_PASSWORDS"), OPTION_ENCRYPT_PASSWORDS);
	wxString defaultval = wxString(DEFAULTVALUE, wxConvUTF8);
	if(GetText(XRCID("ID_MASTER_PASSWORD")) != defaultval)
	{
		wxString passwdUnEncrypted = GetText(XRCID("ID_MASTER_PASSWORD"));
		CCrypto::SetMasterPassword(passwdUnEncrypted);
		wxString passwdEncrypted = wxString(CCrypto::Encrypt(passwdUnEncrypted).c_str(), wxConvUTF8);
		m_pOptions->SetOption(OPTION_MASTER_PASSWORD, passwdEncrypted);
	}
	
	// End of @td

	if (!m_pOptions->OptionFromFzDefaultsXml(OPTION_DEFAULT_KIOSKMODE) && m_pOptions->GetOptionVal(OPTION_DEFAULT_KIOSKMODE) != 2)
		SetOptionFromCheck(XRCID("ID_DONT_SAVE_PASSWORDS"), OPTION_DEFAULT_KIOSKMODE);

	SetOptionFromCheck(XRCID("ID_INTERFACE_SITEMANAGER_ON_STARTUP"), OPTION_INTERFACE_SITEMANAGER_ON_STARTUP);

	return true;
}

bool COptionsPageInterface::Validate()
{
	return true;
}

void COptionsPageInterface::OnLayoutChange(wxCommandEvent& event)
{
	int layout = GetChoice(XRCID("ID_FILEPANELAYOUT"));
	int swap = GetCheck(XRCID("ID_FILEPANESWAP")) ? 1 : 0;

	m_pOwner->m_pMainFrame->UpdateLayout(layout, swap, GetChoice(XRCID("ID_MESSAGELOGPOS")));
}

// Start of @td

void COptionsPageInterface::SetCtrlState()
{
	bool enabled = XRCCTRL(*this, "ID_ENCRYPT_PASSWORDS", wxCheckBox)->GetValue() == 1;

	XRCCTRL(*this, "ID_MASTER_PASSWORD", wxTextCtrl)->Enable(enabled);
}

void COptionsPageInterface::OnEncryptPasswordsChanged(wxCommandEvent& event)
{
	SetCtrlState();
}

// End of @td