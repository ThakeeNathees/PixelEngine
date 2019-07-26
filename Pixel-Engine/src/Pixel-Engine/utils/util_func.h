#pragma once

#include "..//Core.h"

namespace pe
{
	std::vector<std::string>& str_split(std::vector<std::string>& vector, std::string str, std::string delimiter = " ");
	

	template<typename T>
	void print_vector(const std::vector<T>& vector) {
		std::cout << "[ ";
		for (auto e : vector) {
			std::cout << e << ", ";
		}
		std::cout << "]" << std::endl;
	}

}