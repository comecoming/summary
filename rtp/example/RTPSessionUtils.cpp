#include "RTPSessionUtils.h"
 
namespace jrtplib{
	RTPSessionUtils::RTPSessionUtils()
	{
#ifdef WIN32
		WSADATA dat;
		WSAStartup(MAKEWORD(2,2),&dat);
#endif // WIN32
		AccessIsBegin = 0;
	}
 
	RTPSessionUtils::~RTPSessionUtils()
	{
		base_type::EndDataAccess();
#ifdef WIN32
		WSACleanup();
#endif // WIN32
	}
 
	int RTPSessionUtils::CreateDefault(uint16_t port)
	{
		int status;
		RTPUDPv4TransmissionParams transparams;
		RTPSessionParams sessparams;
		sessparams.SetOwnTimestampUnit(1.0/10.0);
		transparams.SetPortbase(port);
		status = base_type::Create(sessparams, &transparams);
 
		base_type::SetDefaultPayloadType(0);
		base_type::SetDefaultTimestampIncrement(0);
		base_type::SetDefaultMark(false);

		return status;
	}

	int RTPSessionUtils::CreateDefault(uint16_t port, const std::string &ip, uint16_t dest_port)
	{
		int status;
		RTPUDPv4TransmissionParams transparams;
		RTPSessionParams sessparams;
		sessparams.SetOwnTimestampUnit(1.0/10.0);
        	sessparams.SetAcceptOwnPackets(true);
		transparams.SetPortbase(port);
		status = base_type::Create(sessparams, &transparams);
 
		base_type::SetDefaultPayloadType(0);
		base_type::SetDefaultTimestampIncrement(0);
		base_type::SetDefaultMark(false);
		base_type::AddDestination(RTPIPv4Address(ntohl(inet_addr(ip.c_str())), dest_port));

		return status;
	}

	int RTPSessionUtils::AddDestination(const std::string& ip, uint16_t port)
	{
		base_type::AddDestination(RTPIPv4Address(ntohl(inet_addr(ip.c_str())), port));

		return 0;
	}
 
	int RTPSessionUtils::DeleteDestination(const std::string& ip, uint16_t port)
	{
		base_type::DeleteDestination(RTPIPv4Address(ntohl(inet_addr(ip.c_str())), port));

		return 0;
	}
 
	int RTPSessionUtils::RecvPacket(char *buf)
	{
		int len = 0;
		char *data;
		if (buf == NULL) return 0;
		base_type::BeginDataAccess();
 
		// check incoming packets
		if (base_type::GotoFirstSourceWithData())
		{
			RTPPacket *pack;
 
			if ((pack = base_type::GetNextPacket()) != NULL)
			{
				len = pack->GetPayloadLength();
				data = (char *)pack->GetPayloadData();
				memcpy(buf, data, len);
				base_type::DeletePacket(pack);
			}
		}

		base_type::EndDataAccess();

		return len;
	}
}

