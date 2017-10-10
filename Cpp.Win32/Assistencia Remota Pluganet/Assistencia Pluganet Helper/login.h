#pragma once
#include "go.h"
#include "stdafx.h"
#include "message.h"
#include "mainconn.h"

namespace AssistenciaRemotaPluganet {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for login
	/// </summary>
	public ref class login : public System::Windows::Forms::Form
	{
	public:
		static login ^instance;
		login(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			instance = this;
			this->worked = false;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~login()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::StatusStrip^  statusStrip;
	private: System::Windows::Forms::ToolStripStatusLabel^  labelStatus;

	private: System::Windows::Forms::Button^  buttonGo;
	private: System::Windows::Forms::GroupBox^  groupMain;
	private: System::Windows::Forms::TextBox^  textPass;

	private: System::Windows::Forms::TextBox^  textLogin;
	private: System::Windows::Forms::Label^  labelPass;

	private: System::Windows::Forms::Label^  labelLogin;
	private: System::Windows::Forms::Timer^  timerConnect;
	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::Timer^  timerConnUpdate;

	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		bool worked;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->statusStrip = (gcnew System::Windows::Forms::StatusStrip());
			this->labelStatus = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->buttonGo = (gcnew System::Windows::Forms::Button());
			this->groupMain = (gcnew System::Windows::Forms::GroupBox());
			this->textPass = (gcnew System::Windows::Forms::TextBox());
			this->textLogin = (gcnew System::Windows::Forms::TextBox());
			this->labelPass = (gcnew System::Windows::Forms::Label());
			this->labelLogin = (gcnew System::Windows::Forms::Label());
			this->timerConnect = (gcnew System::Windows::Forms::Timer(this->components));
			this->timerConnUpdate = (gcnew System::Windows::Forms::Timer(this->components));
			this->statusStrip->SuspendLayout();
			this->groupMain->SuspendLayout();
			this->SuspendLayout();
			// 
			// statusStrip
			// 
			this->statusStrip->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->labelStatus});
			this->statusStrip->Location = System::Drawing::Point(0, 140);
			this->statusStrip->Name = L"statusStrip";
			this->statusStrip->Size = System::Drawing::Size(284, 22);
			this->statusStrip->SizingGrip = false;
			this->statusStrip->TabIndex = 3;
			// 
			// labelStatus
			// 
			this->labelStatus->Name = L"labelStatus";
			this->labelStatus->Size = System::Drawing::Size(99, 17);
			this->labelStatus->Text = L"Esperando ação...";
			// 
			// buttonGo
			// 
			this->buttonGo->Location = System::Drawing::Point(100, 106);
			this->buttonGo->Name = L"buttonGo";
			this->buttonGo->Size = System::Drawing::Size(75, 23);
			this->buttonGo->TabIndex = 6;
			this->buttonGo->Text = L"Conectar";
			this->buttonGo->UseVisualStyleBackColor = true;
			this->buttonGo->Click += gcnew System::EventHandler(this, &login::buttonGo_Click);
			// 
			// groupMain
			// 
			this->groupMain->Controls->Add(this->textPass);
			this->groupMain->Controls->Add(this->textLogin);
			this->groupMain->Controls->Add(this->labelPass);
			this->groupMain->Controls->Add(this->labelLogin);
			this->groupMain->Location = System::Drawing::Point(12, 12);
			this->groupMain->Name = L"groupMain";
			this->groupMain->Size = System::Drawing::Size(260, 88);
			this->groupMain->TabIndex = 7;
			this->groupMain->TabStop = false;
			this->groupMain->Text = L"Informações de acesso";
			// 
			// textPass
			// 
			this->textPass->Location = System::Drawing::Point(47, 51);
			this->textPass->Name = L"textPass";
			this->textPass->PasswordChar = '*';
			this->textPass->Size = System::Drawing::Size(207, 20);
			this->textPass->TabIndex = 9;
			this->textPass->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &login::textPass_KeyDown);
			this->textPass->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &login::textPass_KeyPress);
			// 
			// textLogin
			// 
			this->textLogin->Location = System::Drawing::Point(47, 26);
			this->textLogin->Name = L"textLogin";
			this->textLogin->Size = System::Drawing::Size(207, 20);
			this->textLogin->TabIndex = 8;
			this->textLogin->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &login::textLogin_KeyDown);
			this->textLogin->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &login::textLogin_KeyPress);
			// 
			// labelPass
			// 
			this->labelPass->AutoSize = true;
			this->labelPass->Location = System::Drawing::Point(6, 51);
			this->labelPass->Name = L"labelPass";
			this->labelPass->Size = System::Drawing::Size(41, 13);
			this->labelPass->TabIndex = 7;
			this->labelPass->Text = L"Senha:";
			// 
			// labelLogin
			// 
			this->labelLogin->AutoSize = true;
			this->labelLogin->Location = System::Drawing::Point(6, 29);
			this->labelLogin->Name = L"labelLogin";
			this->labelLogin->Size = System::Drawing::Size(36, 13);
			this->labelLogin->TabIndex = 6;
			this->labelLogin->Text = L"Login:";
			// 
			// timerConnect
			// 
			this->timerConnect->Interval = 2;
			this->timerConnect->Tick += gcnew System::EventHandler(this, &login::timerConnect_Tick);
			// 
			// timerConnUpdate
			// 
			this->timerConnUpdate->Interval = 2;
			this->timerConnUpdate->Tick += gcnew System::EventHandler(this, &login::timerConnUpdate_Tick);
			// 
			// login
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 162);
			this->Controls->Add(this->groupMain);
			this->Controls->Add(this->buttonGo);
			this->Controls->Add(this->statusStrip);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"login";
			this->Text = L"Assistência Pluganet [vFunc]";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &login::login_FormClosed);
			this->Load += gcnew System::EventHandler(this, &login::login_Load);
			this->statusStrip->ResumeLayout(false);
			this->statusStrip->PerformLayout();
			this->groupMain->ResumeLayout(false);
			this->groupMain->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void login_Load(System::Object^  sender, System::EventArgs^  e) {
				actualWID = reinterpret_cast<HWND>(this->Handle.ToPointer());
			}
	private: System::Void buttonGo_Click(System::Object^  sender, System::EventArgs^  e) {
				if(this->textLogin->Text->Length < 4){
					showalert(L"Login muito curto.");
					return;
				}else if(this->textPass->Text->Length < 4){
					showalert(L"Senha muito curta.");
					return;
				}
				this->buttonGo->Enabled = false;
				this->groupMain->UseWaitCursor = true;
				this->textLogin->ReadOnly = true;
				this->textPass->ReadOnly = true;
				this->labelStatus->Text = L"Conectando...";
				this->timerConnect->Enabled = true;
			}
	private: System::Void timerConnect_Tick(System::Object^  sender, System::EventArgs^  e) {
				this->timerConnect->Enabled = false;
				int result = mainConnConnect();
				if(result == 0){
					mainConnLogin(this->textLogin->Text, this->textPass->Text);
					this->labelStatus->Text = L"Conectado com sucesso! Autenticando...";
					this->timerConnUpdate->Enabled = true;
				}else{
					this->buttonGo->Enabled = true;
					this->textLogin->ReadOnly = false;
					this->textPass->ReadOnly = false;
					this->labelStatus->Text = L"Erro! Tente novamente...";
					this->groupMain->UseWaitCursor = false;
					this->worked = false;
				}
			}
	private: System::Void login_FormClosed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {
			if(!this->worked)
				Application::Exit();
		}
	public: System::Void connreceived(char* packet){
			if(packet[0] == 'l'){
				this->timerConnUpdate->Enabled = false;
				if(packet[2] != '-'){
					int type, lid, tickets;
					sscanf(packet, "l\1%i\1%i\1%i", &lid, &type, &tickets);
					if(type > 7){
						this->Hide();
						(gcnew go())->Logged(this->textLogin->Text, type, lid, tickets);
						this->worked = true;
						this->Close();
					}else{
						mainConnSend("D");
						this->buttonGo->Enabled = true;
						this->textLogin->ReadOnly = false;
						this->textPass->ReadOnly = false;
						this->labelStatus->Text = L"Utilize outra conta!";
						this->groupMain->UseWaitCursor = false;
						this->worked = false;
						showalert(L"Véi se é cliente não pode fazer isso...");
					}
					return;
				}else{
					this->buttonGo->Enabled = true;
					this->textLogin->ReadOnly = false;
					this->textPass->ReadOnly = false;
					this->labelStatus->Text = L"Erro! Tente novamente...";
					this->groupMain->UseWaitCursor = false;
					this->worked = false;
					showalert(L"Usuário e/ou senha errado(s).");
				}
			}
		}
	private: System::Void timerConnUpdate_Tick(System::Object^  sender, System::EventArgs^  e) {
			char msgbuffer[256];
			int recvr;
			recvr = recv(mainConnSocket, msgbuffer, sizeof(msgbuffer), 0);
			switch(recvr){
				case NULL:
					this->timerConnUpdate->Enabled = false;
					showalert(L"Conexão perdida com o servidor! O aplicativo será finalizado.");
					Application::Exit();
				break;
				case SOCKET_ERROR:
					this->timerConnUpdate->Enabled = false;
					showalert(L"Erro com a conexão! O aplicativo será finalizado.");
					Application::Exit();
				break;
				default:
					connreceived(msgbuffer);
				break;
			}
		}
	private: System::Void textPass_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			if(e->KeyChar == '\n')
				buttonGo_Click(sender, gcnew System::EventArgs());
		}
	private: System::Void textLogin_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) {
			if(e->KeyChar == '\n')
				buttonGo_Click(sender, gcnew System::EventArgs());
		}
	private: System::Void textLogin_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			if(e->KeyCode == Keys::Enter)
				buttonGo_Click(sender, gcnew EventArgs());
		}
	private: System::Void textPass_KeyDown(System::Object^  sender, System::Windows::Forms::KeyEventArgs^  e) {
			if(e->KeyCode == Keys::Enter)
				buttonGo_Click(sender, gcnew EventArgs());
		}
};
}