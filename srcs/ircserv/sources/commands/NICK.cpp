/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NICK.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:50:45 by momihamm          #+#    #+#             */
/*   Updated: 2024/05/07 11:50:50 by momihamm         ###   ########.fr       */
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

namespace ircserv
{
	int Client::NICK(std::string commandArgs)
	{
		commandArgs = ircserv::trim(commandArgs);
		if (commandArgs.length() < 1)
		{
			// https://modern.ircdocs.horse/#errnonicknamegiven-431
			*this << ":localhost 431 NICK :No nickname given" << ircserv::crlf;
			return (this->isAuthenticated());
		}
		if (this->_password.length() < 1)
		{
			// https://modern.ircdocs.horse/#errnotregistered-451
			*this << ":localhost 451 NICK :You have not registered" << ircserv::crlf;
			return (this->isAuthenticated());
		}
		if (ircserv::is_valid_nickname(commandArgs) == false)
		{
			// https://modern.ircdocs.horse/#errerroneusnickname-432
			*this << ":localhost 432 NICK :Erroneus nickname" << ircserv::crlf;
			return (this->isAuthenticated());
		}
		if (this->getServer()->getClientByNickname(commandArgs) != NULL)
		{
			// https://modern.ircdocs.horse/#errnicknameinuse-433
			*this << ":localhost 433 NICK :Nickname is already in use" << ircserv::crlf;
			return (this->isAuthenticated());
		}
		this->_nickname = commandArgs;
		return (this->isAuthenticated());
	};
};
