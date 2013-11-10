#include "SharedMemory.h"
#include <stdio.h>
#include <string.h>
#include <iostream>
using namespace std;

SharedMemory::SharedMemory(vector<int> keys, const int sizeInBytesArg): sizeInBytes(sizeInBytesArg){
	numSemaphores = keys.size() - 1;
	initShm(keys[0]);
	keys.erase(keys.begin());
	initSems(keys, numSemaphores);
}


int*
SharedMemory::getShm() const {
	return shm;
}

void
SharedMemory::initShm(key_t keyShm) {
	int flag = SHM_R | SHM_W;
	int shmid = shmget(keyShm, sizeInBytes, flag);

	if (shmid < 0) {
		shmid = shmget(keyShm, sizeInBytes, flag | IPC_CREAT);
		if (shmid < 0) {
		perror("shmget | IPC_CREAT");
		}
	}
	shm = (int *)shmat(shmid, /*addr*/NULL, /*flag*/0);
	if (shm == NULL) {
		perror("shmat");
		exit(1);
	}
}

void
SharedMemory::initSems(vector<key_t> keysSems, int numSemaphores) {
	for (int semIndex = 0; semIndex < numSemaphores; semIndex++) {
		key_t keySem =  keysSems[semIndex];
		int semId =  semget(keySem, 2, IPC_CREAT | OBJ_PERMS);
		if(BinarySems::initSemAvailable(semId, MATCH_WRITE_SEM) == -1) {
			cout << "Problem initSemAvailable\n";
			exit(-1);
		}
		if(BinarySems::initSemInUse(semId, PUB_READ_SEM) ==- 1) {
			cout << "Problem initSemInUse\n";
			exit(-2);
		}
		semIds.push_back(semId);
	}
}

void
SharedMemory::writeTo(void* ptr) {

	vector <int>::const_iterator semIdIter;
	for (semIdIter = semIds.begin(); semIdIter!=semIds.end(); ++semIdIter) {
		BinarySems::reserveSem(*semIdIter, MATCH_WRITE_SEM);
	}
	memset(shm, 0, sizeInBytes);
	memcpy(shm, ptr, sizeInBytes);

	for (semIdIter = semIds.begin(); semIdIter!=semIds.end(); ++semIdIter) {
		BinarySems::releaseSem(*semIdIter, PUB_READ_SEM);
	}

}

void
SharedMemory::readFrom(int semId, void* data) {

	BinarySems::reserveSem(semId, PUB_READ_SEM);
	memcpy(data, shm, sizeInBytes);
	BinarySems::releaseSem(semId, MATCH_WRITE_SEM);

}

int
SharedMemory::getSemId(int index) const {
	return semIds[index];
}

SharedMemory::SharedMemory() {
	// dummy
}
