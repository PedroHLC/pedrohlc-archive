#pragma once

namespace pHLC_Chat {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ServerForm
	/// </summary>
	public ref class ServerForm : public System::Windows::Forms::Form
	{
	public:
		ServerForm(void)
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
		~ServerForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListBox^  listBox_Messages;
	protected: 
	private: System::Windows::Forms::TextBox^  textBox_Nick;
	private: System::Windows::Forms::TextBox^  textBox_Message;

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
			this->listBox_Messages = (gcnew System::Windows::Forms::ListBox());
			this->textBox_Nick = (gcnew System::Windows::Forms::TextBox());
			this->textBox_Message = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// listBox_Messages
			// 
			this->listBox_Messages->FormattingEnabled = true;
			this->listBox_Messages->Location = System::Drawing::Point(12, 12);
			this->listBox_Messages->Name = L"listBox_Messages";
			this->listBox_Messages->Size = System::Drawing::Size(600, 394);
			this->listBox_Messages->TabIndex = 0;
			// 
			// textBox_Nick
			// 
			this->textBox_Nick->Location = System::Drawing::Point(12, 412);
			this->textBox_Nick->Name = L"textBox_Nick";
			this->textBox_Nick->Size = System::Drawing::Size(124, 20);
			this->textBox_Nick->TabIndex = 1;
			// 
			// textBox_Message
			// 
			this->textBox_Message->Location = System::Drawing::Point(142, 412);
			this->textBox_Message->Name = L"textBox_Message";
			this->textBox_Message->Size = System::Drawing::Size(470, 20);
			this->textBox_Message->TabIndex = 2;
			// 
			// ServerForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(624, 442);
			this->Controls->Add(this->textBox_Message);
			this->Controls->Add(this->textBox_Nick);
			this->Controls->Add(this->listBox_Messages);
			this->Name = L"ServerForm";
			this->Text = L"pHLC\'s Chat [SERVER]";
			this->Load += gcnew System::EventHandler(this, &ServerForm::ServerForm_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void ServerForm_Load(System::Object^  sender, System::EventArgs^  e) {

			 }
	};
}
