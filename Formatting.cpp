#include "pch.h"
#include <regex>
#include "globals.h"

std::string Format(std::string Input) {
	//Format <p>
	std::regex tag("<p>|<\\/p>");
	std::string result="";
	Input=std::regex_replace(Input, tag, "");
	
	//Format Hyperlinks
	tag = ("<a.*?\\/a>");
	std::string titleHolder = "";
	std::smatch regexResult;
	std::smatch regexResult2;
	if (std::regex_search(Input, regexResult, tag)) {
		print("regexRsult array size: %i\n", regexResult.size());
		for (int i = 0;i <10;i++) {
			tag = ("<a.*?\\/a>");
			std::regex_search(Input, regexResult, tag);
			print("Hyperlink Detected: Hyperlink #%i\n",i);
			titleHolder = regexResult.str();
			print("regexResult is currently:%s\n", regexResult.str().c_str());
			print("titleHolder is currently:%s\n", titleHolder.c_str());
			std::regex t("title=\"(.*)\">");
			std::regex_search(titleHolder, regexResult2, t);
			print("regexResult2 is currently:%s\n", regexResult2.str().c_str());
			titleHolder = regexResult2[1].str();
			print("titleHolder is currently:%s\n", titleHolder.c_str());
			tag = regexResult.str().c_str();
			print("Tag to be replaced:%s\n\n", regexResult.str().c_str());
			Input = std::regex_replace(Input, tag, titleHolder);
			print("%s\n", Input.c_str());
		}
		
	}
	
	//Format html Lists
	//tag="<ul.*"
	result = Input.c_str();
	return result;
	
	
}