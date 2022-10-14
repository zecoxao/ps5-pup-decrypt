#ifndef __DEBUG_H__
#define __DEBUG_H__


#define printfsocket(format, ...)\
do {\
  char __printfsocket_buffer[512];\
  int __printfsocket_size = f_sprintf(__printfsocket_buffer, format, ##__VA_ARGS__);\
  f_sceNetSend(sock, __printfsocket_buffer, __printfsocket_size, 0);\
} while(0)


#include "time.h"

void notify(char* message);
unsigned char GetElapsed(unsigned long ResetInterval);

extern int sock;
extern time_t prevtime;

#define SSIZET_FMT "%zd"

#endif
