#pragma once

#include "ReasonForm.h"
#include "ServerCommunication.h"

namespace Project4 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for FirstUseForm
	/// </summary>
	public ref class FirstUseForm : public System::Windows::Forms::Form
	{
	public:
		FirstUseForm(void)
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
		~FirstUseForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Button^  button_ok;
	private: System::Windows::Forms::Label^  label_login;

	private: System::Windows::Forms::TextBox^  token_entry;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Button^  button_return;
	private: System::Windows::Forms::Label^  label2;






	protected: 

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FirstUseForm::typeid));
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button_ok = (gcnew System::Windows::Forms::Button());
			this->label_login = (gcnew System::Windows::Forms::Label());
			this->token_entry = (gcnew System::Windows::Forms::TextBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button_return = (gcnew System::Windows::Forms::Button());
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// label1
			// 
			resources->ApplyResources(this->label1, L"label1");
			this->label1->Name = L"label1";
			// 
			// button_ok
			// 
			resources->ApplyResources(this->button_ok, L"button_ok");
			this->button_ok->Name = L"button_ok";
			this->button_ok->UseVisualStyleBackColor = true;
			this->button_ok->Click += gcnew System::EventHandler(this, &FirstUseForm::button_ok_Click);
			// 
			// label_login
			// 
			resources->ApplyResources(this->label_login, L"label_login");
			this->label_login->Name = L"label_login";
			// 
			// token_entry
			// 
			resources->ApplyResources(this->token_entry, L"token_entry");
			this->token_entry->Name = L"token_entry";
			this->token_entry->UseSystemPasswordChar = true;
			this->token_entry->TextChanged += gcnew System::EventHandler(this, &FirstUseForm::token_entry_TextChanged);
			// 
			// panel1
			// 
			resources->ApplyResources(this->panel1, L"panel1");
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->button_return);
			this->panel1->Controls->Add(this->token_entry);
			this->panel1->Controls->Add(this->label_login);
			this->panel1->Controls->Add(this->button_ok);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Name = L"panel1";
			// 
			// label2
			// 
			resources->ApplyResources(this->label2, L"label2");
			this->label2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(0)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->label2->Name = L"label2";
			// 
			// button_return
			// 
			resources->ApplyResources(this->button_return, L"button_return");
			this->button_return->Name = L"button_return";
			this->button_return->UseVisualStyleBackColor = true;
			this->button_return->Click += gcnew System::EventHandler(this, &FirstUseForm::button_return_Click);
			// 
			// FirstUseForm
			// 
			this->AcceptButton = this->button_ok;
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ControlBox = false;
			this->Controls->Add(this->panel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"FirstUseForm";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button_ok_Click(System::Object^  sender, System::EventArgs^  e);
private: System::Void token_entry_TextChanged(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void button_return_Click(System::Object^  sender, System::EventArgs^  e);
};
}
