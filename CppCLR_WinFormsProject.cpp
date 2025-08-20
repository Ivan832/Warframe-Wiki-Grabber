#include "pch.h"
#include "globals.h"
#define CURL_STATICLIB
#include "dependencies\include\curl\curl.h"
#include <regex>
#include <iostream>
#include <WinUser.h>



using namespace System;
CURL* curl;
std::string searchItem = "";

// int main(array<System::String ^> ^args)
// {
//    return 0;
// }

#include "Form1.h"


using namespace System::Windows::Forms;

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

	return 0;
}

//Method that does Write call backing
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

//Method that gets the Aquisition methods of items
std::string Aquisition(std::string data) {
#pragma region Old Anchor Method
	//std::regex r ("(Acquisition)");
	//std::smatch result;
	//int count = 0;
	//int Aclen = 16; //Magic number that acco

	//std::regex r("("Contents")");

	//while (count<3) {
	//	count++;
	//	std::regex_search(data, result, r);
	//	data = data.substr(result.position() + Aclen, data.length());
	//	print("Current Aquisition ping: %i \n", count);
	//	print("%s\n", data.c_str());
	//	print("------------------------------------------------------------------------------------------\n"
	//		  "------------------------------------------------------------------------------------------\n"
	//		  "------------------------------------------------------------------------------------------\n"
	//		  "------------------------------------------------------------------------------------------\n");
	//}
#pragma endregion
//^Old mehtod of finding Aquisition area.
	std::regex r("(id=\"Acquisition\")");
	std::smatch result;
	std::regex_search(data, result, r);
	data = data.substr(result.position(), data.length());
	std::string endInfo = "";

	//r = ("(<p)(.*?)(\/p>)"); // Grabs only what is directly after "Acquisition"
	//r = ("(<ul)(.*?)(\/ul>)");  //Grabs Aquisitipon methods that are formatted as a list
	//r= ("(\/h2>)(.*?)(<h2)");	  // Grabs everything between "Acquisition and next Header"
	r = ("(\/h2>)(.*?)(<h2)");
	std::regex_search(data, result, r); //Grab everything between Aquisition header and next header
	print("%s\n",result.str().c_str());
	data = result.str();
	endInfo = Format(data);
#pragma region Old Format section
	//r = ("(<p)(.*?)(\/p>)");
	//if (std::regex_search(data, result, r)) { //Check if the Aquisition Area has a paragraph for the methods
	//	data = result.str();
	//	endInfo=Format(data);
	//}
	//r = ("(<ul)(.*?)(\/ul>)"); //
	//if (std::regex_search(data, result, r)) { //Check if the Aquisition Area has a list for the methods
	//	data = result.str();
	//	endInfo = Format(data);
	//}
#pragma endregion
	


	//std::regex_search(data, result, r);
	//data = result.str();
	//print("PRINTING DATA RESULTS: %s\n", result.str().c_str());
	return endInfo;
}

