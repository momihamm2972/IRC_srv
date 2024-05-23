/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabachi <ahabachi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:06:11 by ahabachi          #+#    #+#             */
/*   Updated: 2024/05/03 18:47:31 by ahabachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
/*                                                                            */
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

#pragma once

# include "./tools.hpp"
# include <iostream>
# include <sstream>

namespace ircserv
{
	class Server;
	class Channel;
	class Client
	{
		private:
			int                _fd;
			ircserv::Server*   _server;
			char               _buffer[IRCSERV_BUFFER_SIZE];
			std::string        _fullbuffer;
			std::string        _command;
			bool               _is_authenticated;
			std::ostringstream _stream;

			std::string        _nickname;
			std::string        _password;

			std::string        _username;
			std::string        _usermode;
			std::string        _hostname;
			std::string        _realname;
		public:
			Client();
			~Client();
			Client& operator=(Client const& other);
			Client(Client const& other);

			/* ****************** operators ****************** */
			Client& operator<<(int val);
			Client& operator<<(const std::string s);

			/* ****************** commands ****************** */
			int                INVITE(std::string commandArgs);
			int                JOIN(std::string commandArgs);
			int                KICK(std::string commandArgs);
			int                MODE(std::string commandArgs);
			int                NICK(std::string commandArgs);
			int                PART(std::string commandArgs);
			int                PASS(std::string commandArgs);
			int                PONG(std::string commandArgs);
			int                PRIVMSG(std::string commandArgs);
			int                TOPIC(std::string commandArgs);
			int                USER(std::string commandArgs);
			int                UNKNOWN(std::string commandArgs);

			/* ****************** methods ****************** */

			void               setNickname(std::string nickname);
			std::string        getNickname(void) const;
			int                getFd(void) const;
			ircserv::Server*   getServer(void);
			bool               isAuthenticated(void);
			bool               init(ircserv::Server* server, int fd);
			bool               communicate(void);
			void               check_command(void);
			int                parse_command(void);

	};
};
