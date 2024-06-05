
# include "../sources/tools.cpp"

int main(int argc, char const *argv[])
{
	std::string phrase = "  The                         quick brown fox          jumps over the lazy dog  ";
		
	phrase = "";

	std::cout << "(" << ircserv::nextWord(phrase) << ")" << std::endl;
	std::cout << "(" << ircserv::nextWord(phrase) << ")" << std::endl;
	std::cout << "(" << ircserv::nextWord(phrase) << ")" << std::endl;
	std::cout << "(" << ircserv::nextWord(phrase) << ")" << std::endl;
	std::cout << "(" << ircserv::nextWord(phrase) << ")" << std::endl;
	std::cout << "(" << ircserv::nextWord(phrase) << ")" << std::endl;
	std::cout << "(" << ircserv::nextWord(phrase) << ")" << std::endl;
	std::cout << "(" << ircserv::nextWord(phrase) << ")" << std::endl;
	std::cout << "(" << ircserv::nextWord(phrase) << ")" << std::endl;
	std::cout << "(" << ircserv::nextWord(phrase) << ")" << std::endl;
	std::cout << "(" << ircserv::nextWord(phrase) << ")" << std::endl;
	std::cout << "(" << ircserv::nextWord(phrase) << ")" << std::endl;

	return 0;
}
