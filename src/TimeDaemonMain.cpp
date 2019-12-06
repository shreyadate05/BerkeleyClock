/*
 * CoordinatorMain.h
 *
 *  Created on: Oct 29, 2019
 *      Author: shreya
 */

#ifndef TIMEDAEMONMAIN_CPP_
#define TIMEDAEMONMAIN_CPP_

#include "TimeDaemon.h"

int main(int argc, char* argv[])
{
	TimeDaemon master;
	srand((unsigned int)time(NULL));

	if (argc != 3)
	{
		std::cout << "\nCommand to run time daemon: ./daemon <input_file> <daemon_time>\n";
		return -1;
	}

	master.readInputFile(argv[1]);
	master.setDaemonTime(argv[2]);
	master.startMaster();

	std::cout << std::endl;
	return 0;
}

#endif /* COORDINATORMAIN_CPP_ */
