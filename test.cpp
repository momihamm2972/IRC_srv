# include <iostream>
# include <vector>
#include "/Users/ahabachi/Desktop/42cursus-ft_irc/srcs/ircserv/sources/tools.cpp"

void	splitWords(std::vector<std::string>& words, std::string& phrase)
{
	phrase = ircserv::trim(phrase);
	while (true)
	{
		size_t word_len = 0;
		while ((word_len < phrase.length()) && (phrase[word_len] != ',') && (phrase[word_len] != ' '))
		{
			word_len++;
		}
		std::string word = phrase.substr(0, word_len);
		words.push_back(word);
		if ((word_len >= phrase.length()) || (phrase[word_len] == ' '))
		{
			phrase = phrase.substr(word_len, phrase.length());
			break;
		}
		phrase = phrase.substr(word_len + 1, phrase.length());
	}
}

int main(int argc, char const *argv[])
{
	std::string commandArgs = "#food,,#genral makla,l3ya9a";
	std::string args = commandArgs;

	std::vector<std::string> channel_names;
	std::vector<std::string> channel_keys;

	splitWords(channel_names, args);
	std::cout << "afetr\n";
	splitWords(channel_keys, args);

	return 0;
}