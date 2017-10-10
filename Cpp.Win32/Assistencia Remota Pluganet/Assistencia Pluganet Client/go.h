#pragma once
#include "stdafx.h"
#include "message.h"
#include "mainconn.h"
#define WM_SOCKET		101

namespace AssistenciaPluganetCliente {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Security::Permissions;

	/// <summary>
	/// Summary for go
	/// </summary>
	public ref class go : public System::Windows::Forms::Form
	{
	public:
		go(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		int type, login_id, tickets;

	protected: 

	protected: 
		String ^login_name;

		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~go()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::StatusStrip^  statusStrip;
	protected: 

	private: System::Windows::Forms::ToolStripStatusLabel^  StatusLabel;
	private: System::Windows::Forms::Label^  labelAnnounce;
	private: System::Windows::Forms::Label^  labelTechName;
	private: System::Windows::Forms::TextBox^  inBox;
	private: System::Windows::Forms::Button^  buttonSend;


	private: System::Windows::Forms::RichTextBox^  outBox;
	private: System::Windows::Forms::Panel^  outBoxHack;
	private: System::ComponentModel::IContainer^  components;


	protected: 

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
			this->statusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->StatusLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->labelAnnounce = (gcnew System::Windows::Forms::Label());
			this->labelTechName = (gcnew System::Windows::Forms::Label());
			this->inBox = (gcnew System::Windows::Forms::TextBox());
			this->buttonSend = (gcnew System::Windows::Forms::Button());
			this->outBox = (gcnew System::Windows::Forms::RichTextBox());
			this->outBoxHack = (gcnew System::Windows::Forms::Panel());
			this->statusStrip->SuspendLayout();
			this->outBoxHack->SuspendLayout();
			this->SuspendLayout();
			// 
			// statusStrip
			// 
			this->statusStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->StatusLabel});
			this->statusStrip->Location = System::Drawing::Point(0, 315);
			this->statusStrip->Name = L"statusStrip";
			this->statusStrip->Size = System::Drawing::Size(284, 22);
			this->statusStrip->SizingGrip = false;
			this->statusStrip->TabIndex = 0;
			this->statusStrip->Text = L"statusStrip";
			// 
			// StatusLabel
			// 
			this->StatusLabel->Name = L"StatusLabel";
			this->StatusLabel->Size = System::Drawing::Size(118, 17);
			this->StatusLabel->Text = L"Esperando resposta...";
			// 
			// labelAnnounce
			// 
			this->labelAnnounce->AutoSize = true;
			this->labelAnnounce->Location = System::Drawing::Point(12, 9);
			this->labelAnnounce->Name = L"labelAnnounce";
			this->labelAnnounce->Size = System::Drawing::Size(149, 13);
			this->labelAnnounce->TabIndex = 1;
			this->labelAnnounce->Text = L"Você está conversando com: ";
			// 
			// labelTechName
			// 
			this->labelTechName->AutoSize = true;
			this->labelTechName->Location = System::Drawing::Point(168, 8);
			this->labelTechName->Name = L"labelTechName";
			this->labelTechName->Size = System::Drawing::Size(89, 13);
			this->labelTechName->TabIndex = 2;
			this->labelTechName->Text = L"[CARREGANDO]";
			// 
			// inBox
			// 
			this->inBox->Enabled = false;
			this->inBox->Location = System::Drawing::Point(12, 288);
			this->inBox->Name = L"inBox";
			this->inBox->Size = System::Drawing::Size(205, 20);
			this->inBox->TabIndex = 3;
			this->inBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &go::inBox_KeyDown);
			// 
			// buttonSend
			// 
			this->buttonSend->Enabled = false;
			this->buttonSend->Location = System::Drawing::Point(223, 288);
			this->buttonSend->Name = L"buttonSend";
			this->buttonSend->Size = System::Drawing::Size(49, 23);
			this->buttonSend->TabIndex = 4;
			this->buttonSend->Text = L"Enviar";
			this->buttonSend->UseVisualStyleBackColor = true;
			this->buttonSend->Click += gcnew System::EventHandler(this, &go::buttonSend_Click);
			// 
			// outBox
			// 
			this->outBox->BackColor = System::Drawing::Color::White;
			this->outBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->outBox->Dock = System::Windows::Forms::DockStyle::Fill;
			this->outBox->Location = System::Drawing::Point(0, 0);
			this->outBox->Margin = System::Windows::Forms::Padding(5);
			this->outBox->Name = L"outBox";
			this->outBox->ReadOnly = true;
			this->outBox->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::ForcedVertical;
			this->outBox->Size = System::Drawing::Size(258, 255);
			this->outBox->TabIndex = 7;
			this->outBox->Text = L"Textos deverão aparecer aqui:";
			this->outBox->TextChanged += gcnew System::EventHandler(this, &go::outBox_TextChanged);
			// 
			// outBoxHack
			// 
			this->outBoxHack->BackColor = System::Drawing::Color::White;
			this->outBoxHack->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->outBoxHack->Controls->Add(this->outBox);
			this->outBoxHack->Location = System::Drawing::Point(12, 25);
			this->outBoxHack->Name = L"outBoxHack";
			this->outBoxHack->Size = System::Drawing::Size(260, 257);
			this->outBoxHack->TabIndex = 8;
			// 
			// go
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 337);
			this->Controls->Add(this->outBoxHack);
			this->Controls->Add(this->buttonSend);
			this->Controls->Add(this->inBox);
			this->Controls->Add(this->labelTechName);
			this->Controls->Add(this->labelAnnounce);
			this->Controls->Add(this->statusStrip);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"go";
			this->Text = L"Assistência Pluganet";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &go::menu_FormClosed);
			this->Load += gcnew System::EventHandler(this, &go::menu_Load);
			this->statusStrip->ResumeLayout(false);
			this->statusStrip->PerformLayout();
			this->outBoxHack->ResumeLayout(false);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void menu_Load(System::Object^  sender, System::EventArgs^  e) {
				actualWID = reinterpret_cast<HWND>(this->Handle.ToPointer());
				int nResult=WSAAsyncSelect(mainConnSocket,actualWID,WM_SOCKET,(FD_CLOSE|FD_READ));
				if(nResult){
					showalert(L"Erro(1): WSAAsyncSelect falhou.");
					this->Close();
				}
			 }
	private: System::Void menu_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
				Application::Exit();
		}
	private: System::Void outBox_TextChanged(System::Object^  sender, System::EventArgs^  e) {
				this->outBox->SelectionStart = this->outBox->Text->Length;
				this->outBox->ScrollToCaret();
		}
	public: System::Void Logged(String ^login, int type, int lid, int tickets){
				this->type = type;
				this->login_id = lid;
				this->tickets = tickets;
				this->login_name = login;
				this->Show();
				mainConnSend("W\n");
		}
	protected:	
	System::Void connreceived(char* packet){
			switch(packet[0]){
				case 'W':
					char partner[61];
					sscanf(packet, "W\1%s\n", partner);
					if(partner[0] != '-'){
						this->labelTechName->Text = gcnew String(partner);
						this->inBox->Enabled = true;
						this->buttonSend->Enabled = true;
					}else
						mainConnSend("W\n");
				break;

				case 'O':
					this->inBox->Enabled = false;
					this->buttonSend->Enabled = false;
					this->labelTechName->Text = L"[CARREGANDO]";
				break;

				case 'X':
				break;

				case 'C':
					char messageC[2048];
					ZeroMemory(messageC,sizeof(messageC));
					sscanf(packet, "C\1%s\n", messageC);
					String::Join(this->labelTechName->Text,
						String::Concat(gcnew String(L"\n"), this->labelTechName->Text, gcnew String(L": "), gcnew String(messageC)));
				break;

				case 'c':
					char messagec[2048];
					ZeroMemory(messagec,sizeof(messagec));
					sscanf(packet, "c\1%s\n", messagec);
					String::Join(this->labelTechName->Text,
						String::Concat(gcnew String(L"\nVocê: "), gcnew String(messagec)));
				break;

				case 'S':
				break;
			}
		}
	System::Void connUpdate(DWORD_PTR param) {
			if(WSAGETSELECTERROR(param)){
				showalert(L"Conexão perdida com o servidor! O aplicativo será finalizado.");
				Application::Exit();
				return;
			}else switch(WSAGETSELECTEVENT(param)){
				case FD_CLOSE:
					showalert(L"Conexão perdida com o servidor! O aplicativo será finalizado.");
					Application::Exit();
					return;
				break;
				case FD_READ:
					char msgbuffer[256];
					ZeroMemory(msgbuffer,sizeof(msgbuffer));
					recv(mainConnSocket, msgbuffer, sizeof(msgbuffer), 0);
					//showalertA(msgbuffer);
					connreceived(msgbuffer);
					return;
				break;
			}
		}                            
	//SecurityPermission(SecurityAction::Demand, Flags=SecurityPermissionFlag::UnmanagedCode)]
	virtual System::Void WndProc( Message% m ) override {
			switch ( m.Msg ){
				case WM_SOCKET:
					connUpdate(reinterpret_cast<DWORD_PTR>(m.LParam.ToPointer()));
				break;
			}
			Form::WndProc( m );
		}

	private: System::Void buttonSend_Click(System::Object^  sender, System::EventArgs^  e) {
				 if(this->inBox->Text->Length < 1)
					 return;
				 chatSend(this->inBox->Text);
				 this->inBox->Text = L"";
		}
	private: System::Void inBox_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			if(e->KeyCode == Keys::Enter)
					buttonSend_Click(sender, gcnew EventArgs());
		}
};}