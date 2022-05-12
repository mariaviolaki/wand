#pragma once

namespace wand::Utils
{
	// Get a file path and return its contents as a string
	std::string ReadFile(const std::string& path);

	// Convert a given string to uppercase
	std::string ToUpper(const std::string& str);
	// Convert a given string to lowercase
	std::string ToLower(const std::string& str);

	// Search for an integer in an array and return its position
	int FindInArray(int num, const int* arr, unsigned int count);
}
