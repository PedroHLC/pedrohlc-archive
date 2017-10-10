#pragma once

namespace pHLC_Chat {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for LaunchForm
	/// </summary>
	public ref class LaunchForm : public System::Windows::Forms::Form
	{
	public:
		LaunchForm(void)
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
		~LaunchForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label_FormDesc;
	protected: 
	private: System::Windows::Forms::Button^  button_Host;
	private: System::Windows::Forms::Button^  button_Client;
	private: System::Windows::Forms::Button^  button_search;
	private: System::Windows::Forms::ListBox^  listBox_Servers;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label_FormDesc = (gcnew System::Windows::Forms::Label());
			this->button_Host = (gcnew System::Windows::Forms::Button());
			this->button_Client = (gcnew System::Windows::Forms::Button());
			this->button_search = (gcnew System::Windows::Forms::Button());
			this->listBox_Servers = (gcnew System::Windows::Forms::ListBox());
			this->SuspendLayout();
			// 
			// label_FormDesc
			// 
			this->label_FormDesc->AutoSize = true;
			this->label_FormDesc->Location = System::Drawing::Point(5, 5);
			this->label_FormDesc->Name = L"label_FormDesc";
			this->label_FormDesc->Size = System::Drawing::Size(104, 13);
			this->label_FormDesc->TabIndex = 0;
			this->label_FormDesc->Text = L"Escolha uma opção:";
			// 
			// button_Host
			// 
			this->button_Host->Location = System::Drawing::Point(5, 30);
			this->button_Host->Name = L"button_Host";
			this->button_Host->Size = System::Drawing::Size(104, 23);
			this->button_Host->TabIndex = 1;
			this->button_Host->Text = L"Host";
			this->button_Host->UseVisualStyleBackColor = true;
			this->button_Host->Click += gcnew System::EventHandler(this, &LaunchForm::button_Host_Click);
			// 
			// button_Client
			// 
			this->button_Client->Location = System::Drawing::Point(4, 59);
			this->button_Client->Name = L"button_Client";
			this->button_Client->Size = System::Drawing::Size(105, 23);
			this->button_Client->TabIndex = 2;
			this->button_Client->Text = L"Conectar pelo IP";
			this->button_Client->UseVisualStyleBackColor = true;
			// 
			// button_search
			// 
			this->button_search->Enabled = false;
			this->button_search->Location = System::Drawing::Point(5, 88);
			this->button_search->Name = L"button_search";
			this->button_search->Size = System::Drawing::Size(104, 23);
			this->button_search->TabIndex = 3;
			this->button_search->Text = L"Procurar Servidor";
			this->button_search->UseVisualStyleBackColor = true;
			// 
			// listBox_Servers
			// 
			this->listBox_Servers->Enabled = false;
			this->listBox_Servers->FormattingEnabled = true;
			this->listBox_Servers->Location = System::Drawing::Point(115, 5);
			this->listBox_Servers->Name = L"listBox_Servers";
			this->listBox_Servers->Size = System::Drawing::Size(74, 108);
			this->listBox_Servers->TabIndex = 4;
			// 
			// LaunchForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(201, 120);
			this->Controls->Add(this->listBox_Servers);
			this->Controls->Add(this->button_search);
			this->Controls->Add(this->button_Client);
			this->Controls->Add(this->button_Host);
			this->Controls->Add(this->label_FormDesc);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"LaunchForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"pHLC\'s Chat";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button_Host_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->Hide();
			 }
};
}

