
#include "../../include/ircserv/Client.hpp"

namespace ircserv
{
	int Client::MODE(std::string commandArgs)
	{
		std::cout << "commandName: [" << "MODE" << "]" << std::endl;
		std::cout << "commandArgs: [" << commandArgs << "]" << std::endl;
		return (0);
	};
};
