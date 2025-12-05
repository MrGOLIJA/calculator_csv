
#include "calculator_median.hpp"
#include <spdlog/spdlog.h>

#include <iostream>

void calculator_median::calculate_median(const data_csv& data) {
	int last_median = 0;
	int count = 0;
	for (const auto& d : data) {
		ac(d.price);
		if (count == 0) {
			writer.write("receive_ts;price_median");
			last_median = d.price;
			writer.write(std::format("{};{}",d.receive_ts,d.price));
			count++;
		}
		else if (count == 1) {
			count++;
			auto median = acc::mean(ac);
			if (last_median != median) {
				writer.write(std::format("{};{}", d.receive_ts, median));
			}
		}
		else {
			count++;
			auto median = acc::median(ac);
			if (last_median != median) {
				writer.write(std::format("{};{}", d.receive_ts,	median));
			}
		}
	}
	spdlog::info("Wrote {} median", count);
}
