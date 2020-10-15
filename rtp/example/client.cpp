
#include <iostream>
#include "RTPSessionUtils.h"
using namespace jrtplib;
int main()
{
	int status;
	RTPSessionUtils sess;
	status = sess.CreateDefault(8000, "192.168.1.100", 9000);//local port, dest ip, dest port
	if(status)
	{
		std::cout << "RTP error:" << RTPGetErrorString(status) << std::endl;
		return -1;
	}
 
	while (1)
	{
		std::string buf;
		std::cout << "Input send data:" ;
		std::cin >> buf;
 
		sess.SendPacket((void*)buf.c_str(), buf.length(), 0, false, 0);
	}
 
	return 0;
}
