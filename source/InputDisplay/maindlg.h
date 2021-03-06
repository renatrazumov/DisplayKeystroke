// maindlg.h : Declaration of the Cmaindlg

#pragma once

#include "resource.h"       // main symbols

#include <atlhost.h>
#include <atlstr.h>
#include <atlfile.h>

using namespace ATL;


#include "websocket.h"
#include "hook.h"
#include "aboutdlg.h"
#include "approvedlg.h"

// Cmaindlg

class Cmaindlg : 
	public CAxDialogImpl<Cmaindlg>
{
protected:

	void init();
	void cleanup();
	void startServer();
	void stopServer();
	void loadConfigFile();
	void saveConfigFile();
	CString getValueFromString(CString& string, LPCWSTR find_str, LPCWSTR def_str);
	void replaceValueFromString(CString& string, LPCWSTR find_str, LPCWSTR replace_str);

	void sendKey(DWORD vkCode, bool toggle);
	void sendMouseCoord(POINT point);
	void addText(LPCTSTR text, ...);

	CWindow host_port_edit;
	CWindow client_ip_edit;
	CWindow richedit;

	Caboutdlg* about_dlg;
	Capprovedlg::ApproveDlgData* approve_dlg_data;
	std::list<WebSocket::Client*> requesting_clients;

	RECT screen;
	POINT last_mouse_pos;

#define MAX_TMP_STR	4096
	WCHAR tmp_str[MAX_TMP_STR];

#define WM_OPEN_APPROVEDLG			(WM_APP + 1)

public:

	static void wsCallback(WebSocket::CallbackMsg* msg);
	void approveConnection(bool accept);
	void openApproveDlg();
	void acceptConnection(WebSocket::Client* client);
	
	static void onKey(DWORD vkCode, bool toggle, void* pass_obj);
	static void onMouseMove(POINT point, void* pass_obj);

public:

	Cmaindlg() :
		about_dlg(NULL),
		approve_dlg_data(NULL)
	{
	}

	~Cmaindlg()
	{
	}

	enum { IDD = IDD_MAINDLG };

BEGIN_MSG_MAP(Cmaindlg)
	CHAIN_MSG_MAP(CAxDialogImpl<Cmaindlg>)
	MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
	MESSAGE_HANDLER(WM_CLOSE, OnClose)
	COMMAND_HANDLER(IDABOUT, BN_CLICKED, OnClickedAbout)
	COMMAND_HANDLER(IDC_BUTTON_START, BN_CLICKED, OnBnClickedButtonStart)
	COMMAND_HANDLER(IDC_CHECK_CLIENTIP, BN_CLICKED, OnBnClickedCheckClientIP)
END_MSG_MAP()

// Handler prototypes:
//  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
//  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
//  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

	LRESULT OnInitDialog(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	void OnFinalMessage(HWND hWnd);
	LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT OnClickedAbout(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBnClickedButtonStart(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	LRESULT OnBnClickedCheckClientIP(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL& bHandled);
	virtual DLGPROC GetDialogProc();
	static INT_PTR CALLBACK mainDlgProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};


