all:
	g++ client.cpp RTPSessionUtils.cpp -o client -I./ -I/usr/local/include -L/usr/local/lib -ljrtp -ljthread -lpthread -I/usr/local/include/jrtplib3
	g++ server.cpp RTPSessionUtils.cpp -o server -I./ -I/usr/local/include -L/usr/local/lib -ljrtp -ljthread -lpthread -I/usr/local/include/jrtplib3
