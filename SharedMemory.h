#ifndef SHARED_MEMORY_H
#define SHARED_MEMORY_H

#include<sys/types.h>
#include<sys/stat.h>
#include<sys/sem.h>
#include<stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <unistd.h>
#include <vector>
#include <stdarg.h>
#include <string>

#include "BinarySems.h"
#include "messages.h"

using namespace std;

/*const int tradePubSemIndex = 1;
const int bookPubIndex = 1;
const int reportingEngineSemIndex = 2;
const int reader = 0;
const int writer = 1;*/
const int MATCH_WRITE_SEM = 0;
const int PUB_READ_SEM = 1;
#define OBJ_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP) // TODO John possible to use const instead?
/*
 * #define SHM_KEY 0x1234
#define SEM_KEY_A 0x5678 #define SEM_KEY_B 0x9678  #define SEM_KEY_C 0x7678

#define OBJ_PERMS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)

#define MATCH_WRITE_SEM 0 #define PUB_READ_SEM 1  #define PUB_SEM 2 #ifndef BUF_SIZE #define BUF_SIZE sizeof(struct TradeMessage)
#endif+

struct shmseg {
    int cnt; char buf[BUF_SIZE];
};
 *
 */


class SharedMemory {
private:
	int* shm;
	vector<int> semIds;
	int numSemaphores;
	void initShm(key_t keyShm);
	void initSems(vector<key_t> keysSems, int numSemaphores);
	int sizeInBytes;
public:
	SharedMemory(vector<int> keys, const int sizeInBytesArg);
	int* getShm() const;
	int getSemId(int index) const;
	void writeTo(void* ptr);
	void readFrom(int semId,void* data);
	SharedMemory();
};

#endif
