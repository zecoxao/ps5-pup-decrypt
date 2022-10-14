/*
#  ____   ____    ____         ___ ____   ____ _     _
# |    |  ____>   ____>  |    |        | <____  \   /
# |____| |    \   ____>  | ___|    ____| <____   \_/	ORBISDEV Open Source Project.
#------------------------------------------------------------------------------------
# Copyright 2010-2020, orbisdev - http://orbisdev.github.io
# Licenced under MIT License
# Review README & LICENSE files for further details.
*/

#ifndef _ORBIS_LIBSCEUSERSERVICE_H_
#define _ORBIS_LIBSCEUSERSERVICE_H_
#pragma once

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef int SceUserServiceUserId;

int sceUserServiceInitialize(int *params);
int sceUserServiceTerminate();
int sceUserServiceGetInitialUser(SceUserServiceUserId *userId);


#ifdef __cplusplus
}
#endif

#endif
