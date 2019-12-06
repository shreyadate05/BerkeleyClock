/*
 * Processes.cpp
 *
 *  Created on: Oct 29, 2019
 *      Author: shreya
 */

#include "Server.h"
#include <pthread.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <map>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>

using std::cout;
using std::string;
using std::vector;
using std::map;

#define MAX_NUM_OF_SECONDS (5*365*24*60*60)

struct tm* GetTimeAndDate()
{
    unsigned int now_seconds  = (unsigned int)time(NULL);
    unsigned int rand_seconds = (rand()*rand())%(MAX_NUM_OF_SECONDS+1);
    time_t       rand_time    = (time_t)(now_seconds-rand_seconds);
    return localtime(&rand_time);
}

bool Servers::setPortNum(string sPort)
{
	bool res = true;

	this->sPort = sPort;

	return res;
}

bool Servers::setName(string sName)
{
	bool res = true;

	this->sName = sName;

	return res;
}

bool Servers::createServers()
{
	bool res = true;

	socket.iPortNum = stoi(sPort);

	if (!Socket::createSocket(socket))
	{
		cout << "\nError in " << __func__;
		return false;
	}

	if (!Socket::bind(socket))
	{
		cout << "\nError in " << __func__;
		return false;
	}

	if (!Socket::listen(socket))
	{
		cout << "\nError in " << __func__;
		return false;
	}

	return res;
}

bool Servers::connectWithMaster()
{
	bool res = true;

	SocketData* newSocket = new SocketData();
	newSocket->iPortNum = socket.iPortNum;
	newSocket->sHostname = socket.sHostname;
	Socket::accept(socket, *newSocket);

	string message = "Hi from " + sName;
	Socket::sendData(*newSocket, message);

	string sServerTime;
	srand(socket.iPortNum);
	int iMyTime = rand()%100;

	Socket::recvData(*newSocket, sServerTime);
	cout << "\n[" << sName << "] Time daemon clock is: " << sServerTime;

	string sDiff = std::to_string(iMyTime - stoi(sServerTime));
	cout << "\n[" << sName << "] Server clock is: " << iMyTime;

	Socket::sendData(*newSocket, sDiff);

	Socket::recvData(*newSocket, sDiff);
	cout << "\n[" << sName << "] Offset for server is: " << sDiff;
	cout << "\n[" << sName << "] Adjusted time: " << iMyTime+stoi(sDiff) << std::endl;

	return res;
}
