#pragma once
#include "boost/filesystem.hpp"
#include <iostream>
#include <vector>
#include <regex>
#include "config_data.hpp"

class config_data;

static class scaner_directory {
public:
	static std::vector<std::string> scan(const std::string& path, const std::vector<std::string>& mask);
};