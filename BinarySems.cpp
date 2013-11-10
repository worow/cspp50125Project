/*
 * BinarySems.cpp
 *
 *  Created on: Nov 6, 2013
 *      Author: viktor
 */

#include "BinarySems.h"
#include <errno.h>
#include <iostream>
/*#include "semun.h"*/
using namespace std;

BinarySems::BinarySems() {

}

int
BinarySems::initSemAvailable(int semId, int semNum){
	union semun arg;
	arg.val = 1;
	return semctl(semId, semNum, SETVAL, arg);
}

int
BinarySems::initSemInUse(int semId, int semNum){
	union semun arg;
	arg.val = 0; 
	return semctl(semId, semNum, SETVAL, arg);
}

int
BinarySems::reserveSem(int semId, int semNum){
    struct sembuf sops;
    sops.sem_num = semNum;
    sops.sem_op = -1;
    sops.sem_flg = bsUseSemUndo ? SEM_UNDO : 0;

    while(semop(semId, &sops, 1) == -1) {
        if(errno != EINTR || !bsRetryOnEintr) {
            return -1;
        }
    }
    return 0;
}


int
BinarySems::releaseSem(int semId, int semNum){
    struct sembuf sops;
    sops.sem_num = semNum;
    sops.sem_op = 1;
    sops.sem_flg =  bsUseSemUndo ? SEM_UNDO : 0;
    return semop(semId, &sops, 1);
}

BinarySems::~BinarySems() {

}

