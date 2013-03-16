#include "WelcomeForm.h"
using namespace Project4;

#pragma comment(linker,"\"/manifestdependency:type='win32' \
name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")

int main()
{
	/*MyForm^ test = gcnew MyForm();
	test->Show();
	while (true) {
	}*/
	System::Windows::Forms::Application::Run(gcnew WelcomeForm());
}