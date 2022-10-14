/*
#  ____   ____    ____         ___ ____   ____ _     _
# |    |  ____>   ____>  |    |        | <____  \   /
# |____| |    \   ____>  | ___|    ____| <____   \_/	ORBISDEV Open Source Project.
#------------------------------------------------------------------------------------
# Copyright 2010-2020, orbisdev - http://orbisdev.github.io
# Licenced under MIT License
# Review README & LICENSE files for further details.
*/

#ifndef _ORBIS_LIBSCESYSMODULE_H_
#define _ORBIS_LIBSCESYSMODULE_H_

#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

int sceSysmoduleIsLoaded(uint16_t id);
int sceSysmoduleLoadModule(uint16_t id);
int sceSysmoduleUnloadModule(uint16_t id);

#define SCE_SYSMODULE_INTERNAL_SYS_CORE 0x80000004
#define SCE_SYSMODULE_INTERNAL_NETCTL 0x80000009
#define SCE_SYSMODULE_INTERNAL_HTTP 0x8000000A
#define SCE_SYSMODULE_INTERNAL_SSL 0x8000000B
#define SCE_SYSMODULE_INTERNAL_NP_COMMON 0x8000000C
#define SCE_SYSMODULE_INTERNAL_SYSTEM_SERVICE 0x80000010
#define SCE_SYSMODULE_INTERNAL_USER_SERVICE 0x80000011
#define SCE_SYSMODULE_INTERNAL_APPINSTUTIL 0x80000014
#define SCE_SYSMODULE_INTERNAL_NET 0x8000001C
#define SCE_SYSMODULE_INTERNAL_IPMI 0x8000001D
#define SCE_SYSMODULE_INTERNAL_VIDEO_OUT 0x80000022
#define SCE_SYSMODULE_INTERNAL_PAD 0x80000024
#define SCE_SYSMODULE_INTERNAL_AUDIO_OUT 0x80000001
#define SCE_SYSMODULE_INTERNAL_IME 0x80000095
#define SCE_SYSMODULE_INTERNAL_GNM_DRIVER 0x80000052
#define SCE_SYSMODULE_INTERNAL_BGFT 0x8000002A
#define SCE_SYSMODULE_INTERNAL_PRECOMPILED_SHADERS 0x80000064

int sceSysmoduleLoadModuleInternal(uint32_t id);
int sceSysmoduleUnloadModuleInternal(uint32_t id);

#ifdef __cplusplus
}
#endif

#endif
