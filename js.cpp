
#include <map>
#include <string>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;


std::map<std::string, std::string> mappify2(std::string const& s)
{
	std::map<std::string, std::string> m;

	std::string::size_type start_pos = 0;
	std::string::size_type end_pos;
	std::string::size_type left_value;
	std::string::size_type right_value;
	
	while ((end_pos = s.find(':', start_pos)) != std::string::npos)
	{
		
		if ((left_value = s.find_first_not_of(": ", end_pos)) == std::string::npos)
			break;
		

		right_value = s.find('\n', left_value);
		
		m.emplace(s.substr(start_pos, end_pos - start_pos), s.substr(left_value, right_value - left_value));
		
		start_pos = right_value;
		if (start_pos != std::string::npos)
			++start_pos;
	}

	return m;
}

int main()
{
	std::ifstream jsonf("D://json//file.json");
	std::string s;
	if (jsonf.is_open())
	{
		
		while (getline(jsonf, s))
		{
			s.erase(std::remove(s.begin(), s.end(), '\"'), s.end());
			s.erase(std::remove(s.begin(), s.end(), '\{'), s.end());
			s.erase(std::remove(s.begin(), s.end(), '\,'), s.end());
			auto m = mappify2(s);

			
			
			for (auto const& p : m)

				std::cout  << p.first << " : " << p.second  << '\n';
			
		}

	}
	
}