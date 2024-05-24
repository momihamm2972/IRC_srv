/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:50:01 by momihamm          #+#    #+#             */
/*   Updated: 2024/05/24 11:56:04 by momihamm         ###   ########.fr       */
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
	
	void	printVector(std::vector<std::pair<std::string, std::string> > data)
	{
		std::vector<std::pair<std::string, std::string> >::iterator it;
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
	}
	
	std::vector<std::pair<std::string, std::string> > parssAndUseData(std::string str1, std::string str2)
	{
		std::vector<std::pair<std::string, std::string> >	data;
		std::string											strC;
		std::string											strK;
		int													puseChnl;
		int													puseKey;
		int													indx;
		int													words;
		int													wordsK;

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
					std::cout << "dkhel\n";
					str2.erase(0);
				}
			indx++;
		}
		// printVector(data);
		return data;
	}
	
	int Client::JOIN(std::string commandArgs)
	{
		std::cout << "commandName: [" << "JOIN" << "]" << std::endl;
		std::cout << "commandArgs: [" << commandArgs << "]" << std::endl;
	
		// !@@@@@@@@@@@@@@@@@@@@@@!
		std::vector<std::pair<std::string, std::string> >	data;
		ircserv::Server										*srv;
		ircserv::Channel									*chnl;
		std::string											str1;
		std::string											str2;
		int													puse;
		int													puse0;

		puse = commandArgs.find(' ');
		srv = this->getServer();
		if (puse != std::string::npos)
		{
			std::cout << "it's contin  a space\n";
			str1 = commandArgs.substr (0, puse);
			str2 = commandArgs.substr (puse + 1);
			data = parssAndUseData(str1, str2);
			printVector(data);
		}
		else
		{
			std::cout << "norm\n";
			str1 = commandArgs.substr(0);
			std::cout << ">>>>>>>>>>>>>>>>>>>>>>" << str1 << std::endl;
			if (str1.find ('#') == std::string::npos && str1.find ('&') == std::string::npos)
			{
				std::cout << "ERROR NOT %= VALID CHNL\n";
				// break;
			}
			else
				str1.erase(0, 1);
			std::cout << "@@@@@@@@@@@@@@@@@@@@@@@" << str1 << std::endl;
			// join simple 121232452353564645645757567457567573624573598237526583794562356723842467128947624897621894235; joini
			// check if exist or not;
			if (srv->getChannelByName(str1))
			{
				std::cout << "exist\n";
			}
			else
			{
				std::cout << "not exist\n";
			}
		}
		
		
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
		return (0);
	};
};
