// Assistencia Remota Pluganet.cpp : main project file.

#include "stdafx.h"
#include "login.h"
#include "go.h"
#include "mainconn.h"

using namespace AssistenciaPluganetCliente;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	(gcnew login())->Show();
	Application::Run();
	return 0;
}