#pragma once
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/median.hpp>
#include <boost/accumulators/statistics/mean.hpp>
#include "csv_data.hpp"
#include "csv_writer.hpp"



namespace acc = boost::accumulators;

class calculator_median
{
public:
	calculator_median(const std::string& path) : writer(path) {}
	void calculate_median(const data_csv& data);
	void init_writer(const std::string& path);
private:
	csv_writer writer;
	acc::accumulator_set<double, acc::stats<acc::tag::median,acc::tag::mean>> ac;
};

