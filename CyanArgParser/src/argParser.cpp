#include "include/argParser.hpp"

#include <iostream>
#include <string>

namespace cyan {
	namespace argParser {
		//PARSER CLASS

		Parser::Parser() {

		}
		Parser::Parser(char parserValueSeparator) {
			valueSeparator = parserValueSeparator;
		}

		Parser::argument* Parser::AddArgument(std::string name) {
			argument* newArgument = new argument(name);
			argumentMap.insert({ name, newArgument });

			return newArgument;
		}

		std::map<std::string, Parser::argument*> Parser::Parse(int argc, char* argv[], std::string& path) {
			path = std::string(argv[0]);
			return Parse(argc, argv);
		}
		std::map<std::string, Parser::argument*> Parser::Parse(int argc, char* argv[]) {

			std::vector<std::string> argumentVector(argv, argv + argc);

			//argumentVector.push_back("--f");
			//argumentVector.push_back("--v");

			//loop over every argument
			std::map<std::string, argument*>::iterator argIt;
			for (argIt = argumentMap.begin(); argIt != argumentMap.end(); ++argIt) {
				argument* currentArg = argIt->second;
				std::list<std::string> aliases = currentArg->GetAliases();

				//loop over every argument alias
				std::list<std::string>::iterator aliasIt;
				for (aliasIt = aliases.begin(); aliasIt != aliases.end(); ++aliasIt) {
					//loop over every argument input for this alias
					for (int i = 1; i < argumentVector.size(); i++) {
						//if the argument accepts an input, extract the part of the input that would be the argument alias, otherwise, the search term is the input
						std::string searchTerm = argumentVector[i];

						size_t inputSeparatorOffset = argumentVector[i].find(valueSeparator);

						if (currentArg->GetDefaultValue() != nullptr) {
							if (inputSeparatorOffset != std::string::npos) {
								searchTerm = argumentVector[i].substr(0, inputSeparatorOffset);
							}
						}
						else {
							//std::cout << aliasIt->c_str() << ": no input" << std::endl;
						}

						//std::cout << "Search term testing against " << aliasIt->c_str() << ": " << searchTerm << std::endl;

						//check if the current alias matches the search term
						if (searchTerm == aliasIt->c_str()) {
							//std::cout << "Search term matched against " << aliasIt->c_str() << ": " << searchTerm << std::endl;

							//if the argument has not already been set by an input
							if (currentArg->set == false) {
								//if the argument accepts an input
								if (currentArg->GetDefaultValue() != nullptr) {
									if (inputSeparatorOffset != std::string::npos) {
										std::string argValue = argumentVector[i].substr(inputSeparatorOffset + 1, argumentVector[i].length() - inputSeparatorOffset);
										currentArg->SetValue(argValue);
										//std::cout << "Value for " << aliasIt->c_str() << ": " << argValue << std::endl;
									}
									else {
										currentArg->SetValue(*currentArg->GetDefaultValue());
									}
								}

								currentArg->set = true;
							}

							argumentVector.erase(argumentVector.begin() + i);
						}
					}
				}
			}

			return argumentMap;
		}

		//ARGUMENT CLASS

		std::list<std::string> Parser::argument::GetAliases() {
			return commandAliases;
		}

		std::string* Parser::argument::GetDefaultValue() {
			return defaultValue;
		}

		void Parser::argument::SetValue(std::string valueIn) {
			value = valueIn;
		}

		std::any Parser::argument::GetValue() {
			return value;
		}

		Parser::argument::argument(const std::string namei) {
			this->name = namei;
		}

		Parser::argument* Parser::argument::AddAlias(const char* alias) {
			commandAliases.push_back(alias);

			//PrintList(commandAliases);

			return this;
		}

		Parser::argument* Parser::argument::SetInput(const char* value) {
			defaultValue = new std::string(value);

			return this;
		}
	}
}