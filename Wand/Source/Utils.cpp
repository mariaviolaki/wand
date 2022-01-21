#include "Utils.h"

#include <iostream>
#include <fstream>
#include <sstream>

namespace wand::Utils // compile with C++17 at least
{
	std::string ReadFile(const std::string& path)
	{
		// Open a file at a specific path
		std::ifstream file(path);
		if (!file)
			std::cout << "Unable to open file at path: " << path << std::endl;
		
		std::string line;
		std::ostringstream stream;
		// Read each line in the file and store them together in a stream
		while (getline(file, line))
			stream << line << "\n";

		return stream.str();
	}
}
