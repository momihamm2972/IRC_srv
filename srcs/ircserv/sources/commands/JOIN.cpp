/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:50:01 by momihamm          #+#    #+#             */
/*   Updated: 2024/06/11 22:24:48 by momihamm         ###   ########.fr       */
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
	std::string client_of_channel(std::vector<std::string> channel)
	{
		std::vector<std::string>::iterator it;
		std::string str;

		it = channel.begin();
		str = "";
		while (it != channel.end())
		{
			str += "@";
			str += *it;
			it++;
		}
		return str;
	}
	
	void	printMap(std::map<std::string , ircserv::Channel>  mAp)
	{
		std::map<std::string , ircserv::Channel>::iterator ir;
		ir = mAp.begin();
		std::cout << "MAPMAPMAPMAPMAPMAPMAPMAPMAPMAPMAPMAPMAPMAPMAPMAPMAP\n";
		while (ir != mAp.end())
		{
			std::cout << ir->first << std::endl;
			ir++;
		}
		std::cout << "MAPMAPMAPMAPMAPMAPMAPMAPMAPMAPMAPMAPMAPMAPMAPMAPMAP\n";
	}
	
	void	printVector(std::vector<std::pair<std::string, std::string> > data)
	{
		std::vector<std::pair<std::string, std::string> >::iterator it;
		std::cout << "VECTORVECTORVECTORVECTORVECTORVECTORVECTORVECTOR\n";
		it = data.begin();
		while (it != data.end())
		{
			std::cout << it->first << "->";
			if (it->second.empty())
				std::cout << "NO KEY" << std::endl;
			else
				std::cout << it->second << std::endl;
			it++;
		}
		std::cout << "VECTORVECTORVECTORVECTORVECTORVECTORVECTORVECTOR\n";
	}

	void solovectorprinting(std::vector<std::string> skepta)
	{
		std::vector<std::string>::iterator it;
		it = skepta.begin();
		while (it != skepta.end())
		{
			std::cout << "C                                               C//" << *it << std::endl;
			it++;
		}
	}


	int Client::JOIN(std::string commandArgs)
	{
		std::cout << "commandName: [" << "JOIN" << "]" << std::endl;
		std::cout << "commandArgs: [" << commandArgs << "]" << std::endl;
		std::string commandArgsCopy = commandArgs;
		std::vector<std::string> channel_names;
		std::vector<std::string> channel_keys;
		// std::string cmd = "JOIN";

		

// ########
		ircserv::Server												*srv;
		srv = this->getServer();
		std::map<std::string /*channel_name*/, ircserv::Channel>& list_of_chles = srv->getChannels();
		ircserv::Channel											*chnl;
		std::string													str1;
		std::string													str2;
		int															puse;
		int															puse0;

		// if (commandArgs.length() == 1 && commandArgs[0] == '#')
		if (commandArgs.empty() || (commandArgs.length() == 1 && commandArgs[0] == '#'))
		{
			// https://modern.ircdocs.horse/#errneedmoreparams-461
			// "<client> <command> :Not enough parameters"
			*this << "461 " << this->getNickname() << " JOIN :Not enough parameters" << ircserv::crlf;
			return 1;
		}
		// check errors befor joining;
		ircserv::splitWords(channel_names, commandArgsCopy);
		ircserv::splitWords(channel_keys , commandArgsCopy);
		for(size_t i = 0; i < channel_names.size(); i++)
		{
			std::string channel_name = channel_names[i];
			std::string channel_key = "";
			if (channel_name.empty())
			{
				// https://modern.ircdocs.horse/#errbadchanmask-476
				  // "<channel> :Bad Channel Mask"
				*this << "476 " << channel_name << " :Bad Channel Mask" << ircserv::crlf;
				continue ;
			}
			if (i < channel_keys.size())
			{
				channel_key = channel_keys[i];
			}
			
				// std::cout << "indawhile\n";
				if (srv->getChannelByName(channel_name))
				{
					std::cout << "exist  o tanchofo blanha replay \n";
					chnl = srv->getChannelByName(channel_name);
					if (chnl->isClient(this->getNickname()))
					{
						// https://modern.ircdocs.horse/#erruseronchannel-443
						// "<client> <channel> :is already on channel"
						*this << "443 " << this->getNickname() << " " << chnl->getName() << " :is already on channel" << ircserv::crlf;
						return 0;
					}
					if (chnl->hasMode(CHANNEL_MODE_L) == true)
					{
						if (chnl->getLimit() <= chnl->getClients().size())
						{
							// https://modern.ircdocs.horse/#errchannelisfull-471
							// "<client> <channel> :Cannot join channel (+l)"
							*this << "471 " << this->getNickname() << " " << chnl->getName() << " :Cannot join channel (+l)" << ircserv::crlf;
							return 1;
						}
					}
					// work in invited
					// kicked
					if (chnl->getTopic().empty())
					{
						// https://modern.ircdocs.horse/#rplnotopic-331
						// "<client> <channel> :No topic is set"
						*this << "331 " << this->getNickname() << " " << chnl->getName() << " :No topic is set" << ircserv::crlf;
					}
					else
					{
						// https://modern.ircdocs.horse/#rpltopic-332
						// "<client> <channel> :<topic>"
						// topicRep = ":IRCServer 332 " + clientStates[clientSocket].nickname + " " + channel + " " + Topic +"\r\n" ;
						*this << "332 " << this->getNickname() << " " << chnl->getName() << " " << chnl->getTopic() << ircserv::crlf;
					}
					
					// 
					
					// if (!(chnl->getKey().compare("") == 0))
					// {
						if (channel_key.compare(chnl->getKey()) != 0)
						{
							// https://modern.ircdocs.horse/#errbadchannelkey-475
							// "<client> <channel> :Cannot join channel (+k)"
							*this << "475 <" << this->getNickname() << "> <" << chnl->getName() << "> :Cannot join channel (+k)" << ircserv::crlf;
							return 1;
						}
					// }
					if (chnl->hasMode(CHANNEL_MODE_I) == true)
					{
						std::cout << "DKHEL\n";
						if (!chnl->isInvited (this->getNickname()))
						{
							// https://modern.ircdocs.horse/#errinviteonlychan-473
							// "<client> <channel> :Cannot join channel (+i)"
							*this << "473 " << this->getNickname() << " " << chnl->getName() << " :Cannot join channel (+i)" << ircserv::crlf;
							return 1;
						}
					}
					// work in invited
					// if (chnl->isClient(this->getNickname()) != true)
					// {
						// https://modern.ircdocs.horse/#rplendofnames-366
						//   "<client> <channel> :End of /NAMES list"
						// std::string broadcastMessage = ":" + client.getNickname() + "!" + client.getUsername() + "@" + this->getServerHostName() + " JOIN " + channelName + "\r\n";
						// *this << ":" << this->getNickname() << "!" << this->_username << "@" << this->_hostname << " JOIN " << chnl->getName() << ircserv::crlf;
					// 	chnl->addClient (this->getNickname());
					// // }
					// std::cout << "OperatorOperatorOperatorOperatorOperatorOperatorOperatorOperatorOperatorOperator\n";
					// solovectorprinting (chnl->getOperators());
					// std::cout << "OperatorOperatorOperatorOperatorOperatorOperatorOperatorOperatorOperatorOperator\n";
					// std::cout << "ClientsClientsClientsClientsClientsClientsClientsClientsClientsClientsClientsClients\n";
					// solovectorprinting (chnl->getClients());
					// std::cout << "ClientsClientsClientsClientsClientsClientsClientsClientsClientsClientsClientsClients\n";
					*this << ":" << this->getNickname() << "!" << this->_username << "@" << this->_hostname << " JOIN " << chnl->getName() << ircserv::crlf;
					
					// if (chnl->hasMode() == true)
					// {
					// 	*this << "324 " <<  this->getNickname() << " " << chnl->getName() << " + " << 
					// }
					*this << "353 " << this->getNickname() << " = " << chnl->getName() << " :" << client_of_channel(chnl->getClients()) << ircserv::crlf;
					*this << "366 " << this->getNickname() << " = " << chnl->getName() << " :End of /NAMES list." << ircserv::crlf;
				}
				else
				{
					std::cout << "not exist **********"<<this->getNickname()<<"****************\n";
					chnl = srv->createChannel(channel_name, this->getNickname());
					if (!channel_key.empty())
					{
						chnl->setKey(channel_key);
						// std::cout << "setkey\n";
					}
					list_of_chles.insert(std::make_pair(channel_name, *chnl));
					// https://modern.ircdocs.horse/#rplendofnames-366
					//   "<client> <channel> :End of /NAMES list"
					
// void printChanneljoin(std::map<int, ClientState>& clientStates, std::string Topic , int clientSocket, const std::string& channel ,std::string chanelClient, std::string mode)
// {
// 	std::string reply = ":" +  clientStates[clientSocket].nickname + "!" + clientStates[clientSocket].username + "@" + clientStates[clientSocket].hostname + " JOIN " + channel+ "\r\n";
// 	send(clientSocket, reply.c_str() , reply.size(), 0);
// 	if (mode != "")
// 	{
// 		std::string modechan = ":IRCServer 324 " + clientStates[clientSocket].nickname + " " + channel + " +" + mode + "\r\n" ;
// 		send(clientSocket, modechan.c_str() , modechan.size(), 0);
// 	}
// 	std::string topicRep = ":IRCServer 332 " + clientStates[clientSocket].nickname + " " + channel + " " + Topic +"\r\n" ;
// 	send(clientSocket, topicRep.c_str() , topicRep.size(), 0);
// 	std::string adminMsg = ":IRCServer 353 " + clientStates[clientSocket].nickname + " = " + channel + " :" + chanelClient +"\r\n" ;
// 	send(clientSocket, adminMsg.c_str() , adminMsg.size(), 0);
// 	std::string endOfList = ":IRCServer 366 " + clientStates[clientSocket].nickname + " = " + channel + " :End of /NAMES list.\r\n" ;
// 	send(clientSocket, endOfList.c_str() , endOfList.size(), 0);
// }
					
					*this << ":" + this->getNickname() + "!" + this->_username + "@" + this->_hostname + " JOIN " + chnl->getName()  + "\r\n";
					
					// if (chnl->hasMode() == true)
					// {
					// 	*this << "324 " <<  this->getNickname() << " " << chnl->getName() << " + " << 
					// }
					*this << "353 " + this->getNickname() + " = " + chnl->getName() + " :" + client_of_channel(chnl->getClients())  + "\r\n";
					*this << "366 " + this->getNickname() + " = " + chnl->getName() + " :End of /NAMES list.\r\n";
					// std::cout << "OperatorOperatorOperatorOperatorOperatorOperatorOperatorOperatorOperatorOperator\n";
					// solovectorprinting (chnl->getOperators());
					// std::cout << "OperatorOperatorOperatorOperatorOperatorOperatorOperatorOperatorOperatorOperator\n";
					// std::cout << "ClientsClientsClientsClientsClientsClientsClientsClientsClientsClientsClientsClients\n";
					// solovectorprinting (chnl->getClients());
					// std::cout << "ClientsClientsClientsClientsClientsClientsClientsClientsClientsClientsClientsClients\n";
					// *this << "366 " << this->getNickname() << " " << chnl->getName() << " :End of /NAMES list" << ircserv::crlf;  
				}
		}
			// printVector (data);
		std::cout << "\n\n\n\n";
		return (0);
	};
};



//  this is second request;
