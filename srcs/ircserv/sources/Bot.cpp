/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   Bot.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabachi <ahabachi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 14:07:46 by ahabachi          #+#    #+#             */
/*   Updated: 2024/05/14 14:08:19 by ahabachi         ###   ########.fr       */
/*                                                                            */
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

# include "../include/ircserv/Bot.hpp"
# include <iostream>

namespace ircserv
{
	Bot::Bot()
	{
		
	}
	Bot::~Bot()
	{
		
	}
	Bot& Bot::operator=(Bot const& other)
	{
		return (*this);
	}
	Bot::Bot(Bot const& other)
	{
		*this = other;
	}
};

int main(void)
{
	return (0);
}
