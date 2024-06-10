/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:50:28 by momihamm          #+#    #+#             */
/*   Updated: 2024/06/09 23:49:16 by momihamm         ###   ########.fr       */
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

	// std::string remove_all_with_spaces(std::string args)
	// {
	// 	std::string result;
	// 	bool inWord;

	// 	inWord = false;
	// 	for (std::size_t i = 0; i < args.length(); ++i) 
	// 	{
	// 		if (std::isspace(args[i])) 
	// 		{
	// 			if (!inWord) 
	// 			{
	// 				result += args[i];
	// 				inWord = true;
	// 			}
	// 		} 
	// 		else 
	// 		{
	// 			result += args[i];
	// 			inWord = false;
	// 		}
	// 	}
	// 	return result;
	// }
	
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
		ircserv::Client		*customer;
		std::string			chnlName;
		std::string			kickedOut;
		std::string			kickRaison;
		int puse;
		int word;

		puse = 0;
		word = 1;
		if (commandArgs.empty())
		{
			// https://modern.ircdocs.horse/#errneedmoreparams-461
			// "<client> <command> :Not enough parameters"
			*this << "461 " << kickedOut << " KICK" << " :Not enough parameters" << ircserv::crlf;
			return 1;
		}
		if (commandArgs.find(':') != std::string::npos)
		{
			kickRaison = commandArgs.substr (commandArgs.find(':') + 1);
			// std::cout << "@@" <<kickRaison << std::endl;
			commandArgs.erase (commandArgs.find(':') + 1);
		}
		commandArgs = remove_all_with_spaces(commandArgs);
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
			else if (word == 3 && commandArgs.find(':') == std::string::npos)
			{
				std::cout << "3333 " << commandArgs << std::endl;
				kickRaison = commandArgs.substr(0, puse);
				commandArgs.erase (0, puse + 1);
				word++;
			}
			if (word > 3)
				break ;
		}
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
					customer = srv->getClientByNickname (kickedOut);
					*customer << "Command to kick " << kickedOut << " from " << chnlName << ircserv::crlf;
				}
				else
				{
					// https://modern.ircdocs.horse/#kick-message
					// Command to kick John from #Finnish using "Speaking English" as the reason (comment).
					customer = srv->getClientByNickname (kickedOut);
					*customer << "Command to kick " << kickedOut << " from " << chnlName << " using `" << kickRaison << "' as the reason (comment)."<< ircserv::crlf;
				}
				// std::cout << "KICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICK\n";
				// vectorsolo (chnl->getKickedClients());
				// std::cout << "KICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICKKICK\n";
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
