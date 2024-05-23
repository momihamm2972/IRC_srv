
# include "../../include/ircserv/Client.hpp"
# include "../../include/ircserv/tools.hpp"
# include <unistd.h>

namespace ircserv
{
	int Client::USER(std::string commandArgs)
	{
		if (commandArgs.length() < 1)
		{
			// https://modern.ircdocs.horse/#errneedmoreparams-461
			*this << ":localhost 461 USER :Not enough parameters" << ircserv::crlf;
			return (this->isAuthenticated());
		}
		if (this->isAuthenticated())
		{
			// https://modern.ircdocs.horse/#erralreadyregistered-462
			*this << ":localhost 462 USER :You may not reregister" << ircserv::crlf;
			return (this->isAuthenticated());
		}
		if (this->_password.length() < 1)
		{
			// https://modern.ircdocs.horse/#errnotregistered-451
			*this << ":localhost 451 USER :You have not registered" << ircserv::crlf;
			return (this->isAuthenticated());			
		}
		size_t i = 0;
		this->_username = "";
		for (; i < commandArgs.length(); i++)
		{
			if (ircserv::isspace(commandArgs[i]))
				break ;
			this->_username += commandArgs[i];
		}
		while ((i < commandArgs.length()) && (ircserv::isspace(commandArgs[i])))
			i++;
		this->_usermode = "";
		for (; i < commandArgs.length(); i++)
		{
			if (ircserv::isspace(commandArgs[i]))
				break ;
			this->_usermode += commandArgs[i];
		}
		while ((i < commandArgs.length()) && (ircserv::isspace(commandArgs[i])))
			i++;
		this->_hostname = "";
		for (; i < commandArgs.length(); i++)
		{
			if (ircserv::isspace(commandArgs[i]))
				break ;
			this->_hostname += commandArgs[i];
		}
		while ((i < commandArgs.length()) && (ircserv::isspace(commandArgs[i])))
			i++;
		if (i < commandArgs.length())
		{
			if (commandArgs[i] == ':')
			{
				this->_realname = commandArgs.substr(i + 1, commandArgs.length() - (i + 1));
			}
			else
			{
				this->_realname = "";
				for (; i < commandArgs.length(); i++)
				{
					if (ircserv::isspace(commandArgs[i]))
						break ;
					this->_realname += commandArgs[i];
				}
			}
		}
		return (this->isAuthenticated());
	};
};
