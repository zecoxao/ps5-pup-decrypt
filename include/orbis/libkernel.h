/*
#  ____   ____    ____         ___ ____   ____ _     _
# |    |  ____>   ____>  |    |        | <____  \   /
# |____| |    \   ____>  | ___|    ____| <____   \_/	ORBISDEV Open Source Project.
#------------------------------------------------------------------------------------
# Copyright 2010-2020, orbisdev - http://orbisdev.github.io
# Licenced under MIT License
# Review README & LICENSE files for further details.
*/

#ifndef _ORBIS_LIBKERNEL_H_
#define _ORBIS_LIBKERNEL_H_


#pragma once

#include <stdint.h>
#include <sys/time.h>
#include <sys/types.h>

//#include <sys/event.h>

#ifdef __cplusplus
extern "C" {
#endif

struct kevent {
	uintptr_t	ident;		/* identifier for this event */
	short		filter;		/* filter for event */
	u_short		flags;
	u_int		fflags;
	intptr_t	data;
	void		*udata;		/* opaque user data identifier */
};


#ifndef MAP_TYPE
	#define MAP_TYPE 0x0f
#endif

typedef struct SceKernelModuleSegmentInfo
{
    void *address;
    uint32_t size;
    int32_t prot;
}
SceKernelModuleSegmentInfo;

typedef struct SceKernelModuleInfo
{
	size_t size;
	char name[256];
	SceKernelModuleSegmentInfo segmentInfo[4];
	uint32_t segmentCount;
	uint8_t fingerprint[20];
}SceKernelModuleInfo;

typedef struct SceKernelModuleInfoEx {
	size_t size;
	char name[256];
	int handle;
	uint32_t tlsIndex;
	uint64_t tlsInitAddr;
	uint32_t tlsInitSize;
	uint32_t tlsSize;
	uint32_t tlsOffset;
	uint32_t tlsAlign;
	uint64_t initProcAddr;
	uint64_t finiProcAddr;
	void* reserved1;
	void* reserved2;
	uint64_t ehFrameHdrAddr;
	uint64_t ehFrameAddr;
	uint32_t ehFrameHdrSize;
	uint32_t ehFrameSize;
	SceKernelModuleSegmentInfo segmentInfo[4];
	uint32_t numSegments;
	uint32_t numRefs;
}SceKernelModuleInfoEx;

typedef struct {
	int type;                //0x00
	int req_id;              //0x04
	int priority;            //0x08
	int msg_id;              //0x0C
	int target_id;           //0x10
	int user_id;             //0x14
	int unk1;                //0x18
	int unk2;                //0x1C
	int app_id;              //0x20
	int error_num;           //0x24
	int unk3;                //0x28
	char use_icon_image_uri; //0x2C
	char message[1024];      //0x2D
	char uri[1024];          //0x42D
	char unkstr[1024];       //0x82D
} SceNotificationRequest;  //Size = 0xC30

typedef struct timeval SceKernelTimeval;
typedef unsigned int SceKernelUseconds;
typedef void *ScePthread;
typedef void *ScePthreadAttr;
typedef void *ScePthreadMutex;
typedef void *ScePthreadMutexattr;
typedef void *SceKernelSema;
typedef uint32_t SceKernelModule;

typedef int64_t SceKernelEqueue;
typedef struct kevent SceKernelEvent;

/* useless C / POSIX wrappers */
int sceKernelStat(const char *path, void * buf);
int sceKernelOpen(const char *path, int flags, int mode);
int sceKernelRead(int fd, void *buf, size_t nbyte);
int sceKernelWrite(int fd, void *buf, size_t nbyte);
int sceKernelLseek(int fd, off_t offset, int whence);
int sceKernelClose(int fd);
int sceKernelMkdir(const char *path, mode_t mode);
int sceKernelChmod(const char *path, mode_t mode);
int sceKernelGetCurrentCpu(void);
int sceKernelGettimeofday(SceKernelTimeval *tp);
uint64_t sceKernelGetProcessTime();
int sceKernelUsleep(unsigned int microseconds);
int scePthreadCancel(ScePthread thread);
int scePthreadCreate(ScePthread *thread, const ScePthreadAttr *attr, void *(*entry)(void *), void *arg, const char *name);
int scePthreadDetach(ScePthread thread);
int scePthreadJoin(ScePthread thread, void **value_ptr);
int scePthreadMutexDestroy(ScePthreadMutex *mutex);
int scePthreadMutexInit(ScePthreadMutex *mutex, const ScePthreadMutexattr *attr, const char *name);
int scePthreadMutexLock(ScePthreadMutex *mutex);
int scePthreadMutexTimedlock(ScePthreadMutex *mutex, SceKernelUseconds usec);
int scePthreadMutexTrylock(ScePthreadMutex *mutex);
int scePthreadMutexUnlock(ScePthreadMutex *mutex);
ScePthread scePthreadSelf(void);
uint64_t sceKernelGetProcessTime(void);
unsigned int sceKernelSleep(unsigned int seconds);
void scePthreadExit(void *value);
void scePthreadYield(void);
int scePthreadGetprio(ScePthread thread, int *p);
int scePthreadSetprio(ScePthread thread, int p);
int scePthreadGetname(ScePthread thread, char * name);

int sceKernelCreateSema(SceKernelSema *s, const char *name, uint32_t attr, int count, int maxCount, void *);
int sceKernelDeleteSema(SceKernelSema s);
int sceKernelPollSema(SceKernelSema s, int count);
int sceKernelWaitSema(SceKernelSema s, int count, SceKernelUseconds *t);
int sceKernelSignalSema(SceKernelSema s, int signal);

int sceKernelCreateEqueue(SceKernelEqueue *eq, const char *name);
int sceKernelDeleteEqueue(SceKernelEqueue eq);
int sceKernelAddUserEvent(SceKernelEqueue eq, int id);
int sceKernelAddReadEvent(SceKernelEqueue eq, int fd, size_t size, void *data);
int sceKernelWaitEqueue(SceKernelEqueue eq, SceKernelEvent *ev, int num, int *out, SceKernelUseconds *timo);   

size_t sceKernelGetDirectMemorySize();

/* more interresting wrappers */
int sceKernelAllocateDirectMemory(off_t, off_t, size_t, size_t, int, off_t *);
int sceKernelMapMainDirectMemory(size_t, size_t, int, off_t *);
int sceKernelMapDirectMemory(void **, size_t, int, int, off_t, size_t);
int sceKernelMapNamedSystemFlexibleMemory(void** , size_t, int, int, const char*);
int sceKernelMprotect(const void *, size_t, int);
int sceKernelReserveVirtualRange(void **, size_t, int, size_t);
int sceKernelReleaseFlexibleMemory(void *, size_t);
int sceKernelMunmap(void *, size_t);

/* sce own syscall wrappers (usefull) */
int sceKernelLoadStartModule(const char *name, size_t argc, const void *argv, uint32_t flags, void *, int *result);
int sceKernelDlsym(SceKernelModule handle, const char *symbol, void **address);
int sceKernelGetModuleList(SceKernelModule *array, size_t size, size_t *available);
int sceKernelGetModuleInfo(SceKernelModule handle, SceKernelModuleInfo *info);
int sceKernelGetModuleInfoByName(const char* name, SceKernelModuleInfo* info);
int sceKernelStopUnloadModule(SceKernelModule handle, size_t argc, const void *argv, uint32_t flags, void *, int *result);

int sceKernelSync();
const char *sceKernelGetFsSandboxRandomWord();

int sceKernelJitCreateSharedMemory(int flags, size_t size, int protection, int *destinationHandle);
int sceKernelJitCreateAliasOfSharedMemory(int handle, int protection, int *destinationHandle);
int sceKernelJitMapSharedMemory(int handle, int protection, void **destination);

int sceKernelIccSetBuzzer(int mode);

int sceKernelDebugOutText(int dbg_channel, const char* text);

int sceKernelSendNotificationRequest(int device, SceNotificationRequest *req, size_t size, int blocking);

#ifdef __cplusplus
}
#endif

#endif
