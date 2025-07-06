#pragma once
#include "dependencies\include\curl\curl.h"
#include <string>
extern CURL* curl;
#define print(...) printf(__VA_ARGS__)
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);
std::string searchItem = "";
extern std::string Aquisition(std::string data);