#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <tuple>
#include <queue>
#include <unordered_map>

namespace parser {
	void readLines(const char* fn, std::vector<std::string>& lines) {
		std::ifstream file(fn);

		if (!file) {
			throw std::tuple<std::string, int>((std::string("Cannot open [" ) + fn + "]").c_str(), 1);
		}

		std::string line;
		while (std::getline(file, line)) {
			lines.push_back(line);
		}
	}
}

namespace d6 {

	int groupSum(std::deque<std::string>& lines) {
		std::unordered_map<char, bool> answered_questions;
		int sum = 0;
		for (auto str = lines.begin(); !lines.empty() && !str->empty(); str++) {
			for(auto i = str->begin(); i != str->end(); i++) {
				bool& answered = answered_questions[*i];
				if (!answered) {
					answered = true;
					sum++;
				}
			}
			lines.pop_front();
		}

		if (!lines.empty() && lines.begin()->empty()) {
			lines.pop_front();
		}

		return sum;
	}

	int largestSum(std::deque<std::string>& lines) {
		int sum = 0;
		while (!lines.empty()) {
			sum += groupSum(lines);
		}
		return sum;
	}

	int run() {
		try {
			std::vector<std::string> lines;
			parser::readLines("day06.txt", lines);
			std::deque<std::string> groupLines(lines.begin(), lines.end());
			std::cout << largestSum(groupLines) << std::endl;
		}
		catch (std::tuple<std::string, int> e) {
			std::string error_msg;
			int error_code;
			std::tie(error_msg, error_code) = e;
			std::cerr << error_msg << std::endl;
			return error_code;
		}
		return 0;
	}
}

int main() {
	return d6::run();
}