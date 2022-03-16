#include "Header.h"


wxBEGIN_EVENT_TABLE(mFrame, wxFrame)
EVT_BUTTON(9001, OnReset)
EVT_BUTTON(9002, OnSetURLB)
wxEND_EVENT_TABLE()


void mFrame::OnExit(wxCommandEvent& event)
{
	Close(true);
}
void mFrame::OnAbout(wxCommandEvent& event)
{
	wxMessageBox("Program to download and parse data from Dividend.com",
		"About Dividend Calculator", wxOK | wxICON_INFORMATION);
}
void mFrame::OnSettings(wxCommandEvent& event)
{
	wxLogMessage("Settings doesn't exist yet");
}
void mFrame::OnReset(wxCommandEvent& evt) {


	datalist->Clear();
	evt.Skip();
}
void mFrame::OnSetURLB(wxCommandEvent& evt) {
	datalist->AppendString(text->GetValue());
	text->Clear();
	evt.Skip();
}

mFrame::mFrame() : wxFrame(NULL, wxID_ANY, "Hello World", wxPoint(30, 30), wxSize(400, 600)) {
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(ID_SETTINGS, "&Settings\tCtrl-H", "Help string");
	menuFile->AppendSeparator();
	menuFile->Append(wxID_EXIT);
	wxMenu* menHelp = new wxMenu;
	menHelp->Append(wxID_ABOUT);
	wxMenuBar* menuBar = new wxMenuBar;
	menuBar->Append(menuFile, "&Functions");
	menuBar->Append(menHelp, "&Help");

	SetMenuBar(menuBar);

	text = new wxTextCtrl(this, wxID_ANY, "", wxPoint(1, 2), wxSize(350, 20));

	wxButton* reset = new wxButton(this, 9001, "Reset", wxPoint(2, 508), wxSize(40, 30));
	wxButton* setUrl = new wxButton(this, 9002, "Set URL", wxPoint(2, 28), wxSize(50, 30));

	//Get all these aligned correctly
	wxStaticText* averagepayout = new wxStaticText(this, wxID_ANY, "0.2");
	wxStaticText* freq = new wxStaticText(this, wxID_ANY, "Monthly");
	wxStaticText* pricerecov = new wxStaticText(this, wxID_ANY, "5.1");
	wxStaticText* avgyield = new wxStaticText(this, wxID_ANY, "4.5%");
	wxStaticText* yieldanddiv = new wxStaticText(this, wxID_ANY, "9.4%");
	wxStaticText* price = new wxStaticText(this, wxID_ANY, "$125.89");
	wxStaticText* mktcap = new wxStaticText(this, wxID_ANY, "345MIL");
	wxStaticText* growth = new wxStaticText(this, wxID_ANY, "-20.89%");


	datalist = new wxListBox(this, wxID_ANY, wxPoint(2, 60), wxSize(200, 300));




	Bind(wxEVT_MENU, &mFrame::OnSettings, this, ID_SETTINGS);
	Bind(wxEVT_MENU, &mFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &mFrame::OnExit, this, wxID_EXIT);
}