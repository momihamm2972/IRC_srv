/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JOIN.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:50:01 by momihamm          #+#    #+#             */
/*   Updated: 2024/05/23 19:36:57 by momihamm         ###   ########.fr       */
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
	
	std::vector<std::string> mySplit(std::string str, std::string del)
	{
		std::vector<std::string>            towD;
		std::vector<std::string>::iterator  it;
		int                                 indx;
		int                                 valu;

		indx = 0;
		while (indx <= str.length())
		{
			valu = str.find (del);
			if (valu != std::string::npos)
			{
				towD.push_back (str.substr(0, valu));
				str.erase(0, valu + 1);
				indx = 0;
			}
				indx++;
		}
		if (!str.empty())
			towD.push_back (str.substr(0,str.length()));
		it = towD.begin();
		while (it != towD.end())
		{
			std::cout << *it << std::endl;
			it++;
		}
		return (towD);
	}
	// check how many of the key and the chanels;

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
			std::cout << it->first << "->" << it->second << std::endl;
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

		// work in the str1
		// how many word
		if (howManyWord(str2) > howManyWord(str1))
		{
			std::cout << "ERROR NOT ENOGH PARAM\n";
			return data;
		}
		// @@@@@@@@@@@@@
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
				data.push_back(make_pair(str1,str2));
			}
			if (indx + 1 == wordsK)
				{
					std::cout << "dkhel\n";
					str2.erase(0);
				}
			indx++;
		}
		printVector(data);
		return data;
	}
	
	int Client::JOIN(std::string commandArgs)
	{
		std::cout << "commandName: [" << "JOIN" << "]" << std::endl;
		std::cout << "commandArgs: [" << commandArgs << "]" << std::endl;
	
		// !@@@@@@@@@@@@@@@@@@@@@@!
		std::string	str1;
		std::string	str2;
		int			puse;
		int			puse0;

		puse = commandArgs.find(' ');
		if (puse != std::string::npos)
		{
			std::cout << "it's contin  a space\n";
			str1 = commandArgs.substr (0, puse);
			str2 = commandArgs.substr (puse + 1);
			parssAndUseData(str1, str2);
		}
		else
		{
			std::cout << "norm\n";
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
