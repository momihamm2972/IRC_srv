/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:50:01 by momihamm          #+#    #+#             */
/*   Updated: 2024/06/05 15:44:45 by momihamm         ###   ########.fr       */
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
		// std::cout << "*******************************************************÷\n";
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
		// std::vector<std::pair<std::string, std::string> >::iterator it;
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
				else
					str1.erase(0, 1);
				data.push_back(make_pair(str1,str2));
			}
			if (indx + 1 == wordsK)
				{
					// std::cout << "dkhel\n";
					str2.erase(0);
				}
			indx++;
		}
		// printVector(data);
		return data;
	}
	
	std::string getKeyOfChennal(std::vector<std::pair<std::string, std::string> > data, std::string nameCh)
	{
		std::vector<std::pair<std::string, std::string> >::iterator it;
		std::string													str;
		// printVector (data);
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

		puse = commandArgs.find(' ');
		if (puse != std::string::npos)
		{
			str1 = commandArgs.substr (0, puse);
			str2 = commandArgs.substr (puse + 1);
			data = parssAndUseData(str1, str2);
			std::cout << "UM6P\n";
			// printVector(data);
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
					return 1;
				}
				else
					commandArgs.erase(0, 1);
				data.push_back(make_pair(commandArgs,""));
			}
		}
			it = data.begin();
			std::cout << "icame " << it->first << std::endl;
			
			while (it != data.end())
			{
				std::cout << "indawhile\n";
				if (srv->getChannelByName(it->first))
				{
					std::cout << "exist  o tanchofo blanha replay\n";
					// if (!chnl->getKey().empty())
					// {
						std::cout << "the channel has a key " << chnl->getKey() << "\n";
						
					// }
					// if (!getKeyOfChennal(data, commandArgs).empty())
					// {
					// 	std::cout << "~~~~~~~~~~~~~~~~~~~~`\n" << getKeyOfChennal(data, commandArgs) << std::endl;
					// }
					// if (it->second.empty())
					// 	std::cout << "no pass needed\n";
					// else
					// {
					// 	std::cout << "pass neded\n";
					// 	puse = commandArgs.find (' ');
					// 	it->second.compare(commandArgs.substr(puse + 1));
					// }
				}
				else
				{
					std::cout << "not exist\n";
					chnl = srv->createChannel(it->first, getNickname());
					if (!it->second.empty())
					{
						chnl->setKey(it->second);
						std::cout << "setkey\n";
					}
					list_of_chles.insert(std::make_pair(it->first, *chnl));
					// https://modern.ircdocs.horse/#rplendofnames-366
					//   "<client> <channel> :End of /NAMES list"
					if (chnl)
						*this << "366 " << this->getNickname() << " " << chnl->getName() << " :End of /NAMES list" << ircserv::crlf;  
				}
				it++;
			}
			// printMap(list_of_chles);
			printVector (data);
		// 	if (str1.find ('#') == std::string::npos && str1.find ('&') == std::string::npos)
		// 	{
		// 		std::cout << "ERROR NOT %= VALID CHNL\n";
		// 		// break;
		// 		return 1;
		// 	}
		// 	else
		// 		str1.erase(0, 1);
		// 	std::cout << "@@@@@@@@@#@@@@@@@@@@@@@@@" << str1 << std::endl;
		// 	// join simple 121232452353564645645757567457567573624573598237526583794562356723842467128947624897621894235; joini
		// 	// check if exist or not;
		// 	if (srv->getChannelByName(str1))
		// 	{
		// 		std::cout << "<<<<<<<\n";
		// 		std::cout << "exist  o tanchofo blanha replay\n";
		// 		it = data.begin();
		// 		if (it->second.empty())
		// 			std::cout << "no pass needed\n";
		// 		else
		// 		{
		// 			std::cout << "pass neded\n";
		// 			puse = commandArgs.find (' ');
		// 			it->second.compareommandArgs.(csubstr(puse + 1));
		// 		}
		// 	}
		// 	else
		// 	{
		// 		std::cout << "not exist\n";
		// 		chnl = srv->createChannel(str1,"mo7a");
		// 		// list_of_chles.insert(std::make_pair(str1, *chnl));
		// 		// https://modern.ircdocs.horse/#rplendofnames-366
		// 		//   "<client> <channel> :End of /NAMES list"
		// 		if (chnl)
		// 			*this << "366 " << this->getNickname() << " " << chnl->getName() << " :End of /NAMES list" << ircserv::crlf;
		// 		// else
		// 			// std::cout <<  
		// 	}
		// 	// *this << "482 " << this->getNickname() << " " << channel->getName() << " :You're not channel operator" << ircserv::crlf;
		// }
		// check if the channel is exit
		
	// ###########################################################################################################################
		// Start here!!
		// size_t	puse;
		// ircserv::Server		*srv;
		// ircserv::Channel	*canal;
		// ircserv::Client		entCli;
		// std::string	chnlName;
		// std::string theRestOf;
	
		// srv = this->getServer();
		// if (commandArgs.find(' ') != std::string::npos)
		// {
		// 	chnlName = commandArgs.substr(0,commandArgs.find(' '));
		// 	// check if the cnl is exist;
		// 	theRestOf = commandArgs.substr(commandArgs.find(' ') + 1);
		// 	std::cout << "name of cnl " << chnlName << " rest " << theRestOf << std::endl;
		// 	if (srv->getChannelByName(chnlName))
		// 		std::cout << "existe\n";
		// 	else
		// 	{
		// 		std::cout<< "not existe\n";
		// 	}
		// }
		// else if(commandArgs.find(',') != std::string::npos)
		// {
		// 	chnlName = commandArgs.substr(0,commandArgs.find(','));
		// 	theRestOf = commandArgs.substr(commandArgs.find(',') + 1);
		// 	std::cout << "name of cnl " << chnlName << " rest " << theRestOf << std::endl;;
		// }
		// else
		// {
		// 	std::cout << "\n\n\n\n\n\n\nkmi \n";
		// 	if (! commandArgs.empty())
		// 	{
		// 		canal = srv->getChannelByName(commandArgs);
		// 		if (canal != NULL)
		// 			std::cout << "existe\n";
		// 		else
		// 		{
		// 			std::cout << "not existe\n";
		// 			srv->createChannel(commandArgs, "mo7a");
		// 			canal = srv->getChannelByName(commandArgs);
		// 			if (canal->isOperator ("mo7a"))
		// 				std::cout << "yes mo7a is operator of " << canal->getName() << " channel\n";
		// 			else
		// 				std::cout << "NO mo7a is not the operator of " << canal->getName() << " channel\n";
		// 			srv->createClientByFd(87);
		// 			entCli.setNickname("smallx");
		// 			canal->addClient("smallx");
		// 			// std::vector<std::string> team;
		// 			// std::vector<std::string>::iterator yd = team.begin();
		// 			// while (yd != team.end())
		// 			// {
		// 			// 	std::cout << *yd << std::endl;
		// 			// 	yd++;
		// 			// }
		// 			// std::cout << "salina\n";
		// 		}
		// 	}
		// }
		std::cout << "\n\n\n\n";
		return (0);
	};
};



//  this is second request;
