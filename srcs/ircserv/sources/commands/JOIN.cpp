/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:50:01 by momihamm          #+#    #+#             */
/*   Updated: 2024/06/10 01:50:28 by momihamm         ###   ########.fr       */
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
	int	howManyWord(std::string str)
	{
		int	end;
		int	cont;
	
		end = str.find(',');
		cont = 0;
		while(end != std::string::npos)
		{
			end = str.find (',');
			if (end != std::string::npos)
				cont++;
			str.erase(0,end + 1);
		}
		if (end == std::string::npos && !str.empty())
			cont++;
		return cont;
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
	
	std::vector<std::pair<std::string, std::string> > parssAndUseData(std::string str1, std::string str2)
	{
		std::vector<std::pair<std::string, std::string> >			data;
		std::string													strC;
		std::string													strK;
		int															puseChnl;
		int															puseKey;
		int															indx;
		int															words;
		int															wordsK;

		if (howManyWord(str2) > howManyWord(str1))
		{
			std::cout << "ERROR NOT ENOGH PARAM\n";
			return data;
		}
		words = howManyWord (str1);
		wordsK = howManyWord (str2);
		indx = 0;
		std::cout << "num of words is " << words << std::endl;
		while (indx < words)
		{
			puseChnl = str1.find(',');
			if (puseChnl != std::string::npos)
			{
				std::cout << "it continse a comma\n";
				strC = str1.substr(0, puseChnl);
				if (strC.find ('#') == std::string::npos && strC.find ('&') == std::string::npos)
				{
					std::cout << "ERROR NOT VALID CHNL\n";
					break;
				}
				else
					strC.erase(0, 1);
				str1.erase(0, puseChnl + 1);
				puseKey = str2.find(',');
				if (puseKey != std::string::npos)
				{
					strK = str2.substr(0, puseKey);
					str2.erase(0, puseKey + 1);
				}
				else
					strK = str2;
				data.push_back(make_pair(strC,strK));
			}
			else
			{
				if (str1.find ('#') == std::string::npos && str1.find ('&') == std::string::npos)
				{
					std::cout << "ERROR NOT !@# VALID CHNL\n";
					break;
				}
				// else
				// 	str1.erase(0, 1);
				data.push_back(make_pair(str1,str2));
			}
			if (indx + 1 == wordsK)
				str2.erase(0);
			indx++;
		}
		return data;
	}
	
	std::string getKeyOfChennal(std::vector<std::pair<std::string, std::string> > data, std::string nameCh)
	{
		std::vector<std::pair<std::string, std::string> >::iterator it;
		std::string													str;

		std::cout << "assan i3lan !@$5 <<" << nameCh << ">>\n";
		it = data.begin();
		str = "notFond";
		while (it != data.end())
		{
			std::cout << "\n(((((((((((((((("<< it->first << "))))))))))))))))\n" << std::endl;
			if (nameCh == it->first)
			{
				std::cout << "netflix -> " << it->second << std::endl;
				return (it->second);
			}
			it++;
		}
		return str;
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

	size_t	howManyClientInTheChannel(std::vector<std::string> clients)
	{
		std::vector<std::string>::iterator it;
		size_t	cont;

		it = clients.begin();
		cont = 0;
		while (it != clients.end())
		{
			it++;
			cont++;
		}
		return cont;
	}

	int Client::JOIN(std::string commandArgs)
	{
		std::cout << "commandName: [" << "JOIN" << "]" << std::endl;
		std::cout << "commandArgs: [" << commandArgs << "]" << std::endl;
	
		std::vector<std::pair<std::string, std::string> >			data;
		std::vector<std::pair<std::string, std::string> >::iterator it;
		ircserv::Server												*srv;
		srv = this->getServer();
		std::map<std::string /*channel_name*/, ircserv::Channel>& list_of_chles = srv->getChannels();
		ircserv::Channel											*chnl;
		std::string													str1;
		std::string													str2;
		int															puse;
		int															puse0;

		if (commandArgs.empty())
		{
			// https://modern.ircdocs.horse/#errneedmoreparams-461
			// "<client> <command> :Not enough parameters"
			*this << "461 " << this->getNickname() << " <JOIN> :Not enough parameters" << ircserv::crlf;
			return 1;
		}
		puse = commandArgs.find(' ');
		if (puse != std::string::npos)
		{
			str1 = commandArgs.substr (0, puse);
			str2 = commandArgs.substr (puse + 1);
			data = parssAndUseData(str1, str2);
			// std::cout << "UM6P\n";
		}
		else
		{
			std::cout << "norm\n";
			str1 = commandArgs.substr(0);
			puse = commandArgs.find(',');
			if (puse != std::string::npos)
			{
				data = parssAndUseData(str1, "");
			}
			else
			{
				if (commandArgs.find ('#') == std::string::npos && commandArgs.find ('&') == std::string::npos)
				{
					// https://modern.ircdocs.horse/#errnosuchchannel-403
					// "<client> <channel> :No such channel"
					*this << "403 " << this->getNickname() << " " << chnl->getName() << " :No such channel" << ircserv::crlf;
					return 1;
				}
				// else
				// 	commandArgs.erase(0, 1);
				data.push_back(make_pair(commandArgs,""));
			}
		}
			it = data.begin();
			std::cout << "icame " << it->first << std::endl;
			
			while (it != data.end())
			{
				// std::cout << "indawhile\n";
				if (srv->getChannelByName(it->first))
				{
					std::cout << "exist  o tanchofo blanha replay \n";
					chnl = srv->getChannelByName(it->first);
					// work in invited
					// kicked
					if (chnl->getTopic().empty())
					{
						// https://modern.ircdocs.horse/#rplnotopic-331
						// "<client> <channel> :No topic is set"
						*this << "331 <" << this->getNickname() << "> <" << chnl->getName() << "> :No topic is set" << ircserv::crlf;
					}
					if (!(chnl->getTopic().empty()))
					{
						// https://modern.ircdocs.horse/#rpltopic-332
						// "<client> <channel> :<topic>"
						*this << "332 <" << this->getNickname() << "> <" << chnl->getName() << "> : " << chnl->getTopic() << ircserv::crlf;
					}
					if (chnl->isKicked(this->getNickname()) == true)
					{
						// https://modern.ircdocs.horse/#errbannedfromchan-474
						// "<client> <channel> :Cannot join channel (+b)"
						*this << "474 <" << this->getNickname() << "> <" << chnl->getName() << "> :Cannot join channel (+b)" << ircserv::crlf;
						return 1;
					}
					// 
					if (chnl->hasMode(CHANNEL_MODE_L) == true)
					{
						// std::cout << "131313131313311313131313131313131313133113131313131313131331131331313   >>" << chnl->getLimit() << "   >??"<<  howManyClientInTheChannel(chnl->getClients())<<"\n";
						if (chnl->getLimit() <= howManyClientInTheChannel(chnl->getClients()))
						{
							// https://modern.ircdocs.horse/#errchannelisfull-471
							// "<client> <channel> :Cannot join channel (+l)"
							*this << "471 <" << this->getNickname() << "> <" << chnl->getName() << "> :Cannot join channel (+l)" << ircserv::crlf;
							return 1;
						}
					}
					// if (!(chnl->getKey().compare("") == 0))
					// {
						if (it->second.compare(chnl->getKey()) != 0)
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
					if (chnl->isClient(this->getNickname()) != true)
					{
						// https://modern.ircdocs.horse/#rplendofnames-366
						//   "<client> <channel> :End of /NAMES list"
						chnl->addClient (this->getNickname());
					}
					std::cout << "OperatorOperatorOperatorOperatorOperatorOperatorOperatorOperatorOperatorOperator\n";
					solovectorprinting (chnl->getOperators());
					std::cout << "OperatorOperatorOperatorOperatorOperatorOperatorOperatorOperatorOperatorOperator\n";
					std::cout << "ClientsClientsClientsClientsClientsClientsClientsClientsClientsClientsClientsClients\n";
					solovectorprinting (chnl->getClients());
					std::cout << "ClientsClientsClientsClientsClientsClientsClientsClientsClientsClientsClientsClients\n";
				}
				else
				{
					// std::cout << "not exist **********"<<this->getNickname()<<"****************\n";
					chnl = srv->createChannel(it->first, this->getNickname());
					if (!it->second.empty())
					{
						chnl->setKey(it->second);
						// std::cout << "setkey\n";
					}
					list_of_chles.insert(std::make_pair(it->first, *chnl));
					std::cout << "OperatorOperatorOperatorOperatorOperatorOperatorOperatorOperatorOperatorOperator\n";
					solovectorprinting (chnl->getOperators());
					std::cout << "OperatorOperatorOperatorOperatorOperatorOperatorOperatorOperatorOperatorOperator\n";
					std::cout << "ClientsClientsClientsClientsClientsClientsClientsClientsClientsClientsClientsClients\n";
					solovectorprinting (chnl->getClients());
					std::cout << "ClientsClientsClientsClientsClientsClientsClientsClientsClientsClientsClientsClients\n";
					if (chnl)
						*this << "366 " << this->getNickname() << " " << chnl->getName() << " :End of /NAMES list" << ircserv::crlf;  
				}
				it++;
			}
			// printVector (data);
		std::cout << "\n\n\n\n";
		return (0);
	};
};



//  this is second request;
