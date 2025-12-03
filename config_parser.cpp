#include "config_parser.hpp"

config_data config_parser::parsing(int argc, char** argv) {
	return parsing_toml(parsing_arguments(argc, argv));
}

std::string config_parser::parsing_arguments(int argc, char** argv) {
	std::string path_to_config = std::filesystem::current_path().string();

	po::options_description desc("Config options");
	desc.add_options()("config,C", po::value<std::string>());
	desc.add_options()("cfg,C", po::value<std::string>());
	po::variables_map vm;

	try {
		po::parsed_options pars = po::command_line_parser(argc, argv).options(desc).allow_unregistered().run();
		po::store(pars, vm);
		po::notify(vm);

		if (vm.count("config")) {
			path_to_config = vm["config"].as<std::string>();
		}
		else if(vm.count("cfg")) {
			path_to_config = vm["cfg"].as<std::string>();
		}
		return path_to_config;
	}
	catch (std::exception& ex) {
		std::cerr << "Error parsing arguments: " << ex.what() << std::endl;
		return path_to_config;
	}
}


config_data config_parser::parsing_toml(std::string path_to_config) {
	if (path_to_config.empty()) {
		throw std::invalid_argument("Path to config is empty");
	}
	try {
		auto config = toml::parse_file(path_to_config);

		config_data data;
		data.input_dir = config["main"]["input"].value_or("");
		data.output_dir = config["main"]["output"].value_or("");
		auto masks = config["main"]["filename_mask"].as_array();

		for (auto& mask : *masks) {
			data.filename_mask.push_back(mask.value_or(""));
		}

		if (data.input_dir.empty()) {
			throw std::runtime_error("Input directory must be specified in config");
		}

		return data;
	}
	catch (std::exception& ex) {
		std::cerr << "Error parsing config file" << path_to_config << " " << ex.what() << std::endl;
		config_data data = {};
		return data;
	}
}


