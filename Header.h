#pragma once
#define CURL_STATICLIB
#include <wx/wx.h>
#include <curl/curl.h>
#include <fstream>

enum { ID_HELLO = 1, ID_SETTINGS};

extern CURL* curl;
extern std::string out;
extern wxListBox* datalist;
extern float pricing;
extern float growth;
extern float avgpayout;
extern float pricerecovery;
extern float averageyield;
extern float yieldanddividend;
extern std::string freqi;
extern std::string mktcap;
extern std::fstream file;

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
public:
	void OnReset(wxCommandEvent& evt);
	void OnSetURLB(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};
