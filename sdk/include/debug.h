#ifndef __DEBUG_H__
#define __DEBUG_H__
#include <time.h>

void plog(const char* fmt, ...);
void notify(const char* message);

#define printfsocket(...) plog(__VA_ARGS__)
#define SSIZET_FMT "%zd"
#endif
