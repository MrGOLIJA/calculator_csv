#pragma once
#include <string>
#include <vector>

struct config_data
{
	std::string input_dir;
	std::string output_dir;
	std::vector<std::string> filename_mask;
};

