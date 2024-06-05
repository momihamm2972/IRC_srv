/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:04:36 by ahabachi          #+#    #+#             */
/*   Updated: 2024/06/05 15:31:26 by momihamm         ###   ########.fr       */
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

# include "./Client.hpp"
# include <iostream>
# include <vector>

# define CHANNEL_MODE_I 1 << 0
# define CHANNEL_MODE_T 1 << 1
# define CHANNEL_MODE_K 1 << 2
# define CHANNEL_MODE_L 1 << 3
# define CHANNEL_MODE_O 1 << 4

namespace ircserv
{
	class Channel
	{
		private:
			std::string                             _name;
			std::string                             _key;
			std::string                             _topic;
			int                                     _modes;
			size_t                                  _limit;
			std::ostringstream                      _stream;
			std::vector<std::string /* nickname */> _operators;
			std::vector<std::string /* nickname */> _invitation_list;
			std::vector<std::string /* nickname */> _clients;
		public:
			Channel();
			~Channel();
			Channel& operator=(Channel const& other);
			Channel(Channel const& other);
			Channel(std::string channel_name, std::string operator_nickname);			

			/* ****************** operators ****************** */
			Channel& operator<<(int val);
			Channel& operator<<(const std::string s);


			/* ****************** getters ****************** */
			std::vector<std::string /* nickname */> &getOperators(void);
			std::vector<std::string /* nickname */> &getClients(void);
			std::vector<std::string /* nickname */> &getInvitedClients(void);
			/* ****************** methods ****************** */

			bool        isClient(std::string nickname);
			bool        addClient(std::string nickname);
			void        removeClient(std::string nickname);

			bool        isOperator(std::string nickname);
			bool        addOperator(std::string nickname);
			void        removeOperator(std::string nickname);

			bool        isInvited(std::string nickname);
			void        inviteClient(std::string nickname);
			void        removeInvited(std::string nickname);

			bool        hasMode(int mode);
			void        setMode(int mode);
			void        unsetMode(int mode);

			void        setLimit(size_t limit);
			size_t      getLimit(void) const;
			void        unsetLimit(void);

			void        setKey(std::string key);
			void        unsetKey(void);
			std::string	getKey(void);//momihamm
		
			void        setTopic(const std::string topic);
			std::string getTopic(void) const;

			std::string getName(void) const;
			void        setName(const std::string name);
	};
};
