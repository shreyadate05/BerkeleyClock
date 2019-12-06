/*
 * TimeDaemon.cpp
 *
 *  Created on: Oct 1, 2019
 *      Author: shreya
 */
#include "TimeDaemon.h"

using std::vector;
using std::string;
using std::stringstream;

using std::cout;
using std::ifstream;
using std::map;
using std::endl;
using std::setw;

#define MAX_NUM_OF_SECONDS (5*365*24*60*60) // number of seconds in 5 years

vector<string> TimeDaemon::StringSplitByDelim(std::string str, char& cDeLim)
{
	vector<string> vTokens;
	stringstream ss(str);
	string item;

	while (std::getline(ss, item, cDeLim))
	{
		if(item != " " || item != "\n" || item!= "\r")
			vTokens.push_back (item);
	}

//	for (int i=0; i< vTokens.size(); i++)
//	{
//		cout << "\nvToken: " << vTokens[i];
//	}

	return vTokens;
}

void TimeDaemon::calculateDrift()
{
	int sum = 0;
	for (int i = 0; i < vOffsets.size(); i++)
	{
		sum += stoi(vOffsets[i]);
	}
	iAverage = sum/(vOffsets.size()+1);

	for (int i = 0; i < vOffsets.size(); i++)
	{
		int adjustedDrift = stoi(vOffsets[i])*-1;
		adjustedDrift += iAverage;
		vAdjustedDrifts.push_back(adjustedDrift);
	}

	iAdjustedDaemonTime = iAverage + stoi(sDaemonTime);
}

void TimeDaemon::setDaemonTime(string sTime)
{
	this->sDaemonTime = sTime;
}

bool TimeDaemon::readInputFile(string sFile)
{
	bool res = true;
	sInputFile = sFile;
	char cDelim = ',';

	std::ifstream file(sInputFile.c_str());
	std::string   line;
	try
	{
		while(std::getline(file, line))
		{
			std::stringstream lineStream(line);
			string value;
			string sInputRow = "";
			// Read single row of space separated vector
			while(lineStream >> value)
			{
				sInputRow += " " + value;
			}

			vector<string> vTemp = StringSplitByDelim(sInputRow, cDelim);
			vNames.push_back(vTemp[0]);
			vPorts.push_back(vTemp[1]);
			//vLocalTimes.push_back(vTemp[2]);
		}
	}
	catch(...)
	{
		std::cout << "\nException thrown while reading client transactions in " << __func__;
		res = false;
	}

	return res;
}

bool TimeDaemon::startMaster()
{
	bool res = true;

	for (int i = 0; i < vNames.size(); i++)
	{
		SocketData socket;
		socket.iPortNum  = stoi(vPorts[i]);
		socket.sHostname = "localhost";
		vSockets.push_back(socket);

		if (!Socket::createSocket(vSockets[vSockets.size()-1]))
		{
			cout << "\nError in " << __func__;
			res =  false;
		}

		if (!Socket::connect(vSockets[vSockets.size()-1]))
		{
			cout << "\nError in " << __func__;
			res =  false;
		}

		string buffer;
		Socket::recvData(vSockets[vSockets.size()-1], buffer);
		cout << "\nConnected to server " << buffer.c_str();
	}

	cout << "\nDaemon time is: " << sDaemonTime;

	for (int i = 0; i < vSockets.size(); i++)
	{
		Socket::sendData(vSockets[i], sDaemonTime);
		string sClient;
		Socket::recvData(vSockets[i], sClient);
		cout << "\nOffset for " << vNames[i] << " " << sClient.c_str();
		vOffsets.push_back(sClient);
	}

	calculateDrift();
	sleep(1);
	cout << "\n";
	cout << "\nAdjusted Daemon time is: " << iAdjustedDaemonTime;
	for (int i = 0; i < vAdjustedDrifts.size(); i++)
	{
		string sAdjustedTime = std::to_string(vAdjustedDrifts[i]);
		Socket::sendData(vSockets[i], sAdjustedTime);
	}

//	for(int i = 0; i < vNames.size(); i++)
//	{
//		string command = "fuser -k " + vPorts[i] + "/tcp";
//		system(command.c_str());
//	}

	return res;
}





