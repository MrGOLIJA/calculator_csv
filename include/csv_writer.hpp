#pragma once
#include <string>
#include <fstream>
#include <filesystem>
#include <time.h>

class csv_writer
{
public:
	csv_writer(std::string path);
	~csv_writer() = default;
	void write(const std::string& line);
private:
	std::string output_dir;
	std::string filename;
	std::ofstream file;
};

