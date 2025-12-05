
#define _CRT_SECURE_NO_WARNINGS
#include "boost/filesystem.hpp"
#include "config_parser.hpp"
#include "scaner_directory.hpp"
#include "csv_handler.hpp"
#include "calculator_median.hpp"

int main(int argc, char** argv) {
	config_data cfg = config_parser::parsing(argc, argv);

	std::vector<std::string> files = scaner_directory::scan(cfg.input_dir,cfg.filename_mask);
	data_csv datas = csv_handler::get_data_from_files(files);

	std::cout << std::fixed << std::setprecision(10);

	calculator_median calculator(cfg.output_dir);
	calculator.calculate_median(datas);
}


