#include "WandPCH.h"
#include "Utils.h"
#include "Logger.h"

namespace wand::Utils // compile with C++17 at least
{
	std::string ReadFile(const std::string& path)
	{
		// Open a file at a specific path
		std::ifstream file(path);
		if (!file)
			Logger::EngineLog("Utils:ReadFile", "Unable to open file at path: " + path + "\n");
		
		std::string line;
		std::ostringstream stream;
		// Read each line in the file and store them together in a stream
		while (getline(file, line))
			stream << line << "\n";

		return stream.str();
	}

	std::string ToUppercase(const std::string& str)
	{
		std::string newStr = str;
		transform(newStr.begin(), newStr.end(), newStr.begin(), ::toupper);
		return newStr;
	}

	std::string ToLowercase(const std::string& str)
	{
		std::string newStr = str;
		transform(newStr.begin(), newStr.end(), newStr.begin(), ::tolower);
		return newStr;
	}

	int FindInArray(int num, const int* arr, unsigned int count)
	{
		for (int i = 0; i < count; i++)
		{
			if (arr[i] == num)
				return i;
		}
		return -1;
	}
}
