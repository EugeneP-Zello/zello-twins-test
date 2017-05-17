// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once
#import "libid:{5069366D-44C6-4D86-946A-8CDF8E5552EC}" raw_interfaces_only, raw_native_types, named_guids, auto_search, no_auto_exclude, no_implementation


class CMainDlg : public CDialogImpl<CMainDlg>,
	public ATL::IDispEventImpl<1,CMainDlg,&ZelloPTTLib::DIID_IZelloClientEvents,&ZelloPTTLib::LIBID_ZelloPTTLib, 1, 0>,
	public ATL::IDispEventImpl<2,CMainDlg,&ZelloPTTLib::DIID_IZelloClientEvents,&ZelloPTTLib::LIBID_ZelloPTTLib, 1, 0>
{
	typedef ATL::IDispEventImpl<1,CMainDlg,&ZelloPTTLib::DIID_IZelloClientEvents,&ZelloPTTLib::LIBID_ZelloPTTLib, 1, 0> TDisp1;
	typedef ATL::IDispEventImpl<2,CMainDlg,&ZelloPTTLib::DIID_IZelloClientEvents,&ZelloPTTLib::LIBID_ZelloPTTLib, 1, 0> TDisp2;
public:
	enum { IDD = IDD_MAINDLG };
	WTL::CListBox						m_lb;
	WTL::CButton						m_ok;
	CComPtr<ZelloPTTLib::IZelloClient>	m_spClient1;
	CComPtr<ZelloPTTLib::IZelloClient>	m_spClient2;
	bool								m_bSignedIn1,m_bSignedIn2;
	BEGIN_MSG_MAP(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		COMMAND_ID_HANDLER(ID_APP_ABOUT, OnAppAbout)
		COMMAND_ID_HANDLER(IDOK, OnOK)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
	END_MSG_MAP()

// Handler prototypes (uncomment arguments if needed):
//	LRESULT MessageHandler(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
//	LRESULT CommandHandler(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
//	LRESULT NotifyHandler(int /*idCtrl*/, LPNMHDR /*pnmh*/, BOOL& /*bHandled*/)

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);
	LRESULT OnAppAbout(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnOK(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

	BEGIN_SINK_MAP(CMainDlg)
		SINK_ENTRY_EX(1, ZelloPTTLib::DIID_IZelloClientEvents, ZelloPTTLib::DISPID_ON_SIGN_IN_STARTED, &CMainDlg::OnSignInStarted)
		SINK_ENTRY_EX(1, ZelloPTTLib::DIID_IZelloClientEvents, ZelloPTTLib::DISPID_ON_SIGN_IN_SUCCEEDED, &CMainDlg::OnSignInSucceeded)
		SINK_ENTRY_EX(1, ZelloPTTLib::DIID_IZelloClientEvents, ZelloPTTLib::DISPID_ON_SIGN_IN_FAILED, &CMainDlg::OnSignInFailed)
	    SINK_ENTRY_EX(1, ZelloPTTLib::DIID_IZelloClientEvents, ZelloPTTLib::DISPID_ON_SIGN_OUT_STARTED, &CMainDlg::OnSignOutStarted)
		SINK_ENTRY_EX(1, ZelloPTTLib::DIID_IZelloClientEvents, ZelloPTTLib::DISPID_ON_SIGN_OUT_COMPLETE, &CMainDlg::OnSignOutFinished)
    	SINK_ENTRY_EX(2, ZelloPTTLib::DIID_IZelloClientEvents, ZelloPTTLib::DISPID_ON_SIGN_IN_STARTED, &CMainDlg::OnSignInStarted2)
		SINK_ENTRY_EX(2, ZelloPTTLib::DIID_IZelloClientEvents, ZelloPTTLib::DISPID_ON_SIGN_IN_SUCCEEDED, &CMainDlg::OnSignInSucceeded2)
		SINK_ENTRY_EX(2, ZelloPTTLib::DIID_IZelloClientEvents, ZelloPTTLib::DISPID_ON_SIGN_IN_FAILED, &CMainDlg::OnSignInFailed2)
	    SINK_ENTRY_EX(2, ZelloPTTLib::DIID_IZelloClientEvents, ZelloPTTLib::DISPID_ON_SIGN_OUT_STARTED, &CMainDlg::OnSignOutStarted2)
		SINK_ENTRY_EX(2, ZelloPTTLib::DIID_IZelloClientEvents, ZelloPTTLib::DISPID_ON_SIGN_OUT_COMPLETE, &CMainDlg::OnSignOutFinished2)
	END_SINK_MAP()

	void ZelloSetup(CComPtr<ZelloPTTLib::IZelloClient> spClient);

	void __stdcall OnSignInStarted();
	void __stdcall OnSignInSucceeded();
	void __stdcall OnSignInFailed(ZelloPTTLib::CLIENT_ERROR ErrorCode);
	void __stdcall OnSignOutStarted();
	void __stdcall OnSignOutFinished();

	void __stdcall OnSignInStarted2();
	void __stdcall OnSignInSucceeded2();
	void __stdcall OnSignInFailed2(ZelloPTTLib::CLIENT_ERROR ErrorCode);
	void __stdcall OnSignOutStarted2();
	void __stdcall OnSignOutFinished2();

};
