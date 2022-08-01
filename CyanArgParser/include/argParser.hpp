#include <string>
#include <list>
#include <map>
#include <any>

namespace cyan {
	namespace argParser {
		class Parser {
			template <typename T> class argument {
				std::string name;
				std::list<std::string> commandAliases;

				bool set = false;

				T* data = nullptr;
				T* defaultValue = nullptr;
				T* implicitValue = nullptr;

			public:
				argument<T>(std::string namei) {
					this->name = namei;
				}

				argument<T>* AddAlias(std::string alias) {
					std::list<std::string>::iterator it;
					it = commandAliases.end();
					commandAliases.insert(it, alias);

					return this;
				}
			};

			std::map<std::string, argument<std::any>*> argumentMap;

		public:
			template <typename T> argument<std::any> AddArgument(std::string name) {
				argument<T>* newArgument = new argument<T>(name);
				argumentMap.insert({ name, newArgument });

				return newArgument;
			}
		};
	}
}