#include "main.h"
#include "rgFrame.h"

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
	rgFrame *myframe = new rgFrame();
	myframe->Show(true);

	return true;
}
