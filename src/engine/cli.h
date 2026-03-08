#ifndef H_CLI
#define H_CLI

#include <string>
#include <iostream>
#include <sstream>

#include "strutils.h"

class cli_t
{
public:
	explicit cli_t() {}
	~cli_t() {}

	void run()
	{
		std::string buf;

		while (m_running == true)
		{
			std::getline(std::cin, buf);
			string_lower(buf);

			if (buf == "exit")
			{
				if (user_confirms() == false)
					continue;

				m_running = false;
				break;
			}
		}
	}

	auto user_confirms() -> bool
	{
		std::cout << "Please indicate \"Y\" to continue, or press \"ENTER\" to return" << std::endl;

		std::string buf;
		std::getline(std::cin, buf);
		string_lower(buf);

		if (in_str(buf, "y"))
		{
			return true;
		}

		return false;
	}

private:
	bool m_running = true;
};

#endif // H_CLI