
#include "config_parser.hpp"
#include <spdlog/spdlog.h>

config_data config_parser::parsing(int argc, char** argv) {
	std::string path = parsing_arguments(argc, argv);
	config_data data = parsing_toml(path);
	return data;
}

std::string config_parser::parsing_arguments(int argc, char** argv) {
	std::string path_to_config = std::filesystem::current_path().string();
	std::cout << path_to_config;

	po::options_description desc("Config options");
	desc.add_options()("config,C", po::value<std::string>());
	desc.add_options()("cfg,c", po::value<std::string>());
	po::variables_map vm;

	try {
		po::parsed_options pars = po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();
		po::store(pars, vm);
		po::notify(vm);

		if (vm.count("config")) {
			spdlog::info("Read command arguments");
			return vm["config"].as<std::string>();
		}
		else if(vm.count("cfg")) {
			spdlog::info("Read command arguments");
			return vm["cfg"].as<std::string>();
		}
		spdlog::info("Arguments are not passed");
		return path_to_config;
	}
	catch (std::exception& ex) {
		spdlog::error("Error parsing arguments {}", ex.what());
		return path_to_config;
	}
}


config_data config_parser::parsing_toml(std::string path_to_config) {
	if (path_to_config.empty()) {
		spdlog::error("Path to config is empty");
		throw std::invalid_argument("Path to config is empty");
	}
	try {
		std::cout << path_to_config;
		spdlog::info("Parsing TOML file...");
		auto config = toml::parse_file(path_to_config);

		config_data data;
		data.input_dir = config["main"]["input"].value_or("");
		data.output_dir = config["main"]["output"].value_or("");
		auto masks = config["main"]["filename_mask"].as_array();
		if (masks != nullptr) {
			if (masks->empty()) {
				spdlog::error("Mask is empty");
			}
			else {
				for (auto& mask : *masks) {
					data.filename_mask.push_back(mask.value_or(""));
				}
			}
		}

		if (data.input_dir.empty()) {
			spdlog::error("Input directory must be specified in config");
			throw std::runtime_error("Input directory must be specified in config");
		}
		spdlog::info("Parsing TOML file succesful");
		return data;
	}
	catch (std::exception& ex) {
		spdlog::error("Error parsing config file {}: {}", path_to_config, ex.what());
		config_data data = {};
		data.input_dir = std::filesystem::current_path().string();
		return data;
	}
}


