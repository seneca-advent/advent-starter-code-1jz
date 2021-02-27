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

namespace d {
	int run() {
		try {
			std::vector<std::string> lines;
			parser::readLines("day.txt", lines);
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
	return d::run();
}