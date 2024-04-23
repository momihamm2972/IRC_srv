/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 20:11:33 by momihamm          #+#    #+#             */
/*   Updated: 2024/04/23 02:32:29 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srv.hpp"

// creat a socket
// 


int main(int ac, char **av)
{
	(void)av;
	DataToStart start;
	if (ac == 3)
	{
		// int     first_socket;
		start.Port = av[1];
		start.Pass = av[2];
		
		if (start.Port.find_first_not_of("123456789") != std::string::npos)
		{
			std::cerr <<"Error 404" << std::endl;
			return (1);
		}
		// std::cout << "kmi " << start.Port << " "<< start.Pass <<  std::endl ;
		start.IdSocket = socket (AF_INET, SOCK_STREAM, 0);
		std::cout << start.IdSocket << std::endl;
		// first_socket = socket ();
	}
	else
		std::cerr << "Error 404" << std::endl;
}