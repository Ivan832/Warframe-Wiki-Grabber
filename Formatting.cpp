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
	//Format <h3?
	result=IDgrabber(result, "h3");
	//Format <p>
	
	tag=("<p>");
	result=std::regex_replace(result, tag, "");
	tag = ("<\\/p>");
	result = std::regex_replace(result, tag, "\n");
	
	//Format Hyperlinks
	result=IDgrabber(result, "href");
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
	
	//Format html Lists
	tag = ("<li>");
	result = std::regex_replace(result, tag, "\n");
	tag = ("<\\/li>");
	result = std::regex_replace(result, tag, "");
	result = result.c_str();
	return result;
	
	
}