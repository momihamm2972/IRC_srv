
#include "../../include/ircserv/Client.hpp"

namespace ircserv
{
	int Client::PRIVMSG(std::string commandArgs)
	{
		std::cout << "commandName: [" << "PRIVMSG" << "]" << std::endl;
		std::cout << "commandArgs: [" << commandArgs << "]" << std::endl;
		return (0);
	};
};
