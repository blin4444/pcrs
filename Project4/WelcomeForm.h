#pragma once
#include "FirstUseForm.h"

namespace Project4 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Threading;
	using namespace System::Globalization;

	/// <summary>
	/// Summary for WelcomeForm
	/// </summary>
	public ref class WelcomeForm : public System::Windows::Forms::Form
	{
	public:
		WelcomeForm(void)
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
		~WelcomeForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::Panel^  panel1;
	private: System::Windows::Forms::Button^  button_FR;
	private: System::Windows::Forms::Button^  button_EN;


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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(WelcomeForm::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->button_FR = (gcnew System::Windows::Forms::Button());
			this->button_EN = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->panel1->SuspendLayout();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->InitialImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.InitialImage")));
			this->pictureBox1->Location = System::Drawing::Point(23, 33);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(897, 179);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// panel1
			// 
			this->panel1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->panel1->BackColor = System::Drawing::SystemColors::Window;
			this->panel1->Controls->Add(this->button_FR);
			this->panel1->Controls->Add(this->button_EN);
			this->panel1->Controls->Add(this->pictureBox1);
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(932, 468);
			this->panel1->TabIndex = 1;
			// 
			// button_FR
			// 
			this->button_FR->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->button_FR->Font = (gcnew System::Drawing::Font(L"Arial", 20.25F));
			this->button_FR->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->button_FR->Location = System::Drawing::Point(475, 339);
			this->button_FR->Name = L"button_FR";
			this->button_FR->Size = System::Drawing::Size(208, 55);
			this->button_FR->TabIndex = 5;
			this->button_FR->Text = L"Bienvenue";
			this->button_FR->UseVisualStyleBackColor = true;
			this->button_FR->Click += gcnew System::EventHandler(this, &WelcomeForm::button_FR_Click);
			// 
			// button_EN
			// 
			this->button_EN->FlatStyle = System::Windows::Forms::FlatStyle::System;
			this->button_EN->Font = (gcnew System::Drawing::Font(L"Arial", 20.25F));
			this->button_EN->ImeMode = System::Windows::Forms::ImeMode::NoControl;
			this->button_EN->Location = System::Drawing::Point(213, 339);
			this->button_EN->Name = L"button_EN";
			this->button_EN->Size = System::Drawing::Size(208, 55);
			this->button_EN->TabIndex = 5;
			this->button_EN->Text = L"Welcome";
			this->button_EN->UseVisualStyleBackColor = true;
			this->button_EN->Click += gcnew System::EventHandler(this, &WelcomeForm::button_EN_Click);
			// 
			// WelcomeForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::Window;
			this->ClientSize = System::Drawing::Size(932, 468);
			this->Controls->Add(this->panel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"WelcomeForm";
			this->Text = L"WelcomeForm";
			this->WindowState = System::Windows::Forms::FormWindowState::Maximized;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->panel1->ResumeLayout(false);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button_EN_Click(System::Object^  sender, System::EventArgs^  e) {
				 Thread::CurrentThread->CurrentUICulture = gcnew CultureInfo("en-CA");
				 FirstUseForm ^next_form = gcnew FirstUseForm();
				 next_form->ShowDialog();
				 WelcomeForm::Visible = false;
			 }
private: System::Void button_FR_Click(System::Object^  sender, System::EventArgs^  e) {
			Thread::CurrentThread->CurrentUICulture = gcnew CultureInfo("fr-FR");
			FirstUseForm ^next_form = gcnew FirstUseForm();
			next_form->ShowDialog();
			WelcomeForm::Visible = false;
		 }
};
}
