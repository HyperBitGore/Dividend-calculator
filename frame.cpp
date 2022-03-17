#include "Header.h"

wxBEGIN_EVENT_TABLE(mFrame, wxFrame)
EVT_BUTTON(9001, OnReset)
EVT_BUTTON(9002, OnSetURLB)
wxEND_EVENT_TABLE()


void mFrame::OnExit(wxCommandEvent& event)
{
	curl_easy_cleanup(curl);
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
	curl_easy_reset(curl);
	datalist->Clear();
	evt.Skip();
}
void findPrice(std::string file) {
	


}
//For payout history, gonna have to do some packet wizardy or something to get data
size_t got_data(char *buf, size_t itemsize, size_t nitems, void* ignore) {
	size_t bytes = itemsize * nitems;
	for (int i = 0; i < bytes; i++) {
		out.push_back(buf[i]);
		if (buf[i] == '\n') {
			file << out;
			datalist->AppendString(out);
			out.clear();
		}
	}
	return bytes;
}
//https://wiki.wxwidgets.org/Converting_everything_to_and_from_wxString
void mFrame::OnSetURLB(wxCommandEvent& evt) {
	wxString mstring(text->GetValue());
	std::string temp = std::string(mstring.mb_str());
	file.open("temp.txt");
	curl_easy_setopt(curl, CURLOPT_URL, temp.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, got_data);
	curl_easy_perform(curl);
	//Now just parse data using downloaded file, can probably cut out file in future and just use buffer

	text->Clear();
	evt.Skip();
	file.close();
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

	//Add code to concat values pulled from html, and add changing of text when new url parsed
	wxStaticText* averagepayout = new wxStaticText(this, wxID_ANY, "Average Payout: 0.2", wxPoint(202, 30), wxSize(70, 30));
	wxStaticText* freq = new wxStaticText(this, wxID_ANY, "Frequency: Monthly", wxPoint(282, 30), wxSize(70, 30));
	wxStaticText* pricerecov = new wxStaticText(this, wxID_ANY, "Days to Price Recovery: 5.1", wxPoint(204, 70), wxSize(100, 30));
	wxStaticText* avgyield = new wxStaticText(this, wxID_ANY, "Average Yield: 4.5%", wxPoint(284, 70), wxSize(100, 30));
	wxStaticText* yieldanddiv = new wxStaticText(this, wxID_ANY, "Yield and Dividend: 9.4%", wxPoint(204, 110), wxSize(100, 30));
	wxStaticText* price = new wxStaticText(this, wxID_ANY, "Price: $125.89", wxPoint(284, 110), wxSize(100, 30));
	wxStaticText* mktcap = new wxStaticText(this, wxID_ANY, "Market Cap: 345MIL", wxPoint(204, 150), wxSize(100, 30));
	wxStaticText* growth = new wxStaticText(this, wxID_ANY, "Growth: -20.89%", wxPoint(284, 150), wxSize(100, 30));


	datalist = new wxListBox(this, wxID_ANY, wxPoint(2, 60), wxSize(200, 300));




	Bind(wxEVT_MENU, &mFrame::OnSettings, this, ID_SETTINGS);
	Bind(wxEVT_MENU, &mFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &mFrame::OnExit, this, wxID_EXIT);
}