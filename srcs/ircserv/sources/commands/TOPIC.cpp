/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:51:24 by momihamm          #+#    #+#             */
/*   Updated: 2024/05/13 20:57:42 by ahaloui          ###   ########.fr       */
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
# include <unistd.h>

namespace ircserv
{
	int Client::TOPIC(std::string commandArgs)
	{
		// case TOPIC:
		// khas tkon operator il kan l mode dyal channel +t
		// TOPIC channel_name // show the channel topics
		// TOPIC channel_name topic
		// TOPIC channel_name :topic with spaces
		
		size_t pos;
		std::string channel_name;
		std::string new_topic;
		ircserv::Server *server;

		pos = commandArgs.find(' ');
		server = this->getServer();
		channel_name = commandArgs.substr(0, pos);
		ircserv::Channel *channel = server->getChannelByName(channel_name);
		if (channel->hasMode(CHANNEL_MODE_T) && !channel->isOperator(this->getNickname()))
		{
			ircserv::Client *client = server->getClientByNickname(this->getNickname());
			*client << "482" << " " << client->getNickname() << " " << channel->getName() << " :You're not channel operator" << ircserv::crlf;
			return (0);
		}

		pos = commandArgs.find(' ');
		if (pos == std::string::npos)
		{
			// dispaly channel topic
			ircserv::Channel *channel = server->getChannelByName(commandArgs);
			if (channel)
			{
				ircserv::Client *client = server->getClientByNickname(this->getNickname());
				*client << "332" << " " << client->getNickname() << " " << channel->getName() << " :" << channel->getTopic() << ircserv::crlf;
			}
			else
			{
				// error
				ircserv::Client *client = server->getClientByNickname(this->getNickname());
				*client << "403" << " " << client->getNickname() << " " << commandArgs << " :No such channel" << ircserv::crlf;
			}
			return (0);
		}


		if (!channel)
		{
			// error
			ircserv::Client *client = server->getClientByNickname(this->getNickname());
			*client << "403" << " " << client->getNickname() << " " << channel_name << " :No such channel" << ircserv::crlf;
			return (0);
		}
		else 
		{
			new_topic = commandArgs.substr(pos + 1);
			channel->setTopic(new_topic);
			ircserv::Client *client = server->getClientByNickname(this->getNickname());
			*client << "332" << " " << client->getNickname() << " " << channel->getName() << " :" << channel->getTopic() << ircserv::crlf;
		}
		return (0);
	};
};
