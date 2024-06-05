/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   INVITE.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:49:53 by momihamm          #+#    #+#             */
/*   Updated: 2024/05/14 22:33:23 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
#include "../../include/ircserv/Client.hpp"
#include "../../include/ircserv/Server.hpp"
#include "../../include/ircserv/Channel.hpp"
# include <unistd.h>

namespace ircserv
{
	int Client::INVITE(std::string commandArgs)
	{
		// case INVITE:
		// khas tkon operator
		// INVITE nickname <channel>
		
		std::string nickname;
		std::string channel_name;
		ircserv::Server *server;
		ircserv::Channel *channel;
		ircserv::Client *client;
		size_t pos;
		commandArgs = ircserv::trim(commandArgs);
		server = this->getServer();
		pos = commandArgs.find(' ');
		
		if (pos == std::string::npos)
		{
			// https://modern.ircdocs.horse/#errneedmoreparams-461
			*this << "461 " << this->getNickname() << " INVITE :Not enough parameters" << ircserv::crlf;
			return (0);
		}
		nickname = commandArgs.substr(0, pos);
		channel_name = ircserv::trim(commandArgs.substr(pos + 1));

		if (channel_name.find(' ') != std::string::npos)
		{
			*this << "461 " << this->getNickname() << " INVITE :Too many parameters" << ircserv::crlf;
			return (0);
		}
		/************************************************************/
		channel = server->getChannelByName(channel_name);
		if (!channel)
		{
			*this << "403 " << this->getNickname() << " " << channel_name << " :No such channel" << ircserv::crlf;
			return (0);
		}
		/************************************************************/
		
		if (channel->isOperator(this->getNickname()) == false)
		{
			*this << "482 " << this->getNickname() << " :You're not channel operator" << ircserv::crlf;
			return (0);
		}
		/***********************************************************/
		client = server->getClientByNickname(nickname);
		if (!client)
		{
			*this << "401 " << this->getNickname() << " " << nickname << " :No such nick" << ircserv::crlf;
			return (0);
		}
		if (channel->isClient(nickname))
		{
			// https://modern.ircdocs.horse/#erruseronchannel-443
			*this << "443 " << this->getNickname() << " " << nickname << " " << channel_name << " :is already on channel" << ircserv::crlf;
			return (0);
		}
		if (channel->isInvited(nickname))
		{
			*this << "443 " << this->getNickname() << " " << nickname << " " << channel_name << " :is already on channel" << ircserv::crlf;
			return (0);
		}
		channel->inviteClient(nickname);
		*client << ":" << this->getNickname() << " INVITE " << nickname << " " << channel_name << ircserv::crlf;
		return (0);
	};
};
