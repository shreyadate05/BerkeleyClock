/*
 * Slaves.h
 *
 *  Created on: Oct 29, 2019
 *      Author: shreya
 */

#ifndef SERVER_H_
#define SERVER_H_

#include <unistd.h>
#include <pthread.h>
#include <vector>
#include <map>
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include "SocketDefs.h"
#include "Socket.h"

const int MAXLINES = 500;

class Servers
{
	std::string sLocalTimes;
	std::string sName;
	std::string sPort;
	SocketData socket;

   public:

	std::vector<std::string> StringSplitByDelim(std::string str, char& cDeLim);

	bool setPortNum(std::string sPort);
	bool setName(std::string sName);

	bool createServers();
	bool connectWithMaster();

};

#endif /* SERVER_H_ */
