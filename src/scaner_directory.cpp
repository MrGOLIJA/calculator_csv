
#include "scaner_directory.hpp"
#include <spdlog/spdlog.h>

std::vector<std::string> scaner_directory::scan(const std::string& path, const std::vector<std::string>& masks) {
	std::vector<std::string> files;
	if (path.empty()) {
		spdlog::error("Path to input directory is empty");
		throw std::runtime_error("Path to input_dir is empty");
	}
	if (!boost::filesystem::exists(path)) {
		spdlog::info("Input directory does not exist");
		throw std::runtime_error("Input directory does not exist");
	}
	try {
		spdlog::info("Searshing csv file in {}", path);
		boost::filesystem::directory_iterator it(path);
		for (auto& dir : it) {
			if (!boost::filesystem::is_regular_file(it->status())) {
				continue;
			}
			std::string ex = dir.path().extension().string();
			if (masks.empty()) {
				if (ex == ".csv") {
					spdlog::info("File found: {}", dir.path().string());
					files.push_back(dir.path().string());
				}
			}
			else {
				for (auto& mask : masks) {
					if (dir.path().string().contains(mask) && ex == ".csv") {
						spdlog::info("File found: {}", dir.path().string());
						files.push_back(dir.path().string());
					}
				}
			}
		}
		return files;
	}
	catch (std::exception& ex) {
		spdlog::error("Error find CSV files: {}", ex.what());
		std::cerr << "Error find CSV files: " << ex.what() << std::endl;
		return files;
	}
}