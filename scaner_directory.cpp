#include "scaner_directory.hpp"

std::vector<std::string> scaner_directory::scan(const config_data& data) {
	std::vector<std::string> files;
	if (data.input_dir.empty()) {
		throw std::runtime_error("Path to input_dir is empty");
	}
	if (!boost::filesystem::exists(data.input_dir)) {
		throw std::runtime_error("Input directory does not exist");
	}
	try {
		boost::filesystem::directory_iterator it(data.input_dir);
		for (auto& dir : it) {
			if (!boost::filesystem::is_regular_file(it->status())) {
				continue;
			}
			std::string ex = dir.path().extension().string();
			if (data.filename_mask.empty()) {
				if (ex == ".csv") {
					files.push_back(dir.path().string());
				}
			}
			else {
				for (auto& mask : data.filename_mask) {
					if (mask == dir.path().string() && ex == ".csv") {
						files.push_back(dir.path().string());
					}
				}
			}
		}
		return files;
	}
	catch (std::exception& ex) {
		std::cerr << "Error findCSV: " << ex.what() << std::endl;
		return files;
	}
}