#pragma once
#include <vector>
#include <string>

struct level_csv {
	uint64_t receive_ts;
	uint64_t exchange_ts;
	double price;
	double quantitly;
	std::string side;
	bool rebuild;
};

using data_csv = std::vector<level_csv>;
