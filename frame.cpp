#include "Header.h"

wxBEGIN_EVENT_TABLE(mFrame, wxFrame)
EVT_BUTTON(9001, OnReset)
EVT_BUTTON(9002, OnSetURLB)
wxEND_EVENT_TABLE()

void findPrice(std::string file) {
	std::ifstream f;
	f.open(file);
	std::string line;
	std::string ret;
	while (getline(f, line)) {
		if (line.find("t-text-black t-text-sm t-font-normal t-text-left t-leading-normal") != std::string::npos) {
			for (int i = 0; i < line.size(); i++) {
				if (line[i] == '>') {
						for (int j = line[i + 1]; j < line.size(); j++) {
							if (std::isdigit(line[j]) || line[j] == '.' || line[j] == '$') {
								ret.push_back(line[j]);
							}
							else if (line[j] == '<') {
								pricing = ret;
								f.close();
								return;
							}
						}
				}
			}
		}
	}

	f.close();
}
void findMktCap(std::string file) {
	std::ifstream f;
	f.open(file);
	std::string line;
	std::string ret;
	int count = 0;
	while (getline(f, line)) {
		if (line.find("t-text-black t-text-sm t-font-normal t-text-left t-leading-normal") != std::string::npos) {
			count++;
			if (count == 2) {
				for (int i = 0; i < line.size(); i++) {
					if (line[i] == '>') {
						if (line[i + 1] == '$') {
							for (int j = i + 1; j < line.size(); j++) {
								if (line[j] != '<') {
									ret.push_back(line[j]);
								}else {
									mktcap = ret;
									f.close();
									return;
								}
							}
						}
					}
				}
			}
		}
	}

	f.close();
}
void findYieldandDiv(std::string file) {
	std::ifstream f;
	f.open(file);
	std::string line;
	std::string ret;
	int count = 0;
	while (getline(f, line)) {
		if (line.find("t-text-black t-text-sm t-font-normal t-text-left t-leading-normal") != std::string::npos) {
			count++;
			if (count == 3) {
				for (int i = 0; i < line.size(); i++) {
					if (line[i] == '>') {
							for (int j = i + 1; j < line.size(); j++) {
								if (line[j] != '<') {
									ret.push_back(line[j]);
								}
								else {
									yieldanddividend = ret;
									f.close();
									return;
								}
						}
					}
				}
			}
		}
	}

	f.close();

}
void findFreq(std::string file) {
	std::ifstream f;
	f.open(file);
	std::string line;
	std::string ret;
	while (getline(f, line)) {
		if (line.find("t-leading-snug t-font-semibold t-capitalize") != std::string::npos) {
				for (int i = 0; i < line.size(); i++) {
					if (line[i] == '>') {
						for (int j = i + 1; j < line.size(); j++) {
							if (line[j] != '<') {
								ret.push_back(line[j]);
							}
							else {
								freqi = ret;
								f.close();
								return;
							}
						}
					}
			}
		}
	}

	f.close();
}
void findPriceRecov(std::string file) {
	std::ifstream f;
	f.open(file);
	std::string line;
	std::string ret;
	while (getline(f, line)) {
		if (line.find("t-leading-snug t-font-semibold") != std::string::npos) {
			for (int i = 0; i < line.size(); i++) {
				if (line[i] == '>') {
					for (int j = i + 1; j < line.size(); j++) {
						if (line[j] != '<') {
							ret.push_back(line[j]);
						}
						else {
							pricerecovery = ret;
							f.close();
							return;
						}
					}
				}
			}
		}
	}

	f.close();
}
void findAvgYield(std::string file) {
	std::ifstream f;
	f.open(file);
	std::string line;
	std::string ret;
	int count = 0;
	while (getline(f, line)) {
		if (line.find("t-leading-snug t-font-semibold") != std::string::npos) {
			count++;
			if (count == 5) {
				for (int i = 0; i < line.size(); i++) {
					if (line[i] == '>') {
						for (int j = i + 1; j < line.size(); j++) {
							if (line[j] != '<') {
								ret.push_back(line[j]);
							}
							else {
								averageyield = ret;
								f.close();
								return;
							}
						}
					}
				}
			}
		}
	}

	f.close();

}



void findGrowths(std::string file) {
	std::ifstream f;
	f.open(file);
	std::string line;
	std::string ret;
	int count = 0;
	bool grabnextline = false;
	while (getline(f, line)) {
		if (grabnextline) {
			for (int i = 0; i < line.size(); i++) {
				ret.push_back(line[i]);
			}	
			growth[count - 2] = ret;
			ret.clear();
			grabnextline = false;
		}

		if (line.find("t-my-4") != std::string::npos) {
			count++;
			if (count == 2 || count == 3 || count == 4 || count == 5 || count == 6) {
				grabnextline = true;
			}
			else if(count == 7){
				f.close();
				return;
			}
		}
	}
	f.close();
}
void findSymbol(std::string file) {
	std::ifstream f;
	f.open(file);
	std::string line;
	std::string ret;
	bool savenextline = false;
	while (getline(f, line)) {
		if (savenextline) {
			for (int i = 0; i < line.size(); i++) {
				if (line[i] != '\n') {
					ret.push_back(line[i]);
				}
			}
			symbol = ret;
			ret.clear();
			f.close();
			return;
		}
		if (line.find("t-flex t-h-full t-items-center t-font-semibold t-text-2xl md:t-text-lg t-uppercase t-leading-tighter") != std::string::npos) {
			savenextline = true;
		}
	}

	f.close();

}


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
void mFrame::OnDrip(wxCommandEvent& evt) {
	
	evt.Skip();
}
size_t got_data(char *buf, size_t itemsize, size_t nitems, void* ignore) {
	size_t bytes = itemsize * nitems;
	for (int i = 0; i < bytes; i++) {
		out.push_back(buf[i]);
		if (buf[i] == '\n') {
			file << out;
			out.clear();
		}
	}
	return bytes;
}
size_t get_json_data(char* buf, size_t itemsize, size_t nitems, void* ignore) {
	size_t bytes = itemsize * nitems;
	for (int i = 0; i < bytes; i++) {
		file << buf[i];
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

	text->Clear();
	evt.Skip();
	file.close();
	findPrice("temp.txt");
	findMktCap("temp.txt");
	findYieldandDiv("temp.txt");
	findFreq("temp.txt");
	findPriceRecov("temp.txt");
	findAvgYield("temp.txt");
	findGrowths("temp.txt");
	findSymbol("temp.txt");

	std::string tem1 = "Price:" + pricing;
	wxString temp1(tem1);
	price->SetLabelText(temp1);
	std::string tem2 = "Market Cap:" + mktcap;
	wxString temp2(tem2);
	marketcap->SetLabelText(temp2);
	std::string tem3 = "Yield and Dividend:" + yieldanddividend;
	wxString temp3(tem3);
	yieldanddiv->SetLabelText(temp3);
	std::string tem4 = "Frequency:" + freqi;
	wxString temp4(tem4);
	freq->SetLabelText(temp4);
	std::string tem5 = "Price Recovery Days:" + pricerecovery;
	wxString temp5(tem5);
	pricerecov->SetLabelText(temp5);
	std::string tem6 = "Average Yield:" + averageyield;
	wxString temp6(tem6);
	avgyield->SetLabelText(temp6);
	std::string tem7 = "Growth 1 Year: " + growth[0];
	wxString temp7(tem7);
	growth1year->SetLabelText(temp7);
	std::string tem8 = "Growth 3 Year: " + growth[1];
	wxString temp8(tem8);
	growth3year->SetLabelText(temp8);
	std::string tem9 = "Growth 5 Year: " + growth[2];
	wxString temp9(tem9);
	growth5year->SetLabelText(temp9);
	std::string tem10 = "Growth 10 Year: " + growth[3];
	wxString temp10(tem10);
	growth10year->SetLabelText(temp10);
	std::string tem11 = "Growth 20 Year: " + growth[4];
	wxString temp11(tem11);
	growth20year->SetLabelText(temp11);
	std::string tem12 = "Symbol: " + symbol;
	wxString temp12(tem12);
	symbolout->SetLabelText(temp12);

	//Write code for finding average payout here
	curl_easy_reset(curl);
	file.open("payout.txt");
	//Do a get request to dividend.com api(inspect packet when you click show all payment history). Will returna .json file it seems, write that to a file and figure out how to extract data I need
	//Need to get symbol of current asset and use that to get the API address
	//https://niranjanmalviya.wordpress.com/2018/06/23/get-json-data-using-curl/
	//use above link as starting point in engineering header for dividend.com
	//Add someway to log everything going on with this so debugging is easier
	std::string symurl = "https://www.dividend.com/api/u/TPDIMTPDS/?symbol=" + symbol;
	curl_slist *header = NULL;
	header = curl_slist_append(header, "accept:application/json,text/plain,*/*");
	header = curl_slist_append(header, "accept-encoding:gzip, deflate, br");
	header = curl_slist_append(header, "accept-language:en-US,en;q=0.9");
	header = curl_slist_append(header, "content-type:application/json;charset=utf-8");
	header = curl_slist_append(header, "cookie:mid=mid44a0b46924a800697a0ff3c351d09e94; exit_interstitial_without_ad=true");
	header = curl_slist_append(header, "dnt:1");
	header = curl_slist_append(header, "if-none-match:W/\"d7d25d30097cad9846896d2b40c0b98f\"");
	std::string ref = "referer:" + temp;
	header = curl_slist_append(header, ref.c_str());

	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
	curl_easy_setopt(curl, CURLOPT_URL, symurl);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, get_json_data);
	curl_easy_perform(curl);

	curl_slist_free_all(header);
	file.close();
}

mFrame::mFrame() : wxFrame(NULL, wxID_ANY, "Dividend Calculator", wxPoint(30, 30), wxSize(400, 600)) {
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(ID_SETTINGS, "&Settings\tCtrl-H", "The settings");
	menuFile->AppendSeparator();
	menuFile->Append(ID_DRIP, "&DRIP", "Calculate DRIP");
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

	symbolout = new wxStaticText(this, wxID_ANY, "N/A", wxPoint(70, 28), wxSize(75, 30));

	wxStaticText* averagepayout = new wxStaticText(this, wxID_ANY, "Average Payout: 0.2", wxPoint(204, 30), wxSize(70, 30));
	freq = new wxStaticText(this, wxID_ANY, "Frequency: Monthly", wxPoint(204, 70), wxSize(70, 30));
	pricerecov = new wxStaticText(this, wxID_ANY, "Days to Price Recovery: 5.1", wxPoint(204, 100), wxSize(100, 30));
	avgyield = new wxStaticText(this, wxID_ANY, "Average Yield: 4.5%", wxPoint(204, 130), wxSize(100, 30));
	yieldanddiv = new wxStaticText(this, wxID_ANY, "Yield and Dividend: 9.4%", wxPoint(204, 160), wxSize(100, 30));
	price = new wxStaticText(this, wxID_ANY, "Price: $125.89", wxPoint(204, 190), wxSize(100, 30));
	marketcap = new wxStaticText(this, wxID_ANY, "Market Cap: 345MIL", wxPoint(204, 220), wxSize(100, 30));
	wxStaticText* divgrowth = new wxStaticText(this, wxID_ANY, "Dividend Growth", wxPoint(204, 250), wxSize(100, 30));
	growth1year = new wxStaticText(this, wxID_ANY, "Growth 1 Year: -20.89%", wxPoint(204, 280), wxSize(100, 30));
	growth3year = new wxStaticText(this, wxID_ANY, "Growth 3 Year: -20.89%", wxPoint(204, 310), wxSize(100, 30));
	growth5year = new wxStaticText(this, wxID_ANY, "Growth 5 Year: -20.89%", wxPoint(204, 340), wxSize(100, 30));
	growth10year = new wxStaticText(this, wxID_ANY, "Growth 10 Year: -20.89%", wxPoint(204, 370), wxSize(100, 30));
	growth20year = new wxStaticText(this, wxID_ANY, "Growth 20 Year: -20.89%", wxPoint(204, 400), wxSize(100, 30));

	//Datalist for payout info
	datalist = new wxListBox(this, wxID_ANY, wxPoint(2, 60), wxSize(200, 300));




	Bind(wxEVT_MENU, &mFrame::OnSettings, this, ID_SETTINGS);
	Bind(wxEVT_MENU, &mFrame::OnDrip, this, ID_DRIP);
	Bind(wxEVT_MENU, &mFrame::OnAbout, this, wxID_ABOUT);
	Bind(wxEVT_MENU, &mFrame::OnExit, this, wxID_EXIT);
}