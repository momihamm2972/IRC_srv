
SOURCES_DIR=srcs/ircserv/sources
OBJECTS_DIR=srcs/ircserv/objects

CPP_SOURCES+=${SOURCES_DIR}/main.cpp
CPP_SOURCES+=${SOURCES_DIR}/tools.cpp
CPP_SOURCES+=${SOURCES_DIR}/Client.cpp
CPP_SOURCES+=${SOURCES_DIR}/Server.cpp
CPP_SOURCES+=${SOURCES_DIR}/Channel.cpp

CPP_SOURCES+=${SOURCES_DIR}/commands/INVITE.cpp
CPP_SOURCES+=${SOURCES_DIR}/commands/JOIN.cpp
CPP_SOURCES+=${SOURCES_DIR}/commands/KICK.cpp
CPP_SOURCES+=${SOURCES_DIR}/commands/MODE.cpp
CPP_SOURCES+=${SOURCES_DIR}/commands/NICK.cpp
CPP_SOURCES+=${SOURCES_DIR}/commands/PART.cpp
CPP_SOURCES+=${SOURCES_DIR}/commands/PASS.cpp
CPP_SOURCES+=${SOURCES_DIR}/commands/PONG.cpp
CPP_SOURCES+=${SOURCES_DIR}/commands/PRIVMSG.cpp
CPP_SOURCES+=${SOURCES_DIR}/commands/TOPIC.cpp
CPP_SOURCES+=${SOURCES_DIR}/commands/UNKNOWN.cpp
CPP_SOURCES+=${SOURCES_DIR}/commands/USER.cpp

all:
	@c++ ${CPP_SOURCES} -o ircserv

test: all
	./ircserv "6000" "pass"
