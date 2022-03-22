#pragma once

namespace wand::Utils
{
	// Get a file path and return its contents as a string
	std::string ReadFile(const std::string& path);

	// Convert a given string to uppercase or lowercase
	std::string ToUppercase(const std::string& str);
	std::string ToLowercase(const std::string& str);

	// Search for an integer in an array and return its position
	int FindInArray(int num, const int* arr, unsigned int count);
}
