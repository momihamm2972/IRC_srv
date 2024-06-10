/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:51:24 by momihamm          #+#    #+#             */
/*   Updated: 2024/06/10 01:36:59 by momihamm         ###   ########.fr       */
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
#include <vector>
#include <iostream>
#include <unistd.h>

namespace ircserv
{
	
	
	int Client::TOPIC(std::string commandArgs)
	{
		// case TOPIC:
		// khas tkon operator il kan l mode dyal channel +t
		// TOPIC channel_name // show the channel topics
		// TOPIC channel_name topic
		// TOPIC channel_name :topic with spaces
		
		std::cout << "commandName: [" << "TOPIC" << "]" << std::endl;
		std::cout << "commandArgs: [" << commandArgs << "]" << std::endl;

		// ###########################################################################
		
		ircserv::Server		*srv;
		ircserv::Channel	*chnl;
		std::string		chnlName;
		std::string		chnlTopic;
		int					omlawet;

		if (commandArgs.find(':') != std::string::npos)
		{
			chnlName = commandArgs.substr(0, commandArgs.find(':'));
			chnlTopic = commandArgs.substr(commandArgs.find(':') + 1);
			chnlName = ircserv::remove_all_with_spaces(chnlName);
			if (chnlName.find(' ') != std::string::npos)
				chnlName = chnlName.substr(0, chnlName.find(' '));
			omlawet = 0;
		}
		else if (commandArgs.find(' ') != std::string::npos)
		{
			chnlName = commandArgs.substr(0, commandArgs.find(' '));
			chnlTopic = commandArgs.substr(commandArgs.find(' ') + 1);
			chnlTopic = ircserv::trim(chnlTopic);
			chnlName = ircserv::remove_all_with_spaces(chnlName);
			chnlTopic = ircserv::remove_all_with_spaces(chnlTopic);
			if (chnlTopic.find(' ') != std::string::npos)
				chnlTopic = chnlTopic.substr(0, chnlTopic.find(' '));
			omlawet = 1;
		}
		else
		{
			chnlName = commandArgs.substr(0 , commandArgs.length());
			omlawet = 1;
		}
		std::cout << "Name = " << chnlName << "#" << std::endl;
		std::cout << "Topic = " << chnlTopic << "!" << std::endl;

		srv = this->getServer();
		chnl = srv->getChannelByName(chnlName);
		if (chnlName.empty())
		{
			// https://modern.ircdocs.horse/#errneedmoreparams-461
			// "<client> <command> :Not enough parameters"
			*this << "461 <" << this->getNickname() << "> <TOPIC> :Not enough parameters" << ircserv::crlf;
			return 1;
		}
		if (chnl)
		{
			if (chnl->hasMode(CHANNEL_MODE_T) == true)
			{
				if (chnl->isOperator(this->getNickname()) == true)
				{
					if (!(chnlTopic.empty()))
					{
						// https://modern.ircdocs.horse/#topic-message
						// TOPIC #test :New topic          ; Setting the topic on "#test" to "New topic".
						chnl->setTopic (chnlTopic);
						*this << "Setting the topic on `" << chnlName << "' to" << chnlTopic << ircserv::crlf;
						return 0;
					}
					else if (chnlTopic.empty() && omlawet == 1)
					{
						// https://modern.ircdocs.horse/#topic-message
						// TOPIC #test :                   ; Clearing the topic on "#test"
						chnl->setTopic ("");
						*this << "Clearing the topic on `" << chnlName << "'" << ircserv::crlf;
						return 0;
					}
					else if (chnlTopic.empty())
					{
						// https://modern.ircdocs.horse/#topic-message
						// TOPIC #test                     ; Checking the topic for "#test"
						if (chnl->getTopic().empty())
						{
							*this << "The topic for `" << chnlName << "' is NONE!!" << ircserv::crlf;
							return 0;
						}
						*this << "The topic for `" << chnlName << "' is " << chnl->getTopic() << ircserv::crlf;
						return 0;
					}
				}
				else
				{
					// https://modern.ircdocs.horse/#errchanoprivsneeded-482
					//  "<client> <channel> :You're not channel operator"
					*this << "482 <" << this->getNickname() << "> <TOPIC> :You're not channel operator" << ircserv::crlf;
					return 1;
				}
			}
			else if (chnl->isClient(this->getNickname()) == true)
			{
				if (!(chnlTopic.empty()))
				{
					// https://modern.ircdocs.horse/#topic-message
					// TOPIC #test :New topic          ; Setting the topic on "#test" to "New topic".
					chnl->setTopic (chnlTopic);
					*this << "Setting the topic on `" << chnlName << "' to" << chnlTopic << ircserv::crlf;
					return 0;
				}
				else if (chnlTopic.empty() && omlawet == 1)
				{
					// https://modern.ircdocs.horse/#topic-message
					// TOPIC #test :                   ; Clearing the topic on "#test"
					chnl->setTopic ("");
					*this << "Clearing the topic on `" << chnlName << "'" << ircserv::crlf;
					return 0;
				}
				else if (chnlTopic.empty())
				{
					// https://modern.ircdocs.horse/#topic-message
					// TOPIC #test                     ; Checking the topic for "#test"
					if (chnl->getTopic().empty())
					{
						*this << "The topic for `" << chnlName << "' is NONE!!" << ircserv::crlf;
						return 0;
					}
					*this << "The topic for `" << chnlName << "' is " << chnl->getTopic() << ircserv::crlf;
					return 0;
				}
			}
			else
			{
				// https://modern.ircdocs.horse/#errnotonchannel-442
				// "<client> <channel> :You're not on that channel"
				*this << "442 <" << this->getNickname() << "> <"<< chnlName << "> :You're not on that channel" << ircserv::crlf;
				return 1;
			}
		}
		else
		{
			// https://modern.ircdocs.horse/#errnosuchchannel-403
			// "<client> <channel> :No such channel"
			*this << "461 <" << this->getNickname() << "> <"<< chnlName << "> :No such channel" << ircserv::crlf;
			return 1;
		}
		
		return (0);
	};
};
