/*
#  ____   ____    ____         ___ ____   ____ _     _
# |    |  ____>   ____>  |    |        | <____  \   /
# |____| |    \   ____>  | ___|    ____| <____   \_/	ORBISDEV Open Source Project.
#------------------------------------------------------------------------------------
# Copyright 2010-2020, orbisdev - http://orbisdev.github.io
# Licenced under MIT License
# Review README & LICENSE files for further details.
*/

#ifndef _ORBIS_LIBSCEVIDEOOUT_H_
#define _ORBIS_LIBSCEVIDEOOUT_H_

#pragma once

#include <stdint.h>
#include <orbis/libkernel.h>
#include <orbis/libSceUserService.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SceVideoOutBufferAttribute {
	int32_t format;
	int32_t tmode;
	int32_t aspect;
	uint32_t width;
	uint32_t height;
	uint32_t pixelPitch;
	uint64_t reserved[2];
} SceVideoOutBufferAttribute;

typedef struct SceVideoOutFlipStatus {
	uint64_t num;
	uint64_t ptime;
	uint64_t stime;
	int64_t flipArg;
	uint64_t reserved[2];
	int32_t numGpuFlipPending;
	int32_t numFlipPending;
	int32_t currentBuffer;
	uint32_t reserved1;
} SceVideoOutFlipStatus;

int sceVideoOutOpen(SceUserServiceUserId userId, int type, int index, const void *param);
int sceVideoOutClose(int handle);
int sceVideoOutRegisterBuffers(int handle, int initialIndex, void * const *addr, int numBuf, const SceVideoOutBufferAttribute *attr);
int sceVideoOutUnregisterBuffers(int handle, int indexAttr);
int sceVideoOutSubmitFlip(int handle, int indexBuf, unsigned int flipMode, int64_t flipArg);
void sceVideoOutSetBufferAttribute(SceVideoOutBufferAttribute *attr, unsigned int format, unsigned int tmode,unsigned int aspect, unsigned int width, unsigned int height, unsigned int pixelPitch);
int sceVideoOutSetFlipRate(int handle, int flipRate);
int sceVideoOutAddFlipEvent(SceKernelEqueue eq, int handle, void *data);
int sceVideoOutGetFlipStatus(int handle, SceVideoOutFlipStatus *status);


#ifdef __cplusplus
}
#endif

#endif
