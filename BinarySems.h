/*
 * BinarySems.h
 *
 *  Created on: Nov 6, 2013
 *      Author: viktor
 */

#ifndef BINARYSEMS_H_
#define BINARYSEMS_H_

#include <sys/sem.h>

/**
 * Utility function with static methods for binary semaphores
 */

const bool bsUseSemUndo = false;
const bool bsRetryOnEintr = true;
class BinarySems {
public:
	BinarySems();
	static int initSemAvailable(int semId, int semNum);
	static int initSemInUse(int semId, int semNum);
	static int reserveSem(int semId, int semNum);
	static int releaseSem(int semId, int semNum);
	virtual ~BinarySems();
};

#endif /* BINARYSEMS_H_ */
