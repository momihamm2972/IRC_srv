
#include "../../include/ircserv/Client.hpp"
#include "../../include/ircserv/Server.hpp"

namespace ircserv
{
	int Client::PASS(std::string commandArgs)
	{
		commandArgs = ircserv::trim(commandArgs);
		if (commandArgs.length() < 1)
		{
			// https://modern.ircdocs.horse/#errneedmoreparams-461
			*this << ":localhost 461 PASS :Not enough parameters" << ircserv::crlf;
			return (this->isAuthenticated());
		}
		if (this->isAuthenticated())
		{
			// https://modern.ircdocs.horse/#erralreadyregistered-462
			*this << ":localhost 462 PASS :You may not reregister" << ircserv::crlf;
		}
		else
		{
			if (this->_password.length() < 1)
			{
				if (commandArgs == this->getServer()->getPassword())
				{
					this->_password = commandArgs;
				}
				else
				{
					// https://modern.ircdocs.horse/#errpasswdmismatch-464
					*this << ":localhost 464 PASS :Password incorrect" << ircserv::crlf;
				}
			}
		}
		return (this->isAuthenticated());
	};
};
