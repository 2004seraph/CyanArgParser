#include <iostream>

#include "../include/argParser.hpp"

namespace cap = cyan::argParser;

int main(int argc, char* argv[]) {
	cap::Parser parser;
	parser.AddArgument("verboseLogging")
		->AddAlias("--v")
		->AddAlias("--verbose")
		->SetInput("2048");
	parser.AddArgument("logToFile")
		->AddAlias("--f");

	std::string path;
	auto args = parser.Parse(argc, argv, path);

	std::cout << path << std::endl;

	if (args.at("verboseLogging")->set) {
		std::cout << "verbose is set" << std::endl;
		std::string val = std::any_cast<std::string>(args.at("verboseLogging")->GetValue());
		std::cout << val << std::endl;
	}
	if (args.at("logToFile")->set) {
		std::cout << "logToFile is set" << std::endl;
	}

	return 0;
}