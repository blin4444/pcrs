#include "WelcomeForm.h"
using namespace Project4;

int main()
{
	/*MyForm^ test = gcnew MyForm();
	test->Show();
	while (true) {
	}*/
	System::Windows::Forms::Application::Run(gcnew WelcomeForm());
}