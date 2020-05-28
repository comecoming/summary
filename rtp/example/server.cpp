#include <iostream>
#include "RTPSessionUtils.h"
#include <unistd.h>
using namespace jrtplib;
 
int main()
{
	int status;
	RTPSessionUtils sess;
	status = sess.CreateDefault(9000, "192.168.6.131", 8000);//local port, dest ip, dest port
	if(status)
	{
		std::cout << "RTP error:" << RTPGetErrorString(status) << std::endl;
		return 0;
	}


	//status = sess.CreateDefault(9000);//local port
	//status = sess.AddDestination("127.0.0.1", 8888);
	//if(status)
	//{
	//	std::cout << "RTP error:" << RTPGetErrorString(status) << std::endl;
	//	return 0;
	//}
 

	while (1)
	{

		int ret;
		char buf[100] = {0};
 
		ret = sess.RecvPacket(buf);
		if (ret > 0)
			std::cout << "recv:" << buf << std::endl;

		usleep(10*1000);
	}
 
	return 0;
}
