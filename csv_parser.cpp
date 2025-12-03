#include "csv_parser.hpp"

namespace qi = boost::spirit::qi;

std::vector<data_csv> csv_reader::get_data_from_files(const std::vector<std::string>& files) {

	std::vector<data_csv> all_data;

	for (const auto& file : files) {
		std::vector<level_csv> levels_csv;
		std::vector<trade_csv> trades_csv;
		data_csv data;

		std::ifstream in_file(file, std::ios::in);
		std::string line;

		int line_num = 0;
		bool is_level = false;
		while (std::getline(in_file, line)) {
			line_num++;
			(line.contains("rebuild") && line_num == 1) ? is_level = true : is_level = false;
			if (is_level) {
				level_csv level = {};
				parsing_csv(line, level);
				levels_csv.push_back(level);
			}
			else{
				trade_csv trade = {};
				parsing_csv(line, trade);
				trades_csv.push_back(trade);
			}
		}
		data.levels_csv = levels_csv;
		data.trades_csv = trades_csv;
		all_data.push_back(data);
	}
	return all_data;
}

bool csv_reader::parsing_csv(const std::string& line,level_csv& csv) {
	auto begin = line.begin();
	auto end = line.end();

	bool succes = qi::phrase_parse(begin, end,
		qi::int_ >> ";" >> qi::int_ >> ";" >>
		qi::double_ >> ";" >> qi::double_ >> ";" >>
		qi::raw[*(qi::char_ - ";")] >> ";" >> qi::bool_, qi::space,
		csv.receive_ts, csv.exchange_ts, csv.price, csv.quantitly, csv.side, csv.rebuild);
	return succes && begin == end;
}

bool csv_reader::parsing_csv(const std::string& line, trade_csv& csv) {
	auto begin = line.begin();
	auto end = line.end();

	bool succes = qi::phrase_parse(begin, end,
		qi::int_ >> ";" >> qi::int_ >> ";" >>
		qi::double_ >> ";" >> qi::double_ >> ";" >>
		qi::raw[*(qi::char_ - ";")], qi::space,
		csv.receive_ts, csv.exchange_ts, csv.price, csv.quantitly, csv.side);
	return succes && begin == end;
}