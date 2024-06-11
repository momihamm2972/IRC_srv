/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PRIVMSG.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 18:43:21 by ahaloui           #+#    #+#             */
/*   Updated: 2024/06/11 18:10:04 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../include/ircserv/Client.hpp"
#include "../../include/ircserv/Server.hpp"
#include <set>

namespace ircserv
{
	int Client::PRIVMSG(std::string commandArgs)
	{

		std::cout << "commandName: [" << "PRIVMSG" << "]" << std::endl;
		std::cout << "commandArgs: [" << commandArgs << "]" << std::endl;
		// privmsg ahaloui,ahabach,aymene:test test test
		// privmsg ahaloui,food,aymene hello world

		
		// message to a channel or a user 
		// PRIVMSG <receiver> <text to send>
		
		// PRIVMSG #channel :text
		// PRIVMSG nickname :text
		
		std::string message;
		std::set<std::string> names;
		int i = 0;
		int j = 0;

		while (i < commandArgs.length())
		{
			if (commandArgs[i] == ',')
			{
				names.insert(commandArgs.substr(j, i - j));
				j = i + 1;
			}
			else if (commandArgs[i] == ' ')
			{
				std::string last = commandArgs.substr(j, i - j);
				if (last.length() > 0)
					names.insert(last);
				break;
			}
			i++;
		}
		/*for case "privmsg test" */
		if (i < commandArgs.length())
			message = trim(commandArgs.substr(i + 1));
		else
			message = "";
			
		if ( message == "" /*for case" privmsg ahaloui"*/  
			|| message.length() < 1 
				|| message == ":" ) 
		{
			// replay error
			// https://modern.ircdocs.horse/#errnotexttosend-412
			*this << "412 " << this->getNickname() << " :No text to send " << ircserv::crlf;
			return (0);
		}
		
		if (message.length() > 1 && message[0] == ':')
			message = message.substr(1);
		else if (message[0] != ':' && message.length() > 0)
		{
			size_t pos = message.find(" ");
			if (pos != std::string::npos)
				message = (message.substr(0, pos));
		}
		if (names.size() < 1)
		{
			// replay error
			// https://modern.ircdocs.horse/#errnonicknamegiven-431
			*this << "431 " << this->getNickname() << " :No nickname given " << ircserv::crlf;
			return (0);
		}
		std::cout << "--------- names ----------: " << std::endl;
		for (std::set<std::string>::iterator it = names.begin(); it != names.end(); it++)
		{
			std::cout << "|" << *it << "|" << std::endl;
		}
		std::cout << "message: "  << "|" << message << "|" << std::endl;
		std::cout << "-------------------------" << std::endl;
		
		ircserv::Server* server = this->getServer();
		for (std::set<std::string>::iterator it = names.begin(); it != names.end(); it++)
		{
		    ircserv::Channel* channel = server->getChannelByName(*it);
		    if (channel)
		    {
		        // send message to channel
		        std::vector<std::string> clients = channel->getClients();
		        for (std::vector<std::string>::iterator it = clients.begin(); it != clients.end(); it++)
		        {
		            ircserv::Client* client = server->getClientByNickname(*it);
		            if (client && client->getNickname() != this->getNickname())
		                *client << "PRIVMSG " << *it << " :" << message << ircserv::crlf;
		        }
		    }
		    else
		    {
		        // send message to user
		        ircserv::Client* client = server->getClientByNickname(*it);
		        if (client && client->getNickname() != this->getNickname())
		        {
		            *client << "PRIVMSG " << *it << " :" << message << ircserv::crlf;
		        }
		        else
		        {
		            // send error message
		            // https://modern.ircdocs.horse/#errnosuchnick-401
		            *this << "401 " << *it << " :No such nick/channel " << ircserv::crlf;
		        }
		    }
		}
		return (1);
	};
};