#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

typedef unsigned int uint;

char* OpenFile(const char* where)
{
	std::ifstream file(where, std::ios::in | std::ios::binary | std::ios::ate);
	if (!file.is_open())
	{
		std::cout << "Unable to open file!\n";
		return nullptr;
	}
	uint size = file.tellg();
	char* result = new char[size + 1];
	file.seekg(0, std::ios::beg);
	file.read(result, size);
	file.close();
	result[size] = '\0';
	return result;
}