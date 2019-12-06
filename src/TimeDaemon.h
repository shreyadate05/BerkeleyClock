/*
 * TimeDaemon.h
 *
 *  Created on: Oct 1, 2019
 *      Author: shreya
 */

#ifndef TIMEDAEMON_H_
#define TIMEDAEMON_H_

#include "SocketDefs.h"
#include "Socket.h"
#include <string.h>
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


class TimeDaemon
{
	SocketData socketData;
	std::string sDaemonTime;
	int iAverage;
	int iAdjustedDaemonTime;

	std::string sInputFile;
	std::vector<SocketData> vSockets;
	std::vector<std::string> vNames;
	std::vector<std::string> vPorts;
	std::vector<std::string> vLocalTimes;
	std::vector<std::string> vOffsets;
	std::vector<int> vAdjustedDrifts;

	public:

		bool readInputFile(std::string sFile);
		bool startMaster();
		void setDaemonTime(std::string sTime);
		void calculateDrift();

		std::vector<std::string> StringSplitByDelim(std::string str, char& cDeLim);
};


#endif /* TIMEDAEMON_H_ */
