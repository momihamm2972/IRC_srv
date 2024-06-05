/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 20:12:45 by ahabachi          #+#    #+#             */
/*   Updated: 2024/06/04 13:13:25 by momihamm         ###   ########.fr       */
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

#pragma once

# include "./Client.hpp"
# include "./Channel.hpp"
# include <iostream>
# include <map>
# include <arpa/inet.h>
# include <fcntl.h>

namespace ircserv
{
	class Server
	{
		private:
			int                                                       _socket_fd;
			struct sockaddr_in                                        _socket_addr;
			fd_set                                                    _readfds;
			fd_set                                                    _writefds;
			fd_set                                                    _currfds;
			int                                                       _port;
			std::string                                               _password;
			std::map<int, ircserv::Client>                            _clients;
			std::map<std::string /*channel_name*/, ircserv::Channel>  _channels;
			bool                                                      _running;

		public:
			Server();
			~Server();
			Server& operator=(Server const& other);
			Server(Server const& other);

			/* ****************** methods ****************** */
			int                                      getPort(void) const;
			int                                      getSocketFd(void) const;
			std::string                              getPassword(void) const;
			std::map<int, ircserv::Client>&          getClients(void);
			std::map<std::string, ircserv::Channel>& getChannels(void);

			ircserv::Client*                         getClientByNickname(const std::string nickname);
			ircserv::Client*                         createClientByFd(int clientfd);
			void                                     removeClientByFd(int clientfd);

			ircserv::Channel*                        getChannelByName(std::string channel_name);
			ircserv::Channel*                        createChannel(std::string channel_name, std::string operator_nickname);
			void                                     removeChannel(std::string channel_name);

			int                                      connect(void);
			bool                                     parse_port(std::string sport);
			bool                                     parse_password(std::string spass);
			bool                                     init(std::string sport, std::string spass);
			bool                                     start(void);
			void                                     fini(void);
	};
};
