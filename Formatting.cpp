#include "pch.h"
#include <regex>
#include "globals.h"

std::string Format(std::string Input) {
	//Format <p>
	std::regex tag("<p>|<\\/p>");
	std::string result="";
	Input=std::regex_replace(Input, tag, "");
	
	//Format Hyperlinks
	tag = ("<a.*\\/a>");
	std::string titleHolder = "";
	std::smatch regexResult;
	std::smatch regexResult2;
	if (std::regex_search(Input, regexResult, tag)) {
		
		titleHolder = regexResult.str();
		print("\n\n titleHolder is currently:%s", titleHolder.c_str());
		std::regex t("title=\"(.*)\">");
		std::regex_search(titleHolder, regexResult2, t);
		titleHolder = regexResult2[1].str();
		print("\n\n titleHolder is currently:%s", titleHolder.c_str());
		Input=std::regex_replace(Input, tag, titleHolder);
		print("\n\n %s", Input.c_str());
	}
	result = Input.c_str();
	return result;
	
	
}