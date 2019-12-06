/*
 * Socket.cpp
 *
 *  Created on: Oct 1, 2019
 *      Author: shreya
 */

#include "Socket.h"
#include <string.h>

using std::cout;
using std::string;

bool Socket::createSocket(SocketData& s)
{
	bool res = true;

	s.iSocket = -1;
	memset(&s.sockAddr, 0, sizeof(s.sockAddr));

	s.iSocket = socket(AF_INET, SOCK_STREAM, 0 );

	if (!isValidSocket(s.iSocket) )
	{
		cout << "\nError in " << __func__;
		res =  false;
	}

	return res;
}

bool Socket::bind(SocketData& s)
{
	bool res = true;

	if (!isValidSocket(s.iSocket) )
	{
		cout << "\nError in " << __func__;
		res = false;
	}

	s.sockAddr.sin_family      = AF_INET;
	s.sockAddr.sin_addr.s_addr = INADDR_ANY;
	s.sockAddr.sin_port        = htons(s.iPortNum);

	int ret = ::bind(s.iSocket, (struct sockaddr*) &s.sockAddr, sizeof(s.sockAddr));
	//std::cout << "\nbind_returned: " << ret;

	if ( ret == -1 )
	{
		cout << "\nError in " << __func__;
		res = false;
	}

	return res;
}

bool Socket::listen(SocketData& s)
{
	bool res = true;

	if ( !isValidSocket(s.iSocket) )
	{
		cout << "\nError in " << __func__;
		res = false;
	}

	int ret = ::listen(s.iSocket, MAXCONNECTIONS);
	if ( ret == -1 )
	{
		cout << "\nError in " << __func__;
		res = false;
	}

	cout << "\nServer is listening...\n";
	return res;
}

bool Socket::accept(SocketData& oldSock, SocketData& newSock)
{
	bool res = true;
	int addr_length = sizeof (oldSock.sockAddr);
	newSock.iSocket = ::accept(oldSock.iSocket, (sockaddr*)&oldSock.sockAddr, (socklen_t*)&addr_length );

	if (newSock.iSocket <= 0)
		res = false;

	return res;
}

bool Socket::setSocketOptions(SocketData& s)
{
	bool res = true;

	int on = 1;
	if(setsockopt(s.iSocket, SOL_SOCKET, SO_REUSEADDR, (const char*)&on, sizeof(on)) == -1 )
	{
		cout << "\nError in " << __func__;
		res =  false;
	}

	return res;
}

bool Socket::connect(SocketData& s)
{
	bool res = true;

	if (!isValidSocket(s.iSocket))
			return false;

	//cout << "\n" << s.iSocket << ", " << s.iPortNum;

	s.sockAddr.sin_family      = AF_INET;
	s.sockAddr.sin_port        = htons(s.iPortNum);

	int status = inet_pton(AF_INET, s.sHostname.c_str(), &s.sockAddr.sin_addr);

	if ( errno == EAFNOSUPPORT )
	{
		cout << "\nError in " << __func__;
		return false;
	}

	status = ::connect(s.iSocket, (struct sockaddr*)&s.sockAddr, sizeof(s.sockAddr));

	if ( status != 0 )
	{
		cout << "\nError in " << __func__;
		res = false;
	}

	return res;
}

bool Socket::sendData(SocketData& s, string sData)
{
	bool res = true;

	//cout << "\n" << s.iSocket << ", " << s.iPortNum;
	int status = write(s.iSocket, sData.c_str(), sData.size());
	if ( status == -1 )
	{
		cout << "\nError in " << __func__;
		res =  false;
	}
	return res;
}

bool Socket::recvData(SocketData& s, string& sData)
{
	bool res = true;

	char buffer[ MAXRECV+1];
	memset (buffer, 0, MAXRECV + 1);

	//cout << "\n" << s.iSocket << ", " << s.iPortNum;
	int status = read(s.iSocket, buffer, MAXRECV);
	if(status == -1 )
	{
		cout << "\nError in " << __func__;
		res =  false;
	}

	sData = buffer;
	return res;
}

bool Socket::isValidSocket(int& sockFd)
{
	return (sockFd != -1);
}

