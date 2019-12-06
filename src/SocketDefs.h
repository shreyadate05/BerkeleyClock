/*
 * SocketDefs.h
 *
 *  Created on: Oct 1, 2019
 *      Author: shreya
 */

#ifndef SOCKETDEFS_H_
#define SOCKETDEFS_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <string.h>
#include <string>
#include <cstring>
#include <iostream>


const int MAXHOSTNAME = 200;
const int MAXCONNECTIONS = 10;
#define MAXRECV 500

typedef struct _SocketData
{
	int iSocket;
	int iPortNum;
	std::string sHostname;
	sockaddr_in sockAddr;

} SocketData;


#endif /* SOCKETDEFS_H_ */
