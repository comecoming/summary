#include "rtpsession.h"
#include "rtppacket.h"
#include "rtpudpv4transmitter.h"
#include "rtpipv4address.h"
#include "rtpsessionparams.h"
#include "rtperrors.h"
#ifndef WIN32
#include <netinet/in.h>
#include <arpa/inet.h>
#else
#include <winsock2.h>
#endif // WIN32
#include "rtpsourcedata.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
 
namespace jrtplib
{
	class RTPSessionUtils : public RTPSession
	{
		typedef RTPSession base_type;
	public:
		RTPSessionUtils();
		~RTPSessionUtils();
 
		int AddDestination(const std::string& ip, uint16_t port);
		int DeleteDestination(const std::string& ip, uint16_t port);
		int CreateDefault(uint16_t port);
		int CreateDefault(uint16_t port, const std::string &ip, uint16_t dest_port);
		int RecvPacket(char *buf);
	private:
		int AccessIsBegin;
	};
}
 
