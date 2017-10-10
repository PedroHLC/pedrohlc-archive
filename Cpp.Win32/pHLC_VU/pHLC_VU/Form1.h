#pragma once
#include <Mmdeviceapi.h>
//#include <Devicetopology.h>
#include <Endpointvolume.h>
#include <shellapi.h>

#define channels_num 2
IAudioMeterInformation *pMeterInfo;
IAudioBass *pBass;
IAudioMidrange *pMid;
IAudioTreble *pTreble;
float peaks[channels_num];
NOTIFYICONDATA ntfIcnDat;

namespace pHLC_VU {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}



	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ProgressBar^  prgBar_LeftCh;
	protected: 
	private: System::Windows::Forms::ProgressBar^  prgBar_RightCh;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::TrackBar^  trackBar_bass;


	private: System::ComponentModel::IContainer^  components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->prgBar_LeftCh = (gcnew System::Windows::Forms::ProgressBar());
			this->prgBar_RightCh = (gcnew System::Windows::Forms::ProgressBar());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->trackBar_bass = (gcnew System::Windows::Forms::TrackBar());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar_bass))->BeginInit();
			this->SuspendLayout();
			// 
			// prgBar_LeftCh
			// 
			this->prgBar_LeftCh->Location = System::Drawing::Point(0, 0);
			this->prgBar_LeftCh->Maximum = 1000;
			this->prgBar_LeftCh->Name = L"prgBar_LeftCh";
			this->prgBar_LeftCh->Size = System::Drawing::Size(240, 25);
			this->prgBar_LeftCh->TabIndex = 0;
			this->prgBar_LeftCh->Value = 50;
			// 
			// prgBar_RightCh
			// 
			this->prgBar_RightCh->Location = System::Drawing::Point(0, 30);
			this->prgBar_RightCh->Maximum = 1000;
			this->prgBar_RightCh->Name = L"prgBar_RightCh";
			this->prgBar_RightCh->Size = System::Drawing::Size(240, 25);
			this->prgBar_RightCh->TabIndex = 1;
			this->prgBar_RightCh->Value = 50;
			// 
			// timer1
			// 
			this->timer1->Interval = 2;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// trackBar_bass
			// 
			this->trackBar_bass->Location = System::Drawing::Point(0, 61);
			this->trackBar_bass->Maximum = 100;
			this->trackBar_bass->Minimum = -100;
			this->trackBar_bass->Name = L"trackBar_bass";
			this->trackBar_bass->Size = System::Drawing::Size(240, 45);
			this->trackBar_bass->TabIndex = 2;
			this->trackBar_bass->Visible = false;
			this->trackBar_bass->Scroll += gcnew System::EventHandler(this, &Form1::trackBar_bass_Scroll);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(240, 55);
			this->Controls->Add(this->trackBar_bass);
			this->Controls->Add(this->prgBar_RightCh);
			this->Controls->Add(this->prgBar_LeftCh);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->ShowInTaskbar = false;
			this->Text = L"pHLC\'s VU";
			this->TopMost = true;
			this->TransparencyKey = System::Drawing::Color::Black;
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->trackBar_bass))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: void Form1_Load(System::Object^  sender, System::EventArgs^  e) {
				//Sytem Tray, from here:
				// http://codingmisadventures.wordpress.com/2009/02/20/creating-a-system-tray-icon-using-visual-c-and-win32/
				ntfIcnDat.cbSize = sizeof(NOTIFYICONDATA);
				ntfIcnDat.hWnd = (HWND)this->Handle.ToPointer();
				ntfIcnDat.uID = 100;
				ntfIcnDat.uVersion = NOTIFYICON_VERSION;
				ntfIcnDat.uCallbackMessage = (WM_USER + 1);
				ntfIcnDat.hIcon = LoadIcon(GetModuleHandle(0), IDI_APPLICATION);
				if(ntfIcnDat.hIcon == NULL)
					ntfIcnDat.hIcon = LoadIcon(NULL, IDI_APPLICATION);
				wcscpy_s(ntfIcnDat.szTip, L"pHLC's VU");
				ntfIcnDat.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP;
				Shell_NotifyIcon(NIM_ADD, &ntfIcnDat);
				//Prepare COM System
				CoInitialize(NULL);
				//Some Variables
				HRESULT result;
				IMMDeviceEnumerator *pEnumerator = NULL;
				IMMDevice *pDevice = NULL;
				IDeviceTopology *pTopology = NULL;
				//IConnector * pConnectorEnd = NULL;
				//IConnector * pConnectorDev = NULL;
				ISubunit *pSubunit = NULL;
				IPart *pPart = NULL;
				//IPartsList *pPartsList = NULL;
				//IMMDeviceEnumerator
				result = CoCreateInstance(
					__uuidof(MMDeviceEnumerator), NULL,
					CLSCTX_ALL, __uuidof(IMMDeviceEnumerator),
					(LPVOID*)&pEnumerator);
				if(FAILED(result))
					exit(1);
				//IMMDevice
				result = pEnumerator->GetDefaultAudioEndpoint(eRender, eMultimedia, &pDevice);
				if(FAILED(result))
					exit(2);
				//IAudioMeterInformation
				result = pDevice->Activate(__uuidof(IAudioMeterInformation),
                           			CLSCTX_ALL, NULL, (void**)&pMeterInfo);
				if(FAILED(result))
					exit(3);
				/*//IDeviceTopology
				result = pDevice->Activate(__uuidof(IDeviceTopology),
                           			CLSCTX_ALL, NULL, (void**)&pTopology);
				if(FAILED(result))
					exit(4);
				//IConnector (End)
				result = pTopology->GetConnector(0, &pConnectorEnd);
				if(FAILED(result))
					exit(5);
				//IConnector (Dev)
				result = pConnectorEnd->GetConnectedTo(&pConnectorDev);
				if(FAILED(result))
					exit(6);
				//IPart
				result = pConnectorDev->QueryInterface(__uuidof(IPart), (void**)&pPart);
					// or
					//ISubunit
					result = pTopology->GetSubunit(0, &pSubunit);
					if(result == E_INVALIDARG)
						MessageBoxA(0, "B", "", 0);
					if(result == E_POINTER)
						MessageBoxA(0, "A", "", 0);
					if(FAILED(result))
						exit(5);
					//IPart
					result = pSubunit->QueryInterface(__uuidof(IPart), (void**)&pPart);
				if(FAILED(result))
					exit(7);
				//IAudioBass
				result = pPart->Activate(CLSCTX_ALL,
									__uuidof(IAudioBass), (void**)&pBass);
				if(FAILED(result))
					exit(8);
				//IAudioMidrange
				result = pPart->Activate(CLSCTX_ALL,
									__uuidof(IAudioMidrange), (void**)&pMid);
				if(FAILED(result))
					exit(9);
				//IAudioTreble
				result = pPart->Activate(CLSCTX_ALL,
									__uuidof(IAudioTreble), (void**)&pTreble);
				if(FAILED(result))
					exit(10);*/
				//Timer
				timer1->Enabled = true;
				//End
			 	}
	private: void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
				if(FAILED(pMeterInfo->GetChannelsPeakValues(channels_num, peaks)))
					exit(1);
				prgBar_LeftCh->Value = (int) ((double) peaks[0] * (double) prgBar_LeftCh->Maximum);
				prgBar_RightCh->Value = (int)((double) peaks[1] * (double) prgBar_RightCh->Maximum);
	}
	protected: virtual void WndProc(Message% m) override{
				// Listen for operating system messages.
				switch (m.Msg){
					case (WM_USER + 1):
						switch (m.LParam.ToInt32()){
							case WM_LBUTTONDBLCLK:
								if (this->FormBorderStyle == System::Windows::Forms::FormBorderStyle::FixedDialog){
									this->TransparencyKey = System::Drawing::SystemColors::Control;
									this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
								}else{
									this->TransparencyKey = System::Drawing::Color::Black;
									this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedDialog;
								}
							break;
						}
					break;
					case WM_CLOSE:
						Shell_NotifyIcon(NIM_DELETE, &ntfIcnDat);
					break;
				}
				Form::WndProc( m );
	}
private: System::Void trackBar_bass_Scroll(System::Object^  sender, System::EventArgs^  e) {
			 /*double value = (double) trackBar_bass->Value / 100;
			 UINT chnum = 0;
			 pBass->GetChannelCount(&chnum);
			 if((int)chnum < 1)
				 return;
			 for(int i=0; i < (int)chnum; i++)
				pBass->SetLevel(i, (float) value, NULL);*/
		 }
};
}