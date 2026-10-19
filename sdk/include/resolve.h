#ifndef __RESOLVE_H__
#define __RESOLVE_H__
/* Port to ps5-payload-sdk: the f_* indirections map straight to libc/libkernel. */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#define f_memset  memset
#define f_memcpy  memcpy
#define f_sprintf sprintf
#define f_free    free
#define f_malloc  malloc
#define f_strcmp  strcmp
#define f_strerror strerror
#define f_ioctl   ioctl
#define f_open    open
#define f_close   close
#define f_read    read
#define f_write   write
#define f_lseek   lseek

static inline void* f_memalign(size_t align, size_t size) {
  void* p = 0;
  if(posix_memalign(&p, align, size)) return 0;
  return p;
}
#endif
