#define _CRT_SECURE_NO_WARNINGS
#include "boost/filesystem.hpp"
#include "config_parser.hpp"
#include "scaner_directory.hpp"

int main(int argc, char** argv) {
	config_data data = config_parser::parsing(argc, argv);
	std::vector<std::string> files = scaner_directory::scan(data);

}


