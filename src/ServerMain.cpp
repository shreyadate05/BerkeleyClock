/*
 * ClientMain.cpp
 *
 *  Created on: Oct 1, 2019
 *      Author: shreya
 */

#include "Server.h"

int main(int argc, char* argv[])
{
	Servers node;

	if (argc != 3)
	{
		std::cout << "\nCommand to run servers: ./server <port_number> <server_name> <server_time>\n";
		return -1;
	}

	node.setPortNum(argv[1]);
	node.setName(argv[2]);
	node.createServers();
	node.connectWithMaster();

	std::cout << std::endl;
	return 0;
}
