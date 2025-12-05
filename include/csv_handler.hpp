#pragma once
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include <thread>
#include <fstream>
#include <mutex>
#include "csv_data.hpp"




static class csv_handler {
public:
	static data_csv get_data_from_files(const std::vector<std::string>& files);
private:
	static std::mutex m;
	static data_csv data;
	static void thread_worker(std::string file);
	static void sort(data_csv& data);
	static bool parsing_csv(const std::string&,level_csv& csv);
};
