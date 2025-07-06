#include "pch.h"
#include "globals.h"
#define CURL_STATICLIB
#include "dependencies\include\curl\curl.h"
#include <regex>
#include <iostream>
#include <WinUser.h>


using namespace System;
CURL* curl;

// int main(array<System::String ^> ^args)
// {
//    return 0;
// }

#include "Form1.h"
//#define print(...) printf(__VA_ARGS__)

//std::string Aquisition = "";

using namespace System::Windows::Forms;
//std::string Aquisition();

[STAThread]
int main()
{
	AllocConsole();
	freopen_s(reinterpret_cast<FILE**>(stdin), "conin$", "r", stdin);
	freopen_s(reinterpret_cast<FILE**>(stdout), "conout$", "w", stdout);

	

	::ShowWindow(GetConsoleWindow(), SW_SHOW);
	
	curl = curl_easy_init();

	
	

	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	auto formInst = gcnew CppCLRWinFormsProject::Form1();

	Application::Run(formInst);
	curl_easy_cleanup(curl);
	print("Hello");
	/*Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew CppCLRWinFormsProject::Form1());*/

	return 0;
}


static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

std::string Aquisition(std::string data) {
	std::regex r ("(Acquisition)");
	std::smatch result;
	int count = 0;
	int Aclen = 11;

	while (count<3) {
		count++;
		std::regex_search(data, result, r);
		data = data.substr(result.position() + Aclen, data.length());
		print("Current Aquisition ping: %i \n", count);
	}
	r = ("(<p)(.*?)(\/p>){1}");
	std::regex_search(data, result, r);
	data = result.str();
	//print("PRINTING DATA RESULTS: %s\n", result.str().c_str());
	return data;
}