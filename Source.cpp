#include "Header.h"

//https://docs.wxwidgets.org/trunk/overview_helloworld.html
//https://www.webscrapingapi.com/c-web-scraping/
//https://stackoverflow.com/questions/53861300/how-do-you-properly-install-libcurl-for-use-in-visual-studio-2017
//https://www.youtube.com/watch?v=FOIbK4bJKS8
//CURL WORKS! HOLY SHIT NEVER THOUGHT I WOULD SEE THE DAY I CAN COMPILE A FUCKING LIBCURL PROGRAM!

wxIMPLEMENT_APP(cApp);
CURL* curl;
std::string out;
wxListBox* datalist;

std::string pricing;
std::string growth[5];
float avgpayout;
std::string pricerecovery;
std::string averageyield;
std::string yieldanddividend;
std::string freqi;
std::string mktcap;
std::string symbol;

std::fstream file;
std::vector<pay> pays;

cApp::cApp() {

}
cApp::~cApp() {

}
bool cApp::OnInit() {
	curl = curl_easy_init();
	if (!curl) {
		return false;
	}
	mFrame* frame = new mFrame();
	frame->Show(true);
	return true;
}
