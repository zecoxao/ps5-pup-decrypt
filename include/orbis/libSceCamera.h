/*
#  ____   ____    ____         ___ ____   ____ _     _
# |    |  ____>   ____>  |    |        | <____  \   /
# |____| |    \   ____>  | ___|    ____| <____   \_/	ORBISDEV Open Source Project.
#------------------------------------------------------------------------------------
# Copyright 2010-2020, orbisdev - http://orbisdev.github.io
# Licenced under MIT License
# Review README & LICENSE files for further details.
*/

#ifndef _ORBIS_LIBSCECAMERA_H_
#define _ORBIS_LIBSCECAMERA_H_

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

//from libSceCamera.sprx firmware 1.76. Other can change
typedef struct SceCameraStartParameter
{
	uint32_t size; //0x0  <- set to  0x18 before call 24 bytes it is a check hardcoded in libSceCamera.sprx
	uint32_t unknown1;//0x4
	uint32_t unknown2;//0x8
	void * unknown3;//0xc
}
SceCameraStartParameter;

typedef struct SceCameraFrameData
{
	uint32_t size; //0x0  <- set to  size< 0xb1+0x158=0x209 (521) it is a check hardcoded in libSceCamera.sprx.I suppose size 520 it's the worst case to pass the check
	uint32_t unknown1;//0x4
	uint32_t unknown2[32];//0x8
	void* pleft[4];//0x88 video frame pointers for left camera 4 resolution modes
	void* pright[4];//0xa8 video frame pointers for right camera 4 resolution modes
	uint32_t sizeleft[4]; //0xc8 video frame size for left camera 4 resolution modes
	uint32_t sizeright[4];//0xd8 video frame size for right camera 4 resolution modes
	uint32_t statusleft;//0xe8
	uint32_t statusright;//0xec
	uint32_t unknown3[70];//0xf0
}
SceCameraFrameData;

typedef struct SceCameraDeviceInfo
{
	uint32_t size; //0x0  <- set to 0x10 before call 24 bytes it is a check hardcoded in libSceCamera.sprx
	uint32_t revision;//0x4  <- check set to 0x1 before call
	uint32_t unknown1;//0x8
	uint32_t unknown2;//0xc
}
SceCameraDeviceInfo;

typedef struct SceCameraConfig
{
	uint32_t size; //0x0  <- set to  0x68 it is a check hardcoded in libSceCamera.sprx
	uint32_t unknown[100]; //0x4
}
SceCameraConfig;

int sceCameraClose(int handle);
int sceCameraGetConfig(int handle, SceCameraConfig *config);
int sceCameraGetDeviceConfig(int handle, SceCameraConfig *config);
int sceCameraGetDeviceInfo(int handle, SceCameraDeviceInfo *info);
int sceCameraGetFrameData(int handle, SceCameraFrameData *frame);
int sceCameraIsAttached(int index);
int sceCameraOpen(int userid, int type, int index, void *);
int sceCameraSetConfig(int handle, SceCameraConfig *config);
int sceCameraStart(int handle, SceCameraStartParameter *param);
int sceCameraStop(int handle);

/* released debug output */
int64_t sceCameraProcConfigStop();
int64_t sceCameraDevStop();

/* guessed from sceCameraSetCalibData */
int64_t sceCameraGetCalibrationData();

/* psxdev unreversed */
int64_t sceCameraAudioOpen();
int64_t sceCameraCloseByHandle();
int64_t sceCameraGetAttribute();
int64_t sceCameraGetAutoExposureGain();
int64_t sceCameraGetAutoWhiteBalance();
int64_t sceCameraGetContrast();
int64_t sceCameraGetDefectivePixelCancellation();
int64_t sceCameraGetExposureGain();
int64_t sceCameraGetGamma();
int64_t sceCameraGetHue();
int64_t sceCameraGetLensCorrection();
int64_t sceCameraGetSaturation();
int64_t sceCameraGetSharpness();
int64_t sceCameraGetWhiteBalance();
int64_t sceCameraIsValidFrameData();
int64_t sceCameraOpenByModuleId();
int64_t sceCameraSetAttribute();
int64_t sceCameraSetAutoExposureGain();
int64_t sceCameraSetAutoWhiteBalance();
int64_t sceCameraSetCalibData();
int64_t sceCameraSetConfigInternal();
int64_t sceCameraSetContrast();
int64_t sceCameraSetDefectivePixelCancellation();
int64_t sceCameraSetExposureGain();
int64_t sceCameraSetGamma();
int64_t sceCameraSetHue();
int64_t sceCameraSetLensCorrection();
int64_t sceCameraSetSaturation();
int64_t sceCameraSetSharpness();
int64_t sceCameraSetWhiteBalance();
int64_t sceCameraStartByHandle();
int64_t sceCameraStopByHandle();

#ifdef __cplusplus
}
#endif

#endif
