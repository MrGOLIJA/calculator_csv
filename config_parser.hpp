#pragma once
#include <iostream>
#include <filesystem>
#include <boost/program_options.hpp>
#include<toml++/toml.hpp>
#include "config_data.hpp"

namespace po = boost::program_options;


static class config_parser {
public:
	static config_data parsing(int argc, char** argv);
private:
	static std::string parsing_arguments(int argc, char** argv);
	static config_data parsing_toml(std::string path_to_file);
};
