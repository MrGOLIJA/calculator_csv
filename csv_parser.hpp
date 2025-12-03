#pragma once
#include <boost/spirit/include/qi.hpp>
#include <boost/fusion/include/adapt_struct.hpp>
#include <cstdint>
#include <fstream>
#include <string>
#include <vector>
#include <tuple>

struct level_csv {
	uint64_t receive_ts;
	uint64_t exchange_ts;
	double price;
	double quantitly;
	std::string side;
	bool rebuild;
};

BOOST_FUSION_ADAPT_STRUCT(
	level_csv,
	(uint64_t, receive_ts)
	(uint64_t, exchange_ts)
	(double, price)
	(double, quantitly)
	(std::string, side)
	(bool, rebuild)
)

struct trade_csv{
	uint64_t receive_ts;
	uint64_t exchange_ts;
	double price;
	double quantitly;
	std::string side;
};

BOOST_FUSION_ADAPT_STRUCT(
	trade_csv,
	(uint64_t, receive_ts)
	(uint64_t, exchange_ts)
	(double, price)
	(double, quantitly)
	(std::string, side)
)

struct data_csv {
	std::vector<level_csv> levels_csv;
	std::vector<trade_csv> trades_csv;
};

class csv_reader {
public:
	std::vector<data_csv> get_data_from_files(const std::vector<std::string>& files);
private:
	bool parsing_csv(const std::string&,level_csv& csv);
	bool parsing_csv(const std::string&,trade_csv& csv);
};
