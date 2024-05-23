
# include "../../sources/Channel.cpp"
# include "../../sources/Client.cpp"
# include "../../sources/Server.cpp"
# include "../../sources/commands/INVITE.cpp"
# include "../../sources/commands/JOIN.cpp"
# include "../../sources/commands/KICK.cpp"
# include "../../sources/commands/MODE.cpp"
# include "../../sources/commands/NICK.cpp"
# include "../../sources/commands/PART.cpp"
# include "../../sources/commands/PASS.cpp"
# include "../../sources/commands/PONG.cpp"
# include "../../sources/commands/PRIVMSG.cpp"
# include "../../sources/commands/TOPIC.cpp"
# include "../../sources/commands/USER.cpp"
# include "../../sources/commands/UNKNOWN.cpp"
# include "../../sources/tools.cpp"

using namespace ircserv;
 
int main(void)
{

    ircserv::Server server = ircserv::Server();

    ircserv::Client *client0 = server.createClientByFd(3); client0->setNickname("client0");
    ircserv::Client *client1 = server.createClientByFd(4); client1->setNickname("client1");
    ircserv::Client *client2 = server.createClientByFd(5); client2->setNickname("client2");
    ircserv::Client *client3 = server.createClientByFd(6); client3->setNickname("client3");
    ircserv::Client *client4 = server.createClientByFd(7); client4->setNickname("client4");
    ircserv::Client *client5 = server.createClientByFd(8); client5->setNickname("client5");
    ircserv::Client *client6 = server.createClientByFd(9); client6->setNickname("client6");

    Channel *channel = server.createChannel("#food", "client0");

    
    for (
        std::vector<std::string>::iterator it = channel->getClients().begin();
        it != channel->getClients().end(); it++)
    {
        std::string nickname = *it;
        ircserv::Client *client = server.getClientByNickname(nickname);
        if (client)
        {
            *client << "Hello " << nickname << ircserv::crlf;
            // std::cout << "nickname: " << nickname << std::endl;
        }
    }



    return (0);
}
