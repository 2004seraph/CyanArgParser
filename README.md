# CyanArgParser - My Argument Parser
 
This is a simple C++17 argument parser made mainly for my own use as well as practice, hence its design and featureset will probably only appease me. I have however attempted to make the interface as intuitive as possible.

## How to use

You must always declare a parser instance, I like to enclose all of my code beneath my namespace `cyan` and then its library.

```cpp
#include "argParser.hpp"

//You will probably find it convienent to use a namespace alias
namespace cap = cyan::argParser;

int main(int argc, char* argv[]) {
	cap::Parser parser;
}
```

#### Creating and customizing arguments

You create arguments be calling the `AddArgument` function of the parser instance, you then may call any number of optional functions on the argument itself to customize it.

```cpp
parser.AddArgument("verboseLogging")//name of the setting
    ->AddAlias("--v")//how it can be accessed from the command line
    ->AddAlias("--verbose");//an alternate alias

parser.AddArgument("writeToFile")
    ->AddAlias("--f");
```

#### Input

Currently the only other option is `SetInput`, which means the argument is accompanied with a string value from the command line. You must supply a default value in case it is unset.

```cpp
parser.AddArgument("memoryLimit")
    ->AddAlias("--m")
    ->SetInput("2048");
```

Arguments with values are set by default using the tilde character (~).

```shell
app.exe --m~1024
```

You may change this character by using a parser constructor overload:

```cpp
int main(int argc, char* argv[]) {
	cap::Parser parser('=');
}
```

#### Parsing arguments

After declaring your arguments, you must then call the `Parse` function of the parser instance, passing in the main arguments. It will return an `std::map` of your schema that you can access.

```cpp
auto args = parser.Parse(argc, argv);

if (args.at("verboseLogging")->set) {
    std::cout << "verbose is set" << std::endl;
}

if (args.at("writeToFile")->set) {
    std::cout << "verbose is set" << std::endl;
}

if (args.at("memoryLimit")->set) {
    std::string val = std::any_cast<std::string>(args.at("memoryLimit")->GetValue());
    std::cout << "Memory: " << val << std::endl;
}
```

## Building

This project uses CMake, you can convert it to a visual studio project to build it using the CMake-gui program, nothing weird should happen, I've tested it.
