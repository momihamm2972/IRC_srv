
#include "../../include/ircserv/Client.hpp"
# include <unistd.h>

namespace ircserv
{
	int Client::UNKNOWN(std::string commandArgs)
	{
		std::cout << "commandName: [" << "UNKNOWN" << "]" << std::endl;
		std::cout << "commandArgs: [" << commandArgs << "]" << std::endl;
		return (0);
	};
};
