#include "csv_handler.hpp"
#include "spdlog/spdlog.h"
#include <functional>
#include <iostream>

data_csv csv_handler::data = {};
std::mutex csv_handler::m;

data_csv csv_handler::get_data_from_files(const std::vector<std::string>& files) {
    std::vector<std::thread> threads;

    for (const auto& file : files) {
        threads.push_back(std::thread(thread_worker, file));

    }
    for (auto& t : threads) {
        try {
            if (t.joinable()) {
                t.join();
            }
        }
        catch (std::exception& ex) {
            spdlog::error("Error join thread {}", ex.what());
        }
    }
    sort(data);
    spdlog::info("Parsing files sucessful");
    return data;
}

void csv_handler::thread_worker(std::string file) {
    spdlog::info("Parsing {}...", file);

    std::ifstream in_file(file, std::ios::in);
    if (!in_file.is_open()) {
        spdlog::error("Error: could not open this file {}", file);
        return;
    }

    std::string line;
    int line_num = 0;

    if (!std::getline(in_file, line)) {
        spdlog::error("Error: file {} empty or unavaliable", file);
        return;
    }

    while (std::getline(in_file, line)) {
        ++line_num;

        if (line.empty()) continue;

        try {
            level_csv level = { 0 };
            if (!parsing_csv(line, level)) {
                spdlog::error("Error parsing level file {} on line {}", file, line);
                continue;
            }
            std::lock_guard<std::mutex> lock(m);
            data.push_back(level);
        }
        catch (const std::exception& e) {
            spdlog::error("Error parsing trade file {} on line {}", file, line);
        }
    }
    spdlog::info("Parsing {} succesful", file);
}

bool csv_handler::parsing_csv(const std::string& line, level_csv& csv) {
    namespace qi = boost::spirit::qi;

    auto begin = line.begin();
    auto end = line.end();

    bool success = qi::phrase_parse(begin, end,
        qi::ulong_long >> qi::omit[';'] >> qi::ulong_long >> qi::omit[';'] >>
        qi::double_ >> qi::omit[';'] >> qi::double_ >> qi::omit[';'] >>
        qi::raw[*(qi::char_ - ";")] >> -(qi::omit[';'] >> qi::int_), qi::space,
        csv.receive_ts, csv.exchange_ts, csv.price, csv.quantitly, csv.side, csv.rebuild);

    if (!success || begin != end) {
        return false;
    }
    return true;
}



void csv_handler::sort(data_csv& data)
{
    std::ranges::sort(data, std::ranges::less{}, &level_csv::receive_ts);
}