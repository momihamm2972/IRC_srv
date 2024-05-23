/* ************************************************************************** */
/*                                                                            */
/*                                                         :::      ::::::::  */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahabachi <ahabachi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 20:22:43 by ahabachi          #+#    #+#             */
/*   Updated: 2024/05/03 17:28:33 by ahabachi         ###   ########.fr       */
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

# include "../include/ircserv/tools.hpp"
# include "../include/ircserv/Server.hpp"
# include "../include/ircserv/Client.hpp"
# include "../include/ircserv/Channel.hpp"

# include <iostream>

int main(int argc, char **argv)
{
	if (argc != 3)
	{
		return (ircserv::usage(argv[0]));
	}
	ircserv::Server srv = ircserv::Server();

	if (srv.init(argv[1], argv[2]) == false)
	{
		return (1);
	}
	if (srv.start() == false)
	{
		srv.fini();
		return (1);
	}
	srv.fini();
	return (0);
}
