
# include "../sources/Channel.cpp"
# include "../sources/Client.cpp"

using namespace ircserv;
 
int main(void)
{
    Channel *channel = new Channel("#channel_name", "ahabachi");

    channel->setLimit(2000);

    channel->addClientByNickname("client_00");
    channel->addClientByNickname("client_01");
    channel->addClientByNickname("client_02");
    channel->addClientByNickname("client_03");
    channel->addClientByNickname("client_04");

    channel->addClientToInvitionListByNickname("client_05");

    channel->setClientAsOperatorByNickname("client_04");


    for (
        std::vector<std::string>::iterator it = channel->getOperators().begin();
        it != channel->getOperators().end(); it++
    )
    {
        std::cout << "operator: " << *it << std::endl;
    }

    for (
        std::vector<std::string>::iterator it = channel->getClients().begin();
        it != channel->getClients().end(); it++
    )
    {
        std::cout << "client  : " << *it << std::endl;
    }
  
    for (
        std::vector<std::string>::iterator it = channel->getInvitedClients().begin();
        it != channel->getInvitedClients().end(); it++
    )
    {
        std::cout << "invited  : " << *it << std::endl;
    }

    return (0);
}
