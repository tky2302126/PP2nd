#pragma once
#include <iostream>
#include <vector>
#include <string>


class StringBuilder
{
private:
	std::vector<std::string> chunks;

public:
	StringBuilder& append( const std::string& str)
	{
		chunks.push_back(str);
		return *this;
	}

	std::string toString() const
	{
		std::string result;
		result.reserve(getTotalSize());
		for(const auto& chunk: chunks)
		{
			result += chunk;
		}
		return result;
	}

private:
	size_t getTotalSize() const
	{
		size_t total = 0;
		for(const auto& chunk: chunks )
		{
			total += chunk.size();
		}
		return total;
	}
};

