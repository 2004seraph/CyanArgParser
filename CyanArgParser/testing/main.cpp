#include <iostream>

#include "../include/argParser.hpp"

namespace cap = cyan::argParser;

int main(int argc, char* argv[]) {
	cap::Parser parser;

	parser.AddArgument<bool>("verboseLogging").AddAlias("--v");

	return 0;
}