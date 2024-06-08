/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:04:36 by ahabachi          #+#    #+#             */
/*   Updated: 2024/06/08 19:59:19 by momihamm         ###   ########.fr       */
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

# include "../include/ircserv/Channel.hpp"

namespace ircserv
{
	Channel::Channel()
	{
		this->_name            = "";
		this->_key             = "";
		this->_topic           = "";
		this->_modes           = 0;
		this->_limit           = 0;
		this->_stream.str("");
		this->_operators.clear();
		this->_invitation_list.clear();
		this->_clients.clear();
		this->_kicked.clear();//momihamm
	}
	
	Channel::~Channel()
	{
		this->_name            = "";
		this->_key             = "";
		this->_topic           = "";
		this->_modes           = 0;
		this->_limit           = 0;
		this->_stream.str("");
		this->_operators.clear();
		this->_invitation_list.clear();
		this->_clients.clear();
		this->_kicked.clear();//momihamm
	}
	
	Channel& Channel::operator=(Channel const& other)
	{
		if (this == &other)
		{
			return (*this);
		}
		this->_name            = other._name;
		this->_key             = other._key;
		this->_topic           = other._topic;
		this->_modes           = other._modes;
		this->_limit           = other._limit;
		this->_operators       = other._operators;
		this->_invitation_list = other._invitation_list;
		this->_clients         = other._clients;
		this->_kicked		   = other._kicked;//momihamm
		this->_stream.str(other._stream.str());
		return (*this);
	}
	Channel::Channel(Channel const& other)
	{
		*this = other;
	}

	Channel::Channel(std::string channel_name, std::string operator_nickname)
	{
		this->_name            = channel_name;
		this->_key             = "";
		this->_topic           = "";
		this->_modes           = 0;
		this->_limit           = 0;
		this->_operators.clear();
		this->_invitation_list.clear();
		this->_clients.clear();
		this->_kicked.clear();//momihamm
		this->_stream.str("");
		this->addClient(operator_nickname);
	}

	/* ****************** getters ****************** */
	std::vector<std::string /* nickname */> &Channel::getOperators(void)
	{
		return (this->_operators);
	}
	std::vector<std::string /* nickname */> &Channel::getClients(void)
	{
		return (this->_clients);
	}
	std::vector<std::string /* nickname */> &Channel::getInvitedClients(void)
	{
		return (this->_invitation_list);
	}
	std::vector<std::string /* nickname */> &Channel::getKickedClients(void)//momihamm
	{
		return (this->_kicked);
	}
	
	/* ****************** methods ****************** */
	bool Channel::isClient(std::string nickname)
	{
		std::vector<std::string>::iterator it = std::find(
			this->getClients().begin(),
			this->getClients().end(),
			nickname
		);
		if (it != this->getClients().end())
		{
			return (true);
		}
		return (false);
	}
	bool Channel::addClient(std::string nickname)
	{
		if (this->hasMode(CHANNEL_MODE_L))
		{
			if (this->getLimit() <= this->getClients().size())
			{
				return (false);
			}
		}
		this->getClients().push_back(nickname);
		this->removeInvited(nickname);
		if (this->getOperators().size() < 1)
		{
			// channel khawya, hada howa first member li joyna
			// lhad channel so howa ghaykon `operator`
			this->addOperator(nickname);
		}
		return (true);
	}
	void Channel::removeClient(std::string nickname)
	{
		std::vector<std::string>::iterator it = std::find(
			this->getClients().begin(),
			this->getClients().end(),
			nickname
		);
		if (it != this->getClients().end())
		{
			this->getClients().erase(it);
		}

		this->removeOperator(nickname);
		this->removeInvited(nickname);
	}
	bool Channel::isOperator(std::string nickname)
	{
		std::vector<std::string>::iterator it = std::find(
			_operators.begin(),
			_operators.end(),
			nickname
		);
		if (it != _operators.end())
		{
			return (true);
		}
		return (false);
	}
	bool Channel::addOperator(std::string nickname)
	{
		std::vector<std::string>::iterator it;

		it = std::find(
			this->getClients().begin(),
			this->getClients().end(),
			nickname
		);
		if (it == this->getClients().end())
		{
			return (false);
		}
		it = std::find(
			this->getOperators().begin(),
			this->getOperators().end(),
			nickname
		);
		if (it == this->getOperators().end())
		{
			this->getOperators().push_back(nickname);
			return (true);
		}
		return (false);
	}

	void Channel::removeOperator(std::string nickname)
	{
		std::vector<std::string>::iterator it = std::find(
			this->getOperators().begin(),
			this->getOperators().end(),
			nickname
		);
		if (it != this->getOperators().end())
		{
			this->getOperators().erase(it);
		}
	}

	bool Channel::isKicked(std::string nickname)//momihamm
	{
		std::vector<std::string>::iterator it = std::find(
			_kicked.begin(),
			_kicked.end(),
			nickname
		);
		if (it != _kicked.end())
		{
			return (true);
		}
		return (false);
	}

	bool Channel::isInvited(std::string nickname)
	{
		std::vector<std::string>::iterator it = std::find(
			_invitation_list.begin(),
			_invitation_list.end(),
			nickname
		);
		if (it != _invitation_list.end())
		{
			return (true);
		}
		return (false);
	}

	void Channel::inviteClient(std::string nickname)
	{
		std::vector<std::string>::iterator it;
		it = std::find(
			this->getClients().begin(),
			this->getClients().end(),
			nickname
		);
		if (it != this->getClients().end())
		{
			return ;
		}
		it = std::find(
			this->getOperators().begin(),
			this->getOperators().end(),
			nickname
		);
		if (it != this->getOperators().end())
		{
			return ;
		}
		it = std::find(
			_invitation_list.begin(),
			_invitation_list.end(),
			nickname
		);
		if (it == _invitation_list.end())
		{
			_invitation_list.push_back(nickname);
		}
	}

	void Channel::removeInvited(std::string nickname)
	{
		std::vector<std::string>::iterator it = std::find(
			_invitation_list.begin(),
			_invitation_list.end(),
			nickname
		);
		if (it != _invitation_list.end())
		{
			_invitation_list.erase(it);
		}
	}

	bool Channel::hasMode(int mode)
	{
		if (this->_modes & mode)
		{
			return (true);
		}
		return (false);
	}
	void Channel::setMode(int mode)
	{
		this->_modes |= mode;
	}
	void Channel::unsetMode(int mode)
	{
		this->_modes &= ~mode;
	}

	size_t Channel::getLimit(void) const
	{
		return (this->_limit);
	}
	void Channel::setLimit(size_t limit)
	{
		this->_limit = limit;
		this->setMode(CHANNEL_MODE_L);
	}
	void Channel::unsetLimit(void)
	{
		this->unsetMode(CHANNEL_MODE_L);
	}

	void Channel::setKey(std::string key)
	{
		this->_key = key;
		this->setMode(CHANNEL_MODE_K);
	}

	void Channel::unsetKey(void)
	{
		this->_key = "";
		this->unsetMode(CHANNEL_MODE_K);
	}
	
	std::string Channel::getKey(void)//momihamm
	{
		return (this->_key);
	}

	void Channel::setTopic(const std::string topic)
	{
		this->_topic = topic;
	}

	std::string Channel::getTopic(void) const
	{
		return (this->_topic);
	}

	std::string Channel::getName(void) const
	{
		return (this->_name);
	}

	void Channel::setName(const std::string name)
	{
		this->_name = name;
	}
};
