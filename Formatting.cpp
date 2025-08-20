#include "pch.h"
#include <regex>
#include "globals.h"

bool replaceString(std::string& str, const std::string& from, const std::string& to) {
	size_t start_pos = str.find(from);
	if (start_pos == std::string::npos)
		return false;
	str.replace(start_pos, from.length(), to);
	return true;
}
std::string IDgrabber(std::string Input,std::string type) {
	std::string InputData = Input;
	std::string titleHolder = "";
	std::smatch regexResult; // Will hold the entire Href(or Header3) html string
	std::smatch regexResult2;//Will hold the title of whatever the Href is for
	std::regex tag("href Or h3");
	std::regex t("Title Or ID");
	if (type == "href") {
		tag = ("<a.*?\\/a>");
		t=("title=\"(.*)\">");
	}
	else if (type == "h3") {
		tag = ("<h3.*?\\/h3>");
		t = ("id=\"(.*?)\">");
	}
	if (std::regex_search(InputData, regexResult, tag)) {// if a hyper link is detected
		while (regexResult.size()) {// runs until no more hyperlinks are found
			std::regex_search(InputData, regexResult, tag); //Acquire Href html segment
			titleHolder = regexResult.str();
			//print("regexResult is currently:%s\n", regexResult.str().c_str());
			//print("titleHolder is currently:%s\n", titleHolder.c_str());
			std::regex_search(titleHolder, regexResult2, t);// Find title in href segment
			//print("regexResult2 is currently:%s\n", regexResult2.str().c_str());
			titleHolder = regexResult2[1].str();
			//print("titleHolder is currently:%s\n", titleHolder.c_str());
			//print("Tag to be replaced:%s\n\n", regexResult.str().c_str());
			replaceString(InputData, regexResult.str(), titleHolder);//Replace entire html segment with only the Title 
			
			//print("%s\n", Input.c_str());
		}
	}
	return InputData;
}
// The above method is needed to deal with segements of html that invovle special characters, mainly ones that would cause trouble with Regex
std::string Format(std::string Input) {
	std::string result = Input;
	print("Initial Data result:\n%s\n", result.c_str());
	std::regex tag("To Be Redeclared");

	//Format <h2>
	tag = ("\/h2>|<h2");
	result = std::regex_replace(result, tag, "");
	print("Result after formatting h2 Tags:\n%s\n\n", result.c_str());

	//Format <h3?
	result = IDgrabber(result, "h3");
	print("Result after formatting h3 Tags:\n%s\n\n", result.c_str());

	//Format <p>
	tag = ("<p>");
	result = std::regex_replace(result, tag, "");
	tag = ("<\\/p>");
	result = std::regex_replace(result, tag, "\n");
	print("Result after formatting <p> Tags:\n%s\n\n", result.c_str());

	//Format Hyperlinks
	result = IDgrabber(result, "href");
	print("Result after formatting hyperlinks:\n%s\n\n", result.c_str());
#pragma region Old Hyperlink Formating
	////Format Hyperlinks
	//tag = ("<a.*?\\/a>");
	//std::string titleHolder = "";
	//std::smatch regexResult; // Will hold the entire Href(or Header3) html string
	//std::smatch regexResult2;//Will hold the title of whatever the Href is for
	//if (std::regex_search(result, regexResult, tag)) {// if a hyper link is detected
	//	while(regexResult.size()){// runs until no more hyperlinks are found
	//		tag = ("<a.*?\\/a>");
	//		std::regex_search(result, regexResult, tag); //Acquire Href html segment
	//		titleHolder = regexResult.str();
	//		//print("regexResult is currently:%s\n", regexResult.str().c_str());
	//		//print("titleHolder is currently:%s\n", titleHolder.c_str());
	//		std::regex t("title=\"(.*)\">");
	//		std::regex_search(titleHolder, regexResult2, t);// Find title in href segment
	//		//print("regexResult2 is currently:%s\n", regexResult2.str().c_str());
	//		titleHolder = regexResult2[1].str();
	//		//print("titleHolder is currently:%s\n", titleHolder.c_str());
	//		//print("Tag to be replaced:%s\n\n", regexResult.str().c_str());
	//		replaceString(result, regexResult.str(), titleHolder);//Replace entire html segment with only the Title 
	//		//print("%s\n", result.c_str());
	//	}
	//}
#pragma endregion

	//Format html Lists
	print("\n\n\n TESTING LIST FORMATING \n\n\n");
	tag = ("<li>");
	std::smatch listresult;
	int listamount = 0;
	print("listamount value= %i\n", listamount);
	while (std::regex_search(result, listresult, tag)) {// if a list tag is detected
		listamount += 1; //keep track of how many list items are found
		print("listamount value= %i\n", listamount);
		replaceString(result, "<li>", "\n--");
		replaceString(result, "</li>", "");
	}
	if (listamount == 1) { // if only 1 list item is found(for some reason?) treat like a single acquisition method instead of a list
		print("listamount value= %i\n", listamount);
		print("One List Object Found\n");
		replaceString(result, "\n--", "");
	}
	tag = ("<ul>");
	result = std::regex_replace(result, tag, "");
	tag = ("<\\/ul>");
	result = std::regex_replace(result, tag, "");
	print("Result after formatting list Tags:\n%s\n\n", result.c_str());

	//Format Tables
	tag = ("<table.*\/table>");
	std::smatch tableResult;
	std::regex_search(result, tableResult, tag);
	std::string tableHolder = tableResult.str();
	replaceString(result, tableHolder, "");
	print("Result after formatting table Tags:\n%s\n\n", result.c_str());

	//Format "Div style" sections
	tag = ("(<div style)(.*?)(<\/div>)");
	result = std::regex_replace(result, tag, "");
	print("Result after formatting Div style section:\n%s\n\n", result.c_str());

	//Format <br> tags
	tag = ("(<br)(.*?)(>)");
	result = std::regex_replace(result, tag, "");
	print("Result after formatting <br> tags:\n%s\n\n", result.c_str());

	//Foramt <b> (BOLD) tags
	tag = ("<b>|<\\/b>");
	result = std::regex_replace(result, tag, "");
	print("Result after formatting <b> tags:\n%s\n\n", result.c_str());



	result = result.c_str();
	return result;


}