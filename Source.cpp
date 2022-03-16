#include "Header.h"

//https://docs.wxwidgets.org/trunk/overview_helloworld.html
//https://www.webscrapingapi.com/c-web-scraping/
// https://docs.libcpr.org/
//https://www.youtube.com/watch?v=FOIbK4bJKS8

wxIMPLEMENT_APP(cApp);

cApp::cApp() {

}
cApp::~cApp() {

}
bool cApp::OnInit() {
	mFrame* frame = new mFrame();
	frame->Show(true);
	return true;
}