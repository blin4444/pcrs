#pragma once
using namespace System::Xml;
using namespace System::Drawing;
#include "XmlGuiMaker.h"
#include "PcrsXmlGuiMaker.h"
#include <vector>
using namespace std;

namespace Receptionist {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	
	/// <summary>
	/// Summary for Receptionist
	/// </summary>
	public ref class ReceptionistForm : public System::Windows::Forms::Form
	{
	public:
		ReceptionistForm(void)
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
		~ReceptionistForm()
		{
			if (components)
			{
				delete components;
			}
		}

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
			this->SuspendLayout();
			// 
			// ReceptionistForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(790, 307);
			this->ForeColor = System::Drawing::Color::Black;
			this->Name = L"ReceptionistForm";
			this->Text = L"Receptionist";
			this->Load += gcnew System::EventHandler(this, &ReceptionistForm::ReceptionistForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	
	private:
	
		System::Void ReceptionistForm_Load(System::Object^  sender, System::EventArgs^  e) {
		Xml::XmlTextReader^ reader = gcnew Xml::XmlTextReader("form.xml");

			FlowLayoutPanel^ panel = gcnew FlowLayoutPanel();
			panel->Padding = System::Windows::Forms::Padding(24);
			panel->AutoScroll = true;
			panel->Dock = DockStyle::Fill;
			this->Controls->Add(panel);

			

			XmlGuiMaker^ maker = gcnew PcrsXmlGuiMaker(panel);
			
		}
	};
}
