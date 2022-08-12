#include <string>
#include <list>
#include <map>
#include <vector>

namespace cyan {
	namespace argParser {
		class Parser {
			class argument {
				std::string name;
				std::list<std::string> commandAliases;

				std::string* defaultValue = nullptr;

				std::string value;

			public:
				bool set = false;

				std::list<std::string> GetAliases();

				std::string* GetDefaultValue();

				void SetValue(std::string valueIn);

				std::string GetValue();

				argument(const std::string namei);

				argument* AddAlias(const char* alias);

				argument* SetInput(const char* value);
			};

			std::map<std::string, argument*> argumentMap;

			char valueSeparator = '~';

		public:
			Parser();
			Parser(char parserValueSeparator);

			argument* AddArgument(std::string name);

			std::map<std::string, argument*> Parse(int argc, char* argv[], std::string& path);
			std::map<std::string, argument*> Parse(int argc, char* argv[]);
		};
	}
}