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
// The above method is needed to deal with segements of html that invovle special characters, mainly ones that would cause trouble with Regex
std::string Format(std::string Input) {
	std::string result = "";
	//Format <p>
	std::regex tag("<p>.*<\\/p>");
	std::smatch paragraphSegs;
	std::string paragraphHolder = "";
	int paragraphCounter = 0;
	if (std::regex_match(Input, paragraphSegs, tag)) {
		while (paragraphSegs.size()) {
			paragraphHolder.append(paragraphSegs[paragraphCounter].str());
			paragraphCounter++;
		}
		Input = paragraphHolder;
	}
	tag=("<p>|<\\/p>");
	Input=std::regex_replace(Input, tag, "");
	
	//Format Hyperlinks
	tag = ("<a.*?\\/a>");
	std::string titleHolder = "";
	std::smatch regexResult; // Will hold the entire Href html string
	std::smatch regexResult2;//Will hold the title of whatever the Href is for
	if (std::regex_search(Input, regexResult, tag)) {// if a hyper link is detected
		while(regexResult.size()){// runs until no more hyperlinks are found
			tag = ("<a.*?\\/a>");
			std::regex_search(Input, regexResult, tag); //Acquire Href html segment
			titleHolder = regexResult.str();
			//print("regexResult is currently:%s\n", regexResult.str().c_str());
			//print("titleHolder is currently:%s\n", titleHolder.c_str());
			std::regex t("title=\"(.*)\">");
			std::regex_search(titleHolder, regexResult2, t);// Find title in href segment
			//print("regexResult2 is currently:%s\n", regexResult2.str().c_str());
			titleHolder = regexResult2[1].str();
			//print("titleHolder is currently:%s\n", titleHolder.c_str());
			//print("Tag to be replaced:%s\n\n", regexResult.str().c_str());
			replaceString(Input, regexResult.str(), titleHolder);//Replace entire html segment with only the Title 
			//print("%s\n", Input.c_str());
		}
	}
	
	//Format html Lists
	tag = ("<li>");
	Input = std::regex_replace(Input, tag, "\n");
	tag = ("<\\/li>");
	Input = std::regex_replace(Input, tag, "");
	result = Input.c_str();
	return result;
	
	
}