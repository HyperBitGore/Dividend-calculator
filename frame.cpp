#include "Header.h"

wxBEGIN_EVENT_TABLE(mFrame, wxFrame)
EVT_BUTTON(9001, OnReset)
EVT_BUTTON(9002, OnSetURLB)
wxEND_EVENT_TABLE()

std::fstream ff;

size_t getStringOccurences(std::string base, std::string cmp) {
	size_t occ = 0;
	std::string::size_type pos = 0;
	while ((pos = base.find(cmp, pos)) != std::string::npos) {
		occ++;
		pos += cmp.length();
	}
	return occ;
}


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
void findPays(std::string file) {
	std::ifstream f;
	f.open(file);
	std::string line;
	std::string ret;
	std::string prev = "PEEPEEPOOPPOO";


	while (getline(f, line)) {
		size_t found = line.find("Pay Date");
		if (line.find(prev) == std::string::npos) {
			if (found != std::string::npos) {
				if (getStringOccurences(line, "null") <= 1) {
					size_t start = found;
					pay pet;
					for (int i = found; i < line.size(); i++) {
						if (std::isdigit(line[i])) {
							start = i;
							i = line.size();
						}
					}
					for (int i = start; i < line.size(); i++) {
						if (line[i] != '}' && line[i] != '\"') {
							ret.push_back(line[i]);
						}
						else {
							pet.paydate = ret;
							prev = ret;
							ret.clear();
							i = line.size();
						}
					}
					size_t outfind = line.find("DPS");
					for (int i = outfind; i < line.size(); i++) {
						if (line[i] == '$') {
							start = i + 1;
							i = line.size();
						}
					}
					for (int i = start; i < line.size(); i++) {
						if (std::isdigit(line[i]) || line[i] == '.') {
							ret.push_back(line[i]);
						}
						else {
							pet.payout = std::stof(ret);
							ret.clear();
							i = line.size();
						}
					}
					pays.push_back(pet);
				}
			}
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
		ff << buf[i];
		if (buf[i] == '}' && buf[i + 1] == ',') {
			ff << '\n';
		}
	}
	return bytes;
}

std::string getFullname(std::string url) {
	size_t found = 0;
	std::string t;
	size_t count = 0;
	for (int i = 0; i < url.size(); i++) {
		if (url[i] == '/') {
			count++;
		}
		if (count == 7) {
			found = i + 1;
			i = url.size();
		}
	}
	if (count < 7) {
		return "NULL";
	}
	for (int i = found; i < url.size(); i++) {
		t.push_back(url[i]);
	}
	return t;
}


//https://wiki.wxwidgets.org/Converting_everything_to_and_from_wxString
void mFrame::OnSetURLB(wxCommandEvent& evt) {
	wxString mstring(text->GetValue());
	std::string temp = std::string(mstring.mb_str());
	file.open("temp.txt");
	curl_easy_setopt(curl, CURLOPT_URL, temp.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, got_data);
	curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1L);
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
	std::fstream fl;
	//Maybe just create a new curl handle for each call of this and each request
	curl_easy_reset(curl);
	ff.open("payout.txt");
	std::string symurl = "https://www.dividend.com/api/dividend/stocks/quote_chart/" + getFullname(temp);
	curl_slist *header = NULL;
	header = curl_slist_append(header, "authority:www.dividend.com");
	header = curl_slist_append(header, "sec-ch-ua:\"Chromium\"; v = \"2021\", \";Not A Brand\"; v = \"99\"");
	header = curl_slist_append(header, "accept:application/json,text/plain,*/*");
	header = curl_slist_append(header, "accept-encoding:identity");
	header = curl_slist_append(header, "content-type:application/json;charset=utf-8");
	header = curl_slist_append(header, "dnt:1");
	header = curl_slist_append(header, "sec-ch-ua-platform:\"Android\"");
	header = curl_slist_append(header, "sec-fetch-dest:empty");
	header = curl_slist_append(header, "sec-fetch-mode:cors");
	header = curl_slist_append(header, "sec-fetch-site:same-origin");
	header = curl_slist_append(header, "accept-language:en-US,en;q=0.9");
	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, header);
	curl_easy_setopt(curl, CURLOPT_URL, symurl.c_str());
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, get_json_data);
	curl_easy_setopt(curl, CURLOPT_FORBID_REUSE, 1L);
	curl_easy_perform(curl);
	
	curl_slist_free_all(header);
	ff.close();
	curl_easy_reset(curl);
	pays.clear();
	findPays("payout.txt");
	float avgp = 0;
	datalist->Clear();
	for (auto& i : pays) {
		avgp += i.payout;
		std::string ten = i.paydate + ":$" + std::to_string(i.payout);
		wxString lt(ten);
		datalist->AppendString(lt);
	}
	avgp = avgp / pays.size();
	std::string tem13 = "Average Payout: " + std::to_string(avgp);
	wxString temp13(tem13);
	averagepayout->SetLabelText(temp13);

}

mFrame::mFrame() : wxFrame(NULL, wxID_ANY, "Dividend Calculator", wxPoint(30, 30), wxSize(400, 600)) {
	wxMenu* menuFile = new wxMenu;
	menuFile->Append(ID_SETTINGS, "&Settings\tCtrl-H", "The settings");
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

	averagepayout = new wxStaticText(this, wxID_ANY, "Average Payout: 0.2", wxPoint(204, 30), wxSize(70, 30));
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