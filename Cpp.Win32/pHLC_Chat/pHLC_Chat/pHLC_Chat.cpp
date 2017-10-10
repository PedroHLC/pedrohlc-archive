// pHLC_Chat.cpp : main project file.

#include "stdafx.h"
#include "LaunchForm.h"

using namespace pHLC_Chat;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew LaunchForm());
	return 0;
}
