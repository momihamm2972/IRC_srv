/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:06:11 by ahabachi          #+#    #+#             */
/*   Updated: 2024/06/11 18:00:01 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*  █████████            ██████████         ██████████         ██████████     */
/*  ██     ██                    ██                 ██         ██      ██     */
/*         ██                    ██                 ██         ██      ██     */
/*         ██                    ██                 ██                 ██     */
/*         ██            ██████████         ██████████                 ██     */
/*         ██                    ██                 ██                 ██     */
/*         ██                    ██                 ██                 ██     */
/*         ██                    ██                 ██                 ██     */
/*      ████████         ██████████         ██████████                 ██     */
/*                                                                            */
/* ************************************************************************** */

# include "../include/ircserv/tools.hpp"
# include "../include/ircserv/Client.hpp"
# include "../include/ircserv/Server.hpp"
# include <iostream>
# include <arpa/inet.h>

namespace ircserv
{
	Client::Client()
	{
		_fd         = -1;
		_server     = NULL;
		ircserv::bzero(_buffer, IRCSERV_BUFFER_SIZE);
		_fullbuffer = "";
		_command    = "";
		_is_authenticated = false;
		_stream.str("");
		_nickname   = "";
		_password   = "";
		_username   = "";
		_usermode   = "";
		_hostname   = "";
		_realname   = "";
	}

	Client::~Client()
	{
		_fd         = -1;
		_server     = NULL;
		ircserv::bzero(_buffer, IRCSERV_BUFFER_SIZE);
		_fullbuffer = "";
		_command    = "";
		_is_authenticated = false;
		_stream.str("");
		_nickname   = "";
		_password   = "";
		_username   = "";
		_usermode   = "";
		_hostname   = "";
		_realname   = "";
	}

	Client& Client::operator=(Client const& other)
	{
		if (this == &other)
		{
			return (*this);
		}
		_fd               = other._fd;
		_server           = other._server;
		_fullbuffer       = other._fullbuffer;
		_command          = other._command;
		_is_authenticated = other._is_authenticated;
		_nickname         = other._nickname;
		_password         = other._password;
		_username         = other._username;
		_usermode         = other._usermode;
		_hostname         = other._hostname;
		_realname         = other._realname;
		ircserv::memcpy(_buffer, other._buffer, IRCSERV_BUFFER_SIZE);
		_stream.str(other._stream.str());
		return (*this);
	}

	Client::Client(Client const& other)
	{
		*this = other;
	}

	/* ****************** operators ****************** */
	Client& Client::operator<<(int val)
	{
		this->_stream << val;
		return (*this);
	}
	Client& Client::operator<<(const std::string s)
	{
		this->_stream << s;
		if (s == ircserv::crlf)
		{
			std::string tmp = this->_stream.str();
			int flags = 0;
			::send(this->getFd(), tmp.c_str(), tmp.length(), flags);
			std::cout << "FD[" << this->getFd() << "][" << _nickname << "] RECIEVE: " << tmp;
			this->_stream.str("");
		}
		return (*this);
	}

	void Client::setNickname(std::string nickname)
	{
		this->_nickname = nickname;
	}

	std::string Client::getNickname(void) const
	{
		return (this->_nickname);
	}

	int Client::getFd(void) const
	{
		return (this->_fd);
	}

	ircserv::Server* Client::getServer(void)
	{
		return (this->_server);
	}

	bool Client::isAuthenticated(void)
	{
		if (this->_is_authenticated)
		{
			return (true);
		}
		if ((this->_nickname.length() > 0) && (this->_password.length() > 0) && (this->_username.length() > 0))
		{
			*this << ":localhost 001 " << this->getNickname() << " :Welcome to the ft_irc Internet Relay Chat Network "                 << this->getNickname() << ircserv::crlf;
			*this << ":localhost 002 " << this->getNickname() << " :Your host is localhost[176.58.122.119/6667], running version 1.0.0"                        << ircserv::crlf;
			*this << ":localhost 003 " << this->getNickname() << " :This server was created Tue May 07 2024 at 19:05:10 UTC"                                   << ircserv::crlf;
			this->_is_authenticated = true;
		}
		return (this->_is_authenticated);
	}

	bool Client::init(ircserv::Server* server, int fd)
	{
		this->_server = server;
		this->_fd = fd;
		return (true);
	}

	bool Client::communicate(void)
	{
		int size = recv(this->getFd(), this->_buffer, IRCSERV_BUFFER_SIZE, 0);
		if (size <= 0)
		{
			// client disconnected
			return (false);			
		}
		std::string message(this->_buffer, size);

		std::cout << "message: |" << message;
		this->_fullbuffer += std::string(this->_buffer, size);
		this->check_command();
		this->parse_command();
		return (true);
	}
	void Client::check_command(void)
	{
		this->_command = "";
		std::string &s = this->_fullbuffer;
		for (size_t i = 0; i < s.length(); i++)
		{
			if ((s[i] == '\n') || ((i + 1 < s.length()) && (s[i] == '\r') && (s[i + 1] == '\n')))
			{
				this->_command = ircserv::ltrim(s.substr(0, i));
				while ((i < s.length()) && (std::isspace(s[i])))
				{
					i = i + 1;
				}
				this->_fullbuffer = s.substr(i, this->_fullbuffer.length() - i);
			}
		}
	}
	int Client::parse_command(void)
	{
		size_t i = 0;
		for (i = 0; i < this->_command.length(); i++)
		{
			if (std::isspace(this->_command[i]))
			{
				break ;
			}
		}

	

		std::string commandName = ircserv::toupper(this->_command.substr(0, i));
		std::string commandArgs = ircserv::ltrim(this->_command.substr(i, this->_fullbuffer.length() - i));
		if (commandName == "INVITE")
			return (this->INVITE(commandArgs));
		if (commandName == "JOIN")
			return (this->JOIN(commandArgs));
		if (commandName == "KICK")
			return (this->KICK(commandArgs));
		if (commandName == "MODE")
			return (this->MODE(commandArgs));
		if (commandName == "NICK")
			return (this->NICK(commandArgs));
		if (commandName == "PART")
			return (this->PART(commandArgs));
		if (commandName == "PASS")
			return (this->PASS(commandArgs));
		if (commandName == "PONG")
			return (this->PONG(commandArgs));
		if (commandName == "PRIVMSG")
			return (this->PRIVMSG(commandArgs));
		if (commandName == "TOPIC")
			return (this->TOPIC(commandArgs));
		if (commandName == "USER")
			return (this->USER(commandArgs));
		return (this->UNKNOWN(commandArgs));
	}

};
