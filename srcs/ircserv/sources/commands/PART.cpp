/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PART.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:50:54 by momihamm          #+#    #+#             */
/*   Updated: 2024/06/09 04:29:17 by momihamm         ###   ########.fr       */
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
	std::string getNextOperator(std::vector<std::string> operaTors)
	{
		std::vector<std::string>::iterator it;

		it = operaTors.begin();
		it++;
		// protiction if no one avilible 
		if (it == operaTors.end())
			return NULL;
		return *it;
	}

	int	howManyOperators(std::vector<std::string> skepta)
	{
		std::vector<std::string>::iterator	it;
		int									cont;

		it = skepta.begin();
		cont = 0;
		while (it != skepta.end())
		{
			cont++;
			it++;
		}
		return cont;
	}

	void kmivectorsolo(std::vector<std::string> skepta)
	{
		std::vector<std::string>::iterator it;
		it = skepta.begin();
		while (it != skepta.end())
		{
			std::cout << "C                                               C//" << *it << std::endl;
			it++;
		}
	}

	std::vector<std::string> useAfterParssData(std::string str)
	{
		std::vector<std::string> 	input;
		int							puse;

		puse = str.find(',');
		while (puse != std::string::npos)
		{
			input.push_back(str.substr(0, puse));
			str.erase(0, puse + 1);
			puse = str.find(',');
		}
		if (puse == std::string::npos)
			input.push_back (str);
		return input;
	}
	
	int Client::PART(std::string commandArgs)
	{
		std::cout << "commandName: [" << "PART" << "]" << std::endl;
		std::cout << "commandArgs: [" << commandArgs << "]" << std::endl;

		// ######################################################################
		ircserv::Server		*srv;
		ircserv::Channel	*chnl;
		std::vector<std::string> data;
		std::vector<std::string>::iterator it;

		srv = this->getServer();
		if (commandArgs.empty())
		{
			// https://modern.ircdocs.horse/#errneedmoreparams-461
			// "<client> <command> :Not enough parameters"
			*this << "461 " << this->getNickname() << " <PART> :Not enough parameters" << ircserv::crlf;
			return 1;
		}
		// parss data
		
		data = useAfterParssData(commandArgs);
		kmivectorsolo(data);
		// check is the channel is valid
		it = data.begin();
		while (it != data.end())
		{
			chnl = srv->getChannelByName(*it);
			if (chnl)
			{
				// is operator;
				// if (chnl->isOperator(this->getNickname()))
				// {
				// 	// https://modern.ircdocs.horse/#part-message
				// 	// :dan-!d@localhost PART #test    ; dan- is leaving the channel #test
				// 	if (howManyOperators(chnl->getOperators()) > 1)
				// 		chnl->removeOperator (this->getNickname());
				// 	else
				// 	{
				// 		if (howManyOperators(chnl->getClients()) == 1)
				// 		{
				// 			// https://modern.ircdocs.horse/#part-message
				// 			// :dan-!d@localhost PART #test    ; dan- is leaving the channel #test
				// 			*this << this->getNickname() << " is leaving the channel " << *it << ircserv::crlf;
				// 			srv->removeChannel (*it);
				// 			return 0;
				// 		}
				// 		chnl->addOperator (getNextOperator(chnl->getClients()));
				// 		chnl->removeOperator (this->getNickname());
				// 	}
				// 	*this << this->getNickname() << " is leaving the channel " << *it << ircserv::crlf;
				// 	// return 0;
				// }
				if (chnl->isClient(this->getNickname()))
				{
					if (chnl->isOperator(this->getNickname()))
					{
						// https://modern.ircdocs.horse/#part-message
						// :dan-!d@localhost PART #test    ; dan- is leaving the channel #test
						if (howManyOperators(chnl->getOperators()) > 1)
							chnl->removeOperator (this->getNickname());
						else
						{
							if (howManyOperators(chnl->getClients()) == 1)
							{
								// https://modern.ircdocs.horse/#part-message
								// :dan-!d@localhost PART #test    ; dan- is leaving the channel #test
								*this << this->getNickname() << " is leaving the channel " << *it << ircserv::crlf;
								srv->removeChannel (*it);
								return 0;
							}
							chnl->addOperator (getNextOperator(chnl->getClients()));
							chnl->removeOperator (this->getNickname());
						}
						// *this << this->getNickname() << " is leaving the channel " << *it << ircserv::crlf;
						// return 0;
					}
					// https://modern.ircdocs.horse/#part-message
					// :dan-!d@localhost PART #test    ; dan- is leaving the channel #test
					chnl->removeClient(this->getNickname());
					*this << this->getNickname() << " is leaving the channel " << *it << ircserv::crlf;
					return 0;
				}
				else
				{
					// https://modern.ircdocs.horse/#errnotonchannel-442
					// "<client> <channel> :You're not on that channel"
					*this << "442 <" << this->getNickname() << "> <" << *it <<"> :You're not on that channel" << ircserv::crlf;
					return 0;
				}
			}
			else
			{
				// https://modern.ircdocs.horse/#errnosuchchannel-403
				// "<client> <channel> :No such channel"
				*this << "403 <" << this->getNickname() << "> <" << *it << "> :No such channel" << ircserv::crlf;
				return 1;
			}
			it++;
		}
		
		return (0);
	};
};
