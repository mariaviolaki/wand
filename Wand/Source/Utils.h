#pragma once

#include <string>

namespace wand::Utils
{
	// Get a file path and return its contents as a string
	std::string ReadFile(const std::string& path);
}