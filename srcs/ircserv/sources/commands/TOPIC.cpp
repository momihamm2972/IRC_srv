/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TOPIC.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:51:24 by momihamm          #+#    #+#             */
/*   Updated: 2024/06/09 04:22:50 by momihamm         ###   ########.fr       */
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
#include <unistd.h>

namespace ircserv
{
	int Client::TOPIC(std::string commandArgs)
	{
		// case TOPIC:
		// khas tkon operator il kan l mode dyal channel +t
		// TOPIC channel_name // show the channel topics
		// TOPIC channel_name topic
		// TOPIC channel_name :topic with spaces
		
		std::cout << "commandName: [" << "TOPIC" << "]" << std::endl;
		std::cout << "commandArgs: [" << commandArgs << "]" << std::endl;
		
		
		return (0);
	};
};
