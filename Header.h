#pragma once
#define CURL_STATICLIB
#include <wx/wx.h>


enum { ID_HELLO = 1, ID_SETTINGS};


class cApp : public wxApp {
public:
	cApp();
	~cApp();
	virtual bool OnInit();
};

class mFrame : public wxFrame {
public:
	mFrame();
private:
	void OnSettings(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	wxTextCtrl* text;
	wxListBox* datalist;
public:
	void OnReset(wxCommandEvent& evt);
	void OnSetURLB(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};
