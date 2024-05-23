// c++ server.cpp -o server && clear && ./server

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

    Server server = Server();

    server.createChannel( "food", "demnati");


    ircserv::Channel* channel = server.getChannelByName("food");

    if (channel)
    {
        *channel << ":localhost 001 " << ircserv::crlf;
    }








    // ircserv::Channel* channel = server.getChannelByName("food");
    
    // if (channel)
    // {
    //     std::cout << "channelName: " << channel->getName() << std::endl;
    //     server.removeChannel("food");
    // }
    // std::cout << "END" << std::endl;




    // return (0);



    // server.createClientByFd( 88 );
    // server.createClientByFd( 88 );
    // server.createClientByFd( 88 );
    // server.createClientByFd( 88 );

    // for (
    //     std::map<int, ircserv::Client>::iterator i = server.getClients().begin();
    //     i != server.getClients().end();
    //     i++
    // )
    // {
    //     std::cout << "fd = " << i->first << std::endl;
    // }

    // server.removeClientByFd( 88 );

    // for (
    //     std::map<int, ircserv::Client>::iterator i = server.getClients().begin();
    //     i != server.getClients().end();
    //     i++
    // )
    // {
    //     std::cout << "fd = " << i->first << std::endl;
    // }

    // leaks();
    return (0);
}
