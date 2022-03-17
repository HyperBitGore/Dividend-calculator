#pragma once
#define CURL_STATICLIB
#include <wx/wx.h>
#include <curl/curl.h>
#include <fstream>

enum { ID_HELLO = 1, ID_SETTINGS};

extern CURL* curl;
extern std::string out;
extern wxListBox* datalist;
extern std::string pricing;
extern std::string growth[5];
extern float avgpayout;
extern std::string pricerecovery;
extern std::string averageyield;
extern std::string yieldanddividend;
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
	wxStaticText* price;
	wxStaticText* marketcap;
	wxStaticText* yieldanddiv;
	wxStaticText* freq;
	wxStaticText* pricerecov;
	wxStaticText* avgyield;
	wxStaticText* growth1year;
	wxStaticText* growth3year;
	wxStaticText* growth5year;
	wxStaticText* growth10year;
	wxStaticText* growth20year;
public:
	void OnReset(wxCommandEvent& evt);
	void OnSetURLB(wxCommandEvent& evt);

	wxDECLARE_EVENT_TABLE();
};

class DRIP {
private:
	int shares;

public:
	void calculateYear();

};

