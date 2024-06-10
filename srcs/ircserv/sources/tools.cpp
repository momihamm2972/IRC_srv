/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 23:14:53 by ahabachi          #+#    #+#             */
/*   Updated: 2024/06/09 23:49:37 by momihamm         ###   ########.fr       */
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

# include "../include/ircserv/tools.hpp"
# include <iostream>

namespace ircserv
{
	int usage(const char *programName)
	{
		std::cerr << programName << " <port> <password>" << std::endl;
		return (1);
	}
	std::string trim(const std::string s)
	{
		size_t first = s.find_first_not_of(" \t");
		if (std::string_view::npos == first)
		{
			return ("");
		}
		size_t last = s.find_last_not_of(" \t");
		return (s.substr(first, (last - first + 1)));
	}
	std::string ltrim(const std::string s)
	{
		size_t first = s.find_first_not_of(" \t");
		if (std::string_view::npos == first)
		{
			return ("");
		}
		return (s.substr(first, (s.length() - first)));
	}
	std::string toupper(const std::string s)
	{
		std::string u = "";
		for (size_t i = 0; i < s.length(); ++i)
		{
			u += std::toupper(s[i]);
		}
		return (u);
	}
	bool isdigit(char c)
	{
		return (('0' <= c) && (c <= '9'));
	}

	bool isprint(char c)
	{
		return (' ' <= c && c <= '~');
	}
	
	bool is_valid_nickname(const std::string nickname)
	{
		// https://modern.ircdocs.horse/#nick-message
		if (nickname.length() < 1)
		{
			return (false);
		}
		if ((nickname.length() < IRCSERV_MIN_NICKNAME_LENGTH) || (nickname.length() > IRCSERV_MAX_NICKNAME_LENGTH))
		{
			return (false);
		}
		if ((nickname[0] == '#') || (nickname[0] == '&') || (nickname[0] == ':'))
		{
			return (false);
		}
		if (ircserv::isdigit(nickname[0]))
		{
			return (false);
		}
		for (size_t i = 0; i < nickname.length(); i++)
		{
			if ((ircserv::isprint(nickname[i]) == false) || (nickname[i] == ' '))
			{
				return (false);
			}
		}
		return (true);
	}
	bool isspace(char c)
	{
		return (('\t' <= c && c <= '\r') || (c == ' '));
	}
	void *memcpy(void *dst, const void *src, size_t n)
	{
		size_t	i = 0;
		while ((dst != src) && (i++ < n))
		{
			((unsigned char *)dst)[i - 1] = ((unsigned char *)src)[i - 1];
		}
		return (dst);
	}
	void bzero(void *s, size_t n)
	{
		size_t	i = 0;
		while (i++ < n)
		{
			((unsigned char *)s)[i - 1] = 0;
		}
	}
	std::string nextWord(std::string &s)
	{
		size_t i = 0;
		s = ircserv::ltrim(s);
		while ((i < s.length()) && (ircserv::isspace(s[i]) == false))
		{
			i = i + 1;
		}
		std::string word = s.substr(0, i);
		if (i < s.length())
		{
			s = ircserv::ltrim(s.substr(i + 1, s.length() - i - 1));
		}
		else
		{
			s = "";
		}
		return (word);
	}
	std::string remove_all_with_spaces(std::string args)//momihamm
	{
		std::string result;
		bool inWord;

		inWord = false;
		for (std::size_t i = 0; i < args.length(); ++i) 
		{
			if (std::isspace(args[i])) 
			{
				if (!inWord) 
				{
					result += args[i];
					inWord = true;
				}
			} 
			else 
			{
				result += args[i];
				inWord = false;
			}
		}
		return result;
	}
};
