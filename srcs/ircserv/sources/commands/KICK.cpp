/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:50:28 by momihamm          #+#    #+#             */
/*   Updated: 2024/06/07 20:41:38 by momihamm         ###   ########.fr       */
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

namespace ircserv
{
	
	void vectorsolo(std::vector<std::string> skepta)
	{
		std::vector<std::string>::iterator it;
		it = skepta.begin();
		while (it != skepta.end())
		{
			std::cout << "C                                               C//" << *it << std::endl;
			it++;
		}
	}
	
	int Client::KICK(std::string commandArgs)
	{
		
		std::cout << "commandName: [" << "KICK" << "]" << std::endl;
		std::cout << "commandArgs: [" << commandArgs << "]" << std::endl;


		// ###########################################################################################
		ircserv::Channel	*chnl;
		ircserv::Server		*srv;
		std::string			chnlName;
		std::string			kickedOut;
		std::string			kickRaison;
		int puse;
		int word;

		// parss data;
		// std::vector<std::string> & listKicked = 
		puse = 0;
		word = 1;
		while (puse != std::string::npos)
		{
			puse = commandArgs.find(' ');
			if (word == 1)
			{
				chnlName = commandArgs.substr(0, puse);
				commandArgs.erase(0, puse + 1);
				word++;
			}
			else if (word == 2)
			{
				kickedOut = commandArgs.substr(0, puse);
				commandArgs.erase(0, puse + 1);
				word++;
			}
			else if (word == 3)
			{
				kickRaison = commandArgs.substr(0, puse);
				commandArgs.erase (0, puse + 1);
				word++;
			}
		}
		std::cout << "NAME OF CHANNEL = " << chnlName << std::endl;
		std::cout << "KICKE OUT = " << kickedOut << std::endl;
		std::cout << "KICK RAISON = " << kickRaison << std::endl;
		// now check is the input is correct;
		if (chnlName.empty() || kickedOut.empty())
		{
			// https://modern.ircdocs.horse/#errneedmoreparams-461
			// "<client> <command> :Not enough parameters"
			*this << "461 " << kickedOut << " KICK" << " :Not enough parameters" << ircserv::crlf;
			return 1;
		}
		if (chnlName.find ('#') == std::string::npos && chnlName.find ('&') == std::string::npos)
		{
			// https://modern.ircdocs.horse/#errbadchanmask-476
			// "<channel> :Bad Channel Mask"
			*this << "476 " << chnlName << " :Bad Channel Mask" << ircserv::crlf;
			return 1;
		}
		srv = this->getServer();
		chnl = srv->getChannelByName(chnlName);
		std::vector<std::string>& listKicked = chnl->getKickedClients();
		if (!chnl)
		{
			// https://modern.ircdocs.horse/#errnosuchchannel-403
			// "<client> <channel> :No such channel"
			*this << "403 " << kickedOut << " <" << chnlName << "> :No such channel" << ircserv::crlf;
			return 1;
		}
		if (chnl->isOperator(this->getNickname()) == true)
		{
			if (chnl->isClient(kickedOut) == true)
			{
				chnl->removeClient(kickedOut);
				listKicked.push_back(kickedOut);
				if (kickRaison.empty())
				{
					// https://modern.ircdocs.horse/#kick-message
					// Command to kick Matthew from #Finnish
					*this << "Command to kick " << kickedOut << " from " << chnlName << ircserv::crlf;
					// return 0;
				}
				else
				{
					// https://modern.ircdocs.horse/#kick-message
					// Command to kick John from #Finnish using "Speaking English" as the reason (comment).
					*this << "Command to kick " << kickedOut << " from " << chnlName << " using `" << kickRaison << "' as the reason (comment)."<< ircserv::crlf;
					// return 0;
				}
				std::cout << "KICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICK\n";
				vectorsolo (chnl->getKickedClients());
				std::cout << "KICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICK\n";
				return 0;
			}
			else
			{
				// https://modern.ircdocs.horse/#errusernotinchannel-441
				// "<client> <nick> <channel> :They aren't on that channel"
				*this << "441 <" << kickedOut << "> <" << kickedOut << "> <" << chnlName << "> :They aren't on that channel" << ircserv::crlf;
				return 1;
			}
		}
		else
		{
			// https://modern.ircdocs.horse/#errchanoprivsneeded-482
			// "<client> <channel> :You're not channel operator"
			*this << "482 " << kickedOut << " <" << chnlName << "> :You're not channel operator" << ircserv::crlf;
			return 1;
		}
		return (0);
	};
};
