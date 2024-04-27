/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srv.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momihamm <momihamm@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 20:11:33 by momihamm          #+#    #+#             */
/*   Updated: 2024/04/27 10:46:31 by momihamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "srv.hpp"
#include <arpa/inet.h>


// creat a socket;
// bind a socket;
// Mark the socket for listening in

int main(int ac, char **av)
{
	(void)av;
	DataToStart start;
	sockaddr_in SrvAddr;
	(void) SrvAddr;
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
		start.binding = bind (start.IdSocket, (const sockaddr *)& SrvAddr, sizeof (SrvAddr));
		std::cout << "ID " << start.IdSocket << " Binding " << start.binding << std::endl;
		// first_socket = socket ();
	}
	else
		std::cerr << "Error 404" << std::endl;
}