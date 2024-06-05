/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MODE.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 21:30:11 by ahaloui           #+#    #+#             */
/*   Updated: 2024/05/15 18:06:24 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/ircserv/Client.hpp"
#include "../../include/ircserv/Server.hpp"

namespace ircserv
{
    int check_mode(char mode)
    {
        if (mode != 'i' && mode != 't' && mode != 'k' && mode != 'l' && mode != 'o')
            return (1);
        return (0);
    }
	int Client::MODE(std::string commandArgs)
	{
        ircserv::Server *server;
        ircserv::Channel *channel;
        std::string channelName = "";
        std::string newModes = "";
        int flag = 0;
        
    
        server = this->getServer();
        commandArgs = ircserv::trim(commandArgs);
        channelName = nextWord(commandArgs);
        if (channelName == "")
        {
			// https://modern.ircdocs.horse/#errneedmoreparams-461
			*this << "461 " << this->getNickname() << " MODE :Not enough parameters" << ircserv::crlf;
			return (0);
        }
        channel = server->getChannelByName(channelName);
        if (channel == NULL)
        {
            // https://modern.ircdocs.horse/#errnosuchchannel-403
            //  "<client> <channel> :No such channel"
            *this << this->getNickname() << " " << channelName << " :No such channel" << ircserv::crlf;
            return (0);
        }
        std::string modes = nextWord(commandArgs);
        std::cout << "modes: |" << modes <<"|" << std::endl;
        if (modes == "")
        {
            // https://modern.ircdocs.horse/#rplchannelmodeis-324
            // "<client> <channel> <modestring> <mode arguments>..."
            
            if (channel->hasMode(CHANNEL_MODE_I))
                *this << "324 " << this->getNickname() << " " << channel->getName() << " +i" << ircserv::crlf;
            else if (channel->hasMode(CHANNEL_MODE_T))
                *this << "324 " << this->getNickname() << " " << channel->getName() << " +t" << ircserv::crlf;
            else if (channel->hasMode(CHANNEL_MODE_K))
                *this << "324 " << this->getNickname() << " " << channel->getName() << " +k" << ircserv::crlf;
            else if (channel->hasMode(CHANNEL_MODE_L))
                *this << "324 " << this->getNickname() << " " << channel->getName() << " +l" << ircserv::crlf;
            else if (channel->hasMode(CHANNEL_MODE_O))
                *this << "324 " << this->getNickname() << " " << channel->getName() << " +o" << ircserv::crlf;
            return (1);
        }

        if (channel->isOperator(this->getNickname()) == false)
        {
            // https://modern.ircdocs.horse/#errchanoprivsneeded-482
            // "<client> <channel> :You're not channel operator"
            
            *this << "482 " << this->getNickname() << " " << channel->getName() << " :You're not channel operator" << ircserv::crlf;
            return (0);
        }
        
        
        for (size_t i = 0; i < modes.length(); ++i) 
        {
            if (modes[i] == '+') 
            {
                if (check_mode(modes[i + 1]) == 1)
                {
                    *this << "472 " << this->getNickname() << " " << modes[i + 1] << " :is unknown mode char to me" << ircserv::crlf;
                    return (0);
                }
                flag = 1;
                continue;
            }
            if (modes[i] == '-') 
            {
                if (check_mode(modes[i + 1]) == 1)
                {
                    *this << "472 " << this->getNickname() << " " << modes[i + 1] << " :is unknown mode char to me" << ircserv::crlf;
                    return (0);
                }
                flag = 2;
                continue;
            }
            if (flag == 1) 
                newModes += "+";
            else if (flag == 2)
                newModes += "-";
            newModes += modes[i];
        }

        std::cout << "newModes: |" << newModes << "|" << std::endl;
        for (size_t i = 0; i < newModes.length(); i += 2)
        {
            std::string tmp = newModes.substr(i, 2);
            /*********************************************************************************/
            if (tmp == "+i")
            {
                // https://modern.ircdocs.horse/#rplchannelmodeis-324
                // "<client> <channel> +i"
                
                if (!channel->hasMode(CHANNEL_MODE_I))
                    channel->setMode(CHANNEL_MODE_I);
                *this << "324 " << this->getNickname() << " " << channel->getName() << " +i" << ircserv::crlf;
            }
            else if (tmp == "-i")
            {
                // https://modern.ircdocs.horse/#rplchannelmodeis-324
                // "<client> <channel> -i"

                if (channel->hasMode(CHANNEL_MODE_I))
                    channel->unsetMode(CHANNEL_MODE_I);
                *this << "324 " << this->getNickname() << " " << channel->getName() << " -i" << ircserv::crlf;
            }
            /*********************************************************************************/
            else if (tmp == "+t")
            {
                // https://modern.ircdocs.horse/#rplchannelmodeis-324
                // "<client> <channel> +t"
                // ghir loperato li ksybedlo topic
                
                if (!channel->hasMode(CHANNEL_MODE_T))
                    channel->setMode(CHANNEL_MODE_T);
                *this << "324 " << this->getNickname() << " " << channel->getName() << " +t" << ircserv::crlf;
            }
            else if (tmp == "-t")
            {
                // https://modern.ircdocs.horse/#rplchannelmodeis-324
                // "<client> <channel> -t"
                
                if (channel->hasMode(CHANNEL_MODE_T))
                    channel->unsetMode(CHANNEL_MODE_T);
                *this << "324 " << this->getNickname() << " " << channel->getName() << " -t" << ircserv::crlf;
            }
            /*********************************************************************************/
            else if (tmp == "+k")
            {
                // https://modern.ircdocs.horse/#rplchannelmodeis-324
                // "<client> <channel> +k"
                
                if (!channel->hasMode(CHANNEL_MODE_K))
                    channel->setMode(CHANNEL_MODE_K);
                std::string key = nextWord(commandArgs);
                // std::cout << "tmp => " << tmp << " ";
                // std::cout << "key: |" << key << "|" << std::endl;
                if (key == "")
                {
                    // https://modern.ircdocs.horse/#errneedmoreparams-461
                    *this << "461 " << this->getNickname() << " MODE :Not enough parameters" << ircserv::crlf;
                    return (0);
                }
                channel->setKey(key);
                *this << "324 " << this->getNickname() << " " << channel->getName() << " +k" << ircserv::crlf;
            }
            else if (tmp == "-k")
            {
                // https://modern.ircdocs.horse/#rplchannelmodeis-324
                // "<client> <channel> -k"
                
                if (channel->hasMode(CHANNEL_MODE_K))
                    channel->unsetMode(CHANNEL_MODE_K);
                channel->setKey("");
                *this << "324 " << this->getNickname() << " " << channel->getName() << " -k" << ircserv::crlf;
            }
            /*********************************************************************************/
            else if (tmp == "+l")
            {
                // https://modern.ircdocs.horse/#rplchannelmodeis-324
                // "<client> <channel> +l"
                
                std::string limit = nextWord(commandArgs);
                // std::cout << "tmp => " << tmp << " ";
                // std::cout << "limit: |" << limit << "|" << std::endl;
                if (limit == "")
                {
                    // https://modern.ircdocs.horse/#errneedmoreparams-461
                    *this << "461 " << this->getNickname() << " MODE :Not enough parameters" << ircserv::crlf;
                    return (0);
                }
                if (!channel->hasMode(CHANNEL_MODE_L))
                    channel->setMode(CHANNEL_MODE_L);
                try 
                {
                    channel->setLimit(std::stoi(limit));
                    *this << "324 " << this->getNickname() << " " << channel->getName() << " +l" << ircserv::crlf;
                }
                catch (const std::exception& e)
                {
                    *this << "461 " << this->getNickname() << " Should be a number" << ircserv::crlf;
                    return (0);
                }
            }
            else if (tmp == "-l")
            {
                // https://modern.ircdocs.horse/#rplchannelmodeis-324
                // "<client> <channel> -l"
                
                if (channel->hasMode(CHANNEL_MODE_L))
                    channel->unsetMode(CHANNEL_MODE_L);
                channel->setLimit(0);
                *this << "324 " << this->getNickname() << " " << channel->getName() << " -l" << ircserv::crlf;
            }
            /*********************************************************************************/
            else if (tmp == "+o")
            {
                // https://modern.ircdocs.horse/#rplchannelmodeis-324
                // "<client> <channel> +o"
                
                std::string operatorName = nextWord(commandArgs);
                if (operatorName == "")
                {
                    // https://modern.ircdocs.horse/#errneedmoreparams-461
                    *this << "461 " << this->getNickname() << " MODE :Not enough parameters" << ircserv::crlf;
                    return (0);
                }
                // std::cout << "tmp => " << tmp << " ";
                // std::cout << "operatorName: |" << operatorName << "|" << std::endl;
                if (!channel->hasMode(CHANNEL_MODE_O))
                    channel->setMode(CHANNEL_MODE_O);
                if (!channel->isOperator(operatorName))
                    channel->addOperator(operatorName);
                *this << "324 " << this->getNickname() << " " << channel->getName() << " +o" << ircserv::crlf;
            }
            else if (tmp == "-o")
            {
                // https://modern.ircdocs.horse/#rplchannelmodeis-324
                // "<client> <channel> -o"
                
                std::string operatorName = nextWord(commandArgs);
                if (operatorName == "")
                {
                    // https://modern.ircdocs.horse/#errneedmoreparams-461
                    *this << "461 " << this->getNickname() << " MODE :Not enough parameters" << ircserv::crlf;
                    return (0);
                }
                if (channel->hasMode(CHANNEL_MODE_O))
                    channel->unsetMode(CHANNEL_MODE_O);
                if (channel->isOperator(operatorName))
                    channel->removeOperator(operatorName);
                *this << "324 " << this->getNickname() << " " << channel->getName() << " -o" << ircserv::crlf;
            }
            /*********************************************************************************/
            else {
                // https://modern.ircdocs.horse/#errunknownmode-472
                // "<client> <mode> :is unknown mode char to me"
                
                *this << "472 " << this->getNickname() << " " << tmp << " :is unknown mode char to me" << ircserv::crlf;
                return (0);
            }
        }
        return (1);
	};
};