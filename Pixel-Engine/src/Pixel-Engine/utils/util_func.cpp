#include "pepch.h"
#include "util_func.h"

namespace pe
{
	std::vector<std::string>& str_split(std::vector<std::string>& vector, std::string str, std::string delimiter) {
		vector.clear();
		size_t pos = 0;
		std::string token;
		while ((pos = str.find(delimiter)) != std::string::npos) {
			token = str.substr(0, pos);
			if(token!="") vector.push_back(token);
			str.erase(0, pos + delimiter.length());
		}
		if(str!="") vector.push_back(str);
		return vector;
	}

	
}