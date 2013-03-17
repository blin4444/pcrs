#include "FirstUseForm.h"
#include "WelcomeForm.h"

using namespace System;

Void Project4::FirstUseForm::button_ok_Click(Object^  sender, EventArgs^  e) {
	ServerCommunication^ comm = gcnew ServerCommunication();
	int r = comm->CheckToken(FirstUseForm::token_entry->Text);
	if (r==0) {
		FirstUseForm::Visible = false;
		ReasonForm ^form2 = gcnew ReasonForm(FirstUseForm::token_entry->Text);
		form2->ShowDialog();

		FirstUseForm::Close();
	}
	else {
		FirstUseForm::label_login->Visible = false;
		FirstUseForm::label2->Visible = true;
		FirstUseForm::button_return->Visible = true;
	}
}

Void Project4::FirstUseForm::button_return_Click(Object^  sender, EventArgs^  e) {
	WelcomeForm ^form2 = gcnew WelcomeForm();
	form2->ShowDialog();
	FirstUseForm::Close();
}