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

	/***********************************************************************************/
	// std::string input = "+itklo -itklo password limit nickname old_password nickname";
    // std::stringstream ss(input);
    // std::vector<std::string> plusTokens;
    // std::vector<std::string> minusTokens;
    // std::string token;

    // while (std::getline(ss, token, '+')) {
    //     std::stringstream tokenStream(token);
    //     std::string intermediateToken;
    //     while (std::getline(tokenStream, intermediateToken, '-')) {
    //         plusTokens.push_back(intermediateToken);
    //     }
    // }
	// std::cout << "-------- plusTokens  ------\n";
	// for (std::vector<std::string>::iterator it = plusTokens.begin();
	// 	it != plusTokens.end(); it++)
	// {
	// 	std::cout << *it << std::endl;
	// }
	// std::cout << "-------- minusTokens ------\n";
	// for (std::vector<std::string>::iterator it = minusTokens.begin();
	// 	it != minusTokens.end(); it++)
	// {
	// 	std::cout << *it << std::endl;
	// }
	/************************************************************************************/

	// std::string input = "+itklo          password    -itklo    limit      nickname          ";
    // std::stringstream ss(input);
    // std::vector<std::string> plusVector;
    // std::vector<std::string> minusVector;
    // std::vector<std::string> otherArgsVector;
    // std::string token;

    // // Tokenize the input
    // while (ss >> token) {
    //     // Check if the token starts with '+' or '-'
    //     if (token[0] == '+') {
    //         plusVector.push_back(token.substr(1)); // Remove the '+' sign
    //     } else if (token[0] == '-') {
    //         minusVector.push_back(token.substr(1)); // Remove the '-' sign
    //     } else {
    //         otherArgsVector.push_back(token);
    //     }
    // }

	// std::cout << "-------- plusTokens  ------\n";
	// for (std::vector<std::string>::iterator it = plusVector.begin();
	// 	it != plusVector.end(); it++)
	// {
	// 	std::cout << *it << std::endl;
	// }
	// std::cout << "-------- minusTokens ------\n";
	// for (std::vector<std::string>::iterator it = minusVector.begin();
	// 	it != minusVector.end(); it++)
	// {
	// 	std::cout << *it << std::endl;
	// }
	// std::cout << "-------- otherArgsVector ------\n";
	// for (std::vector<std::string>::iterator it = otherArgsVector.begin();
	// 	it != otherArgsVector.end(); it++)
	// {
	// 	std::cout << *it << std::endl;
	// }
	/*****************************************************************************/

	std::string input = "+i+o+l+k+t nickname number newkey";
    std::map<std::string, std::string> tokenMap;

    // Splitting the input string into tokens
    size_t pos = 0;
    std::string delimiter = "+";
    std::string token;
    while ((pos = input.find(delimiter)) != std::string::npos) {
        token = input.substr(0, pos);
        input.erase(0, pos + delimiter.length());

        // Check if there's a value for the token
        if (!input.empty() && input[0] != '+') {
            size_t nextPos = input.find(" ");
            std::string value = input.substr(0, nextPos);
            tokenMap[token] = value;
            input.erase(0, nextPos + 1); // Skip the value and space
        } else {
            tokenMap[token] = "NULL";
        }
    }

	// Print the tokens
	for (std::map<std::string, std::string>::iterator it = tokenMap.begin();
		 it != tokenMap.end(); it++) {
		std::cout << it->second << std::endl;
	}
	return (0);
}
