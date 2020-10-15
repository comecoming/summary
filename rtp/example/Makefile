USR_PREFIX = /opt/x64_lib
#USR_PREFIX := /usr/local

all:
	g++ client.cpp RTPSessionUtils.cpp -o client -I./ -I$(USR_PREFIX)/include -L$(USR_PREFIX)/lib -ljrtp -ljthread -lpthread -I$(USR_PREFIX)/include/jrtplib3
	g++ server.cpp RTPSessionUtils.cpp -o server -I./ -I$(USR_PREFIX)/include -L$(USR_PREFIX)/lib -ljrtp -ljthread -lpthread -I$(USR_PREFIX)/include/jrtplib3
