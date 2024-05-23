/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabachi <ahabachi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 20:12:45 by ahabachi          #+#    #+#             */
/*   Updated: 2024/05/03 17:47:45 by ahabachi         ###   ########.fr       */
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

# include "../include/ircserv/Server.hpp"
# include "../include/ircserv/Client.hpp"
# include "../include/ircserv/tools.hpp"
# include <iostream>
# include <unistd.h>

namespace ircserv
{
	Server::Server()
	{
		this->_running = true;
	}
	Server::~Server()
	{

	}
	Server& Server::operator=(Server const& other)
	{
		(void)other;
		return (*this);
	}
	Server::Server(Server const& other)
	{
		*this = other;
	}

	/* ****************** methods ****************** */
	int Server::getPort(void) const
	{
		return (this->_port);
	}
	int Server::getSocketFd(void) const
	{
		return (this->_socket_fd);
	}
	std::string  Server::getPassword(void) const
	{
		return (this->_password);
	}

	std::map<int, ircserv::Client>& Server::getClients(void)
	{
		return (this->_clients);
	}
	std::map<std::string, ircserv::Channel>& Server::getChannels(void)
	{
		return (this->_channels);
	}

	ircserv::Client* Server::getClientByNickname(const std::string nickname)
	{
		for (
			std::map<int, ircserv::Client>::iterator i = this->_clients.begin();
			i != this->_clients.end();
			i++
		)
		{
			if (i->second.getNickname() == nickname)
			{
				return (&(i->second));
			}
		}
		return (NULL);
	}

	ircserv::Client *Server::createClientByFd(int clientfd)
	{
		this->removeClientByFd(clientfd);
		if (clientfd >= 0)
		{
			this->_clients[clientfd] = ircserv::Client();
			if (this->_clients[clientfd].init(this, clientfd) == false)
			{
				std::cout << "can't init client" << std::endl;
				this->removeClientByFd(clientfd);
				return (NULL);
			}
			return (&(this->_clients[clientfd]));
		}
		return (NULL);
	}

	void Server::removeClientByFd(int clientfd)
	{
		std::map<int, ircserv::Client>::iterator it = this->getClients().find(clientfd);
		if (it != this->getClients().end())
		{
			ircserv::Client& client = it->second;
			std::string nickname = client.getNickname();
			for (
				std::map<std::string, ircserv::Channel>::iterator it = this->getChannels().begin();
				it != this->getChannels().end();
				it++
			)
			{
				ircserv::Channel& channel = it->second;
				channel.removeClient(nickname);
			}
			this->getClients().erase(it);
		}
	}

	// Channel methods:
	ircserv::Channel* Server::getChannelByName(std::string channel_name)
	{
		std::map<std::string, ircserv::Channel>::iterator it = this->getChannels().find(channel_name);
		if (it != this->getChannels().end())
		{
			return (&(it->second));
		}
		return (NULL);
	}

	ircserv::Channel* Server::createChannel(std::string channel_name, std::string operator_nickname)
	{
		if (channel_name.length() > 0)
		{
			this->_channels[channel_name] = ircserv::Channel(channel_name, operator_nickname);
			return (&(this->_channels[channel_name]));
		}
		return (NULL);
	}

	void Server::removeChannel(std::string channel_name)
	{
		std::map<std::string, ircserv::Channel>::iterator it = this->getChannels().find(channel_name);
		if (it != this->getChannels().end())
		{
			this->getChannels().erase(it);
		}
	}

	int  Server::connect(void)
	{
		int                fd;
	    struct sockaddr_in client_addr;
	    int                client_addr_size;

	    client_addr_size = sizeof(client_addr);
	    // // Accept the new client connection
		fd = accept(this->getSocketFd(), (struct sockaddr *) &client_addr, (socklen_t *)&client_addr_size);
	    if (fd < 0)
	    {
	        return (-1);
	    }
		return (fd);
	}
	bool Server::parse_port(std::string sport)
	{
		sport = ircserv::trim(sport);
		if ((sport != "0") && ((sport.length() < 1) || (sport[0] <= '0')))
		{
			return (false);
		}
		int p = 0;
		for (size_t i = 0; i < sport.length(); i++)
		{
			if ((sport[i] < '0') || (sport[i] > '9'))
			{
				return (false);
			}
			p = 10 * p + (sport[i] - '0');
			if (p > 65535)
			{
				return (false);
			}
		}
		if ((p < IRCSERV_MIN_PORT_VALUE) || (p > IRCSERV_MAX_PORT_VALUE))
		{
			return (false);
		}
		this->_port = p;
		return (true);
	}
	bool Server::parse_password(std::string spass)
	{
		if ((spass.length() < 1) || (spass.length() < IRCSERV_MIN_PASSWORD_LENGTH) || (spass.length() > IRCSERV_MAX_PASSWORD_LENGTH))
		{
			return (false);
		}
		for (size_t i = 0; i < spass.length(); ++i)
		{
			if ((spass[i] <= ' ') || (spass[i] > '~'))
			{
				return (false);
			}
		}
		this->_password = spass;
		return (true);
	}
	bool Server::init(std::string sport, std::string spass)
	{
		if (parse_port(sport) == false)
		{
			return (false);
		}
		if (parse_password(spass) == false)
		{
			return (false);
		}
		this->_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
		if (this->_socket_fd < 0)
		{
			return (false);
		}
		int enable = 1;
		if (::setsockopt(this->_socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable)) < 0)
		{
			close(this->_socket_fd);
			return (false);
		}
		if (::setsockopt(this->_socket_fd, SOL_SOCKET, SO_NOSIGPIPE, &enable, sizeof(enable)) < 0)
		{
			close(this->_socket_fd);
			return (false);
		}
		ircserv::bzero(&_socket_addr, sizeof(_socket_addr));
		_socket_addr.sin_family      = AF_INET; 
		_socket_addr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
		_socket_addr.sin_port        = htons(this->getPort());
		if (bind(_socket_fd, (const struct sockaddr *)&_socket_addr, sizeof(_socket_addr)) < 0)
		{
			close(this->_socket_fd);
			return (false);
		}
		if (listen(_socket_fd, IRCSERV_BACKLOG) != 0)
		{
			close(this->_socket_fd);
			return (false);
		}
		if (fcntl(this->_socket_fd, F_SETFL, O_NONBLOCK) < 0)
		{
			close(this->_socket_fd);
			return (false);
		}
		FD_ZERO(&this->_currfds);
		FD_ZERO(&this->_readfds);
		FD_ZERO(&this->_writefds);
		FD_SET(this->_socket_fd, &this->_currfds);
		return (true);
	}
	bool Server::start(void)
	{
		while (this->_running)
		{
	        this->_readfds  = this->_currfds;
	        this->_writefds = this->_currfds;

	        if (select(FD_SETSIZE, &this->_readfds, &this->_writefds, NULL, NULL) < 0)
	        {
	        	return (false);
	        }
            for(int rfd = 0; rfd < FD_SETSIZE; rfd++)
            {
                if (FD_ISSET(rfd, &this->_readfds))
                {
                    if (rfd == this->getSocketFd())
                    {
                    	// accept new connection
						int clientfd = this->connect();
						if (clientfd >= 0)
						{
							this->createClientByFd(clientfd);
							FD_SET(clientfd, &this->_currfds);
						}
                    }
                    else
                    {
                    	// communicate
                    	if (this->_clients.count(rfd) > 0)
                    	{
	                    	if (this->_clients[rfd].communicate() == false)
	                    	{
								// can't communicate
								// delete client
	                    	}
                    	}
                    }
                }
            }
	    }
		return (false);
	}
	void Server::fini(void)
	{

	}
};
