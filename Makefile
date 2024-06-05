#  **************************************************************************  #
#                                                                              #
#                                                          :::      ::::::::   #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahabachi <ahabachi@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/14 14:11:33 by ahabachi          #+#    #+#              #
#    Updated: 2024/05/14 14:14:56 by ahabachi         ###   ########.fr        #
#                                                                              #
#  **************************************************************************  #
#                                                                              #
#   █████████            ██████████         ██████████         ██████████      #
#   ██     ██                    ██                 ██         ██      ██      #
#          ██                    ██                 ██         ██      ██      #
#          ██                    ██                 ██                 ██      #
#          ██            ██████████         ██████████                 ██      #
#          ██                    ██                 ██                 ██      #
#          ██                    ██                 ██                 ██      #
#          ██                    ██                 ██                 ██      #
#       ████████         ██████████         ██████████                 ██      #
#                                                                              #
#  **************************************************************************  #

CPP=c++
# CXXFLAGS=-Wall -Wextra -Werror
CXXFLAGS+=-std=c++98
NAME=ircserv
BNAME=ircbot

SOURCES_DIR=srcs/ircserv/sources
OBJECTS_DIR=srcs/ircserv/objects

BOT_SOURCES=${SOURCES_DIR}/Bot.cpp
BOT_OBJECTS=${OBJECTS_DIR}/Bot.o

IRCSERV_SOURCES+=${SOURCES_DIR}/main.cpp
IRCSERV_SOURCES+=${SOURCES_DIR}/tools.cpp
IRCSERV_SOURCES+=${SOURCES_DIR}/Client.cpp
IRCSERV_SOURCES+=${SOURCES_DIR}/Server.cpp
IRCSERV_SOURCES+=${SOURCES_DIR}/Channel.cpp

IRCSERV_SOURCES+=${SOURCES_DIR}/commands/INVITE.cpp
IRCSERV_SOURCES+=${SOURCES_DIR}/commands/JOIN.cpp
IRCSERV_SOURCES+=${SOURCES_DIR}/commands/KICK.cpp
IRCSERV_SOURCES+=${SOURCES_DIR}/commands/MODE.cpp
IRCSERV_SOURCES+=${SOURCES_DIR}/commands/NICK.cpp
IRCSERV_SOURCES+=${SOURCES_DIR}/commands/PART.cpp
IRCSERV_SOURCES+=${SOURCES_DIR}/commands/PASS.cpp
IRCSERV_SOURCES+=${SOURCES_DIR}/commands/PONG.cpp
IRCSERV_SOURCES+=${SOURCES_DIR}/commands/PRIVMSG.cpp
IRCSERV_SOURCES+=${SOURCES_DIR}/commands/TOPIC.cpp
IRCSERV_SOURCES+=${SOURCES_DIR}/commands/UNKNOWN.cpp
IRCSERV_SOURCES+=${SOURCES_DIR}/commands/USER.cpp

IRCSERV_OBJECTS := $(IRCSERV_SOURCES:$(SOURCES_DIR)/%.cpp=$(OBJECTS_DIR)/%.o)

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.cpp
	mkdir -p $(dir $@)
	$(CPP) $(CXXFLAGS) -c "$<" -o "$@"


$(NAME): all

all: $(IRCSERV_OBJECTS)
	$(CPP) -o $(NAME) $(IRCSERV_OBJECTS)

clean:
	rm -rf $(OBJECTS_DIR)

fclean: clean
	rm -rf $(NAME)
	rm -rf $(BNAME)

re: fclean all

bot: all $(BOT_OBJECTS)
	$(CPP) -o $(BNAME) $(BOT_OBJECTS)

test: all
	./ircserv "6000" "pass"

bonus: bot
b: bonus
f: fclean
t: test

.PHONY: all clean fclean bonus $(NAME) $(BNAME) bot
