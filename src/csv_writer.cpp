
#include "csv_writer.hpp"
#include <spdlog/spdlog.h>

csv_writer::csv_writer(std::string path) {
	if (std::filesystem::exists(path)) {
		filename = path + std::to_string(time(0));
		filename += ".csv";
		file.open(filename, std::ios::out);
	}
	else {
		std::string out_path = std::filesystem::current_path().string();
		out_path += "\\output\\";
		output_dir = std::filesystem::create_directory(out_path);
		filename = out_path + std::to_string(time(0));
		filename += ".csv";
		file.open(filename, std::ios::out);
		spdlog::info("Output file {} from {} is open", filename, output_dir);
	}
}

void csv_writer::write(const std::string& line) {
	file << line << "\n";
}
