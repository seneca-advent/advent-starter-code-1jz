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

namespace d5 {

	std::tuple<int, int, int> ticketInfo(const char* ticketCode) {
		int row = 0, col = 0, ID = 1337;
		int row_min = 0;
		int row_max = 127;
		int col_min = 0;
		int col_max = 7;

		for (int i = 0; i < strlen(ticketCode); i++) {
			switch (ticketCode[i]) {
			case 'B':
				row_min += ((row_max - row_min) >> 1) + 1;
				row = row_min;
				break;
			case 'F':
				row_max -= ((row_max - row_min) >> 1) + 1;
				row = row_max;
				break;
			case 'R':
				col_min += ((col_max - col_min) >> 1) + 1;
				col = col_min;
				break;
			case 'L':
				col_max -= ((col_max - col_min) >> 1) + 1;
				col = col_max;
			default:
				break;
			}
		}

		ID = (row << 3) + col;

		return std::make_tuple(row, col, ID);
	}

	int run() {
		try {
			std::vector<std::string> lines;// ({ "BFFFBBFRRR", "FFFBBBFRRR", "BBFFBBFRLL" });
			parser::readLines("day05.txt", lines);
			int highestID = 0;

			for (auto str : lines) {
				int row, col, ID;
				std::tie(row, col, ID) = ticketInfo(str.c_str());
				if (ID > highestID)
					highestID = ID;
				//std::cout << str << ": row " << row << ", column " << col << ", seat ID " << ID << "." << std::endl;
			}
			std::cout << highestID << std::endl;
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
	return d5::run();
}
