// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "resource.h"

#include "MainDlg.h"


LRESULT CMainDlg::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	// center the dialog on the screen
	CenterWindow();
	m_lb.Attach(GetDlgItem(IDC_LIST));
	m_ok.Attach(GetDlgItem(IDOK));
	HRESULT hr = m_spClient1.CoCreateInstance(ZelloPTTLib::CLSID_ZelloClient);
	hr = m_spClient2.CoCreateInstance(ZelloPTTLib::CLSID_ZelloClient);
	hr = TDisp1::DispEventAdvise(m_spClient1);
	hr = TDisp2::DispEventAdvise(m_spClient2);

	// set icons
	HICON hIcon = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON), LR_DEFAULTCOLOR);
	SetIcon(hIcon, TRUE);
	HICON hIconSmall = (HICON)::LoadImage(_Module.GetResourceInstance(), MAKEINTRESOURCE(IDR_MAINFRAME), 
		IMAGE_ICON, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON), LR_DEFAULTCOLOR);
	SetIcon(hIconSmall, FALSE);
	m_bSignedIn1 = m_bSignedIn2 = false;
	m_ok.SetWindowText(L"Sign in");
	ZelloSetup(m_spClient1);
	ZelloSetup(m_spClient2);
	return TRUE;
}

void CMainDlg::ZelloSetup(CComPtr<ZelloPTTLib::IZelloClient> spClient) {
	ZelloPTTLib::INetwork* pNet = NULL;
	if(SUCCEEDED(spClient->get_Network(&pNet))) {
		pNet->put_NetworkName(CComBSTR(L"default"));
		pNet->put_LoginServer(CComBSTR(L"default.loudtalks.net"));
		pNet->EnableTls(CComBSTR(L"tls.zellowork.com"));
		pNet->Release();
	}
}

LRESULT CMainDlg::OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CSimpleDialog<IDD_ABOUTBOX, FALSE> dlg;
	dlg.DoModal();
	return 0;
}

LRESULT CMainDlg::OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	HRESULT hr;

	if(false==m_bSignedIn1)
		hr = m_spClient1->SignIn(ATL::CComBSTR("test4"),ATL::CComBSTR("test"),VARIANT_FALSE);
	else
		hr = m_spClient1->SignOut();

	if(false == m_bSignedIn2)
		hr = m_spClient2->SignIn(ATL::CComBSTR("test5"),ATL::CComBSTR("test"),VARIANT_FALSE);
	else
		hr = m_spClient2->SignOut();

	m_ok.EnableWindow(FALSE);
	return 0;
}

LRESULT CMainDlg::OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	EndDialog(wID);
	TDisp1::DispEventUnadvise(m_spClient1);
	TDisp2::DispEventUnadvise(m_spClient2);
	m_spClient1.Release();
	m_spClient2.Release();
	return 0;
}

void __stdcall CMainDlg::OnSignInStarted()
{
	m_lb.AddString(L"1 - OnSignInStarted");
}

void __stdcall CMainDlg::OnSignInSucceeded()
{
	m_lb.AddString(L"1 - OnSignInSucceeded");
	m_ok.EnableWindow(TRUE);
	m_ok.SetWindowText(L"Sign out");
	m_bSignedIn1 = true;
}

void __stdcall CMainDlg::OnSignInFailed(ZelloPTTLib::CLIENT_ERROR ErrorCode)
{
	m_lb.AddString(L"1 - OnSignInFailed");
	m_ok.EnableWindow(TRUE);
	m_ok.SetWindowText(L"Sign in");
	m_bSignedIn1 = false;
}

void __stdcall CMainDlg::OnSignOutStarted()
{
	m_lb.AddString(L"1 - OnSignOutStarted");
}

void __stdcall CMainDlg::OnSignOutFinished()
{
	m_lb.AddString(L"1 - OnSignOutFinished");
	m_ok.EnableWindow(TRUE);
	m_ok.SetWindowText(L"Sign in");
	m_bSignedIn1 = false;
}

void __stdcall CMainDlg::OnSignInStarted2()
{
	m_lb.AddString(L"2 - OnSignInStarted");
}

void __stdcall CMainDlg::OnSignInSucceeded2()
{
	m_lb.AddString(L"2 - OnSignInSucceeded");
	m_ok.EnableWindow(TRUE);
	m_ok.SetWindowText(L"Sign out");
	m_bSignedIn2 = true;
}

void __stdcall CMainDlg::OnSignInFailed2(ZelloPTTLib::CLIENT_ERROR ErrorCode)
{
	m_lb.AddString(L"2 - OnSignInFailed");
	m_ok.EnableWindow(TRUE);
	m_ok.SetWindowText(L"Sign in");
	m_bSignedIn2 = false;
}

void __stdcall CMainDlg::OnSignOutStarted2()
{
	m_lb.AddString(L"2 - OnSignOutStarted");
}

void __stdcall CMainDlg::OnSignOutFinished2()
{
	m_lb.AddString(L"2 - OnSignOutFinished");
	m_ok.EnableWindow(TRUE);
	m_ok.SetWindowText(L"Sign in");
	m_bSignedIn2 = false;
}
