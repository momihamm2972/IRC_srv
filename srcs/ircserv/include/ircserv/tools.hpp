/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 23:14:53 by ahabachi          #+#    #+#             */
/*   Updated: 2024/06/09 23:51:05 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

#pragma once

# include <iostream>

# define IRCSERV_MIN_PORT_VALUE      1024
# define IRCSERV_MAX_PORT_VALUE      65535
# define IRCSERV_BACKLOG             1024
# define IRCSERV_BUFFER_SIZE         1024
# define IRCSERV_MIN_PASSWORD_LENGTH 4
# define IRCSERV_MAX_PASSWORD_LENGTH 64
# define IRCSERV_MIN_NICKNAME_LENGTH 1
# define IRCSERV_MAX_NICKNAME_LENGTH 16

namespace ircserv
{
	const std::string crlf = "\r\n";
	int         usage(const char *programName);
	std::string trim(const std::string s);
	std::string ltrim(const std::string s);
	std::string toupper(const std::string s);
	bool        is_valid_nickname(const std::string nickname);
	bool        isdigit(char c);
	bool        isprint(char c);
	bool        isspace(char c);
	void        *memcpy(void *dst, const void *src, size_t n);
	void        bzero(void *s, size_t n);
	std::string nextWord(std::string &s);
	std::string remove_all_with_spaces(std::string args);//momihamm
};
