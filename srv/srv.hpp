/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 20:11:35 by momihamm          #+#    #+#             */
/*   Updated: 2024/04/23 02:14:14 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <string>
#include <sys/socket.h>

class DataToStart
{
	public :
		std::string	Port;
		std::string	Pass;
		int			IdSocket;
};
