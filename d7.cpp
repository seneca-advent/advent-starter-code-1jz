#include <fstream>
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <tuple>
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

namespace d7 {

	// global hashmap cause im lazy
	std::unordered_map<std::string, std::unordered_map<std::string, bool>> bags;

	// fills `bags` with bag-types the bags they contain
	void loadBags(std::vector<std::string> lines) {
		for (auto str : lines) {
			std::string bag = str.substr(0, str.find("contain") - 6);
			std::unordered_map<std::string, bool> contains;
			std::string substr = str.substr(str.find("contain") + 8, str.length());
			for (;;) {
				int delim = substr.find(",");
				std::string heldBag = substr.substr(0, (delim != -1 ? delim : substr.length() - 1));
				
				if (heldBag.compare("no other bags") == 0) {
					break;
				}

				heldBag = heldBag.substr(heldBag.find(" ") + 1, heldBag.find_last_of(" ") - 2);

				contains[heldBag] = true;

				if (delim == -1)
					break;
				else
					substr.erase(0, (delim != -1 ? delim + 2 : substr.length()));
			}
			bags[bag] = contains;
		}
	}

	// "breadth first search" of bag "tree" we created.
	bool findGoldBag(std::unordered_map<std::string, bool> containedBags) {
		for (auto i = containedBags.begin(); i != containedBags.end(); i++) {
			if (i->first.compare("shiny gold") == 0)
				return true;
		}

		for (auto i = containedBags.begin(); i != containedBags.end(); i++) {
			if (findGoldBag(bags[i->first]))
				return true;
		}

		return false;
	}

	// counts gold bags
	int numOfBags(std::vector<std::string> lines) {
		loadBags(lines);
		int goldBags = 0;

		for (auto i = bags.begin(); i != bags.end(); i++) {
			if (i->first.compare("shiny gold") != 0 && findGoldBag(i->second)) {
				goldBags++;
				// std::cout << i->first << " has a gold bag." << std::endl;
			}
		}

		return goldBags;
	}

	int run() {
		try {
			std::vector<std::string> lines;
			parser::readLines("day07.txt", lines);
			std::cout << numOfBags(lines) << std::endl;
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
	return d7::run();
}