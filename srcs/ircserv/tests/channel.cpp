/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   channel.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahaloui <ahaloui@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 23:47:24 by ahaloui           #+#    #+#             */
/*   Updated: 2024/05/14 21:49:09 by ahaloui          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


# include "../sources/Channel.cpp"
# include "../sources/Server.cpp"
# include "../sources/Client.cpp"
# include "../sources/tools.cpp"
# include "../sources/commands/INVITE.cpp"
# include "../sources/commands/JOIN.cpp"
# include "../sources/commands/KICK.cpp"
# include "../sources/commands/MODE.cpp"
# include "../sources/commands/NICK.cpp"
# include "../sources/commands/PART.cpp"
# include "../sources/commands/PASS.cpp"
# include "../sources/commands/PONG.cpp"
# include "../sources/commands/PRIVMSG.cpp"
# include "../sources/commands/TOPIC.cpp"
# include "../sources/commands/USER.cpp"
# include "../sources/commands/UNKNOWN.cpp"



using namespace ircserv;


 
int main(void)
{

    // ircserv::Server *server = new ircserv::Server();

    // ircserv::Channel *channel =  server->createChannel("food", "demnati");

    // channel->addClient("aymene");
    // channel->addClient("ahabachi");

    // ircserv::Client *client =  server->createClientByFd(1);
    // client->setNickname("ahaloui");

    // ircserv::Client *client1 =  server->createClientByFd(2);
    // client1->setNickname("aymene");

    // ircserv::Client *client2 =  server->createClientByFd(3);
    // client2->setNickname("ahabachi");

    // client->PRIVMSG("food :hello from another world");
    // client->PRIVMSG("aymene,ahabachi :hello from another world");
    /**************************************************/


    // ircserv::Server *server = new ircserv::Server();
    // ircserv::Channel *channel =  server->createChannel("food", "demnati");

    // channel->addClient("aymene");
    // channel->addClient("ahabachi");


    // ircserv::Client *client1 =  server->createClientByFd(2);
    // client1->setNickname("aymene");
    // ircserv::Client *client2 =  server->createClientByFd(3);
    // client2->setNickname("ahabachi");

    // ircserv::Client *client =  server->createClientByFd(1);
    // client->setNickname("ahaloui");

    // client->MODE("food1");

    /****************************************************************/


    std::string commandArgs = "              +itklo+-itklo             fx           sfd            ";
    std::string newCommandArgs = "";
    std::string otherArgs = "";
    int flag = 0;
    size_t i = 0;

    commandArgs = ircserv::trim(commandArgs);
    for (i = 0; i < commandArgs.length(); ++i) 
    {
        // if (commandArgs[i] != 'i' || commandArgs[i] != 't' 
        //     || commandArgs[i] != 'k' || commandArgs[i] != 'l' 
        //         || commandArgs[i] != 'o' || commandArgs[i] != '+' 
        //             || commandArgs[i] != '-')
        // {
        //     std::cout << "|" << commandArgs[i] << "|" << std::endl;
        //     std::cout << "Error: invalid character" << std::endl; 
        //     return (0);
        // }
        if (ircserv::isspace(commandArgs[i]))
            break;
        if (commandArgs[i] == '+') 
        {
            flag = 1;
            continue;
        }
        if (commandArgs[i] == '-') 
        {
            flag = 0;
            continue;
        }
        if (flag == 1) 
            newCommandArgs += "+";
        else 
            newCommandArgs += "-";
        newCommandArgs += commandArgs[i];
    }
    otherArgs = commandArgs.substr(i);
    std::cout << newCommandArgs << std::endl;

    for (size_t i = 0; i < newCommandArgs.length(); i += 2)
    {
        std::string tmp = newCommandArgs.substr(i, 2);
        if (tmp == "+i")
        {
            
        }
        else if (tmp == "+t")
            std::cout << "t" << std::endl;
        else if (tmp == "+k")
            std::cout << "k" << std::endl;
        else if (tmp == "+l")
            std::cout << "l" << std::endl;
        else if (tmp == "+o")
            std::cout << "o" << std::endl;
    }
    return (1);
}