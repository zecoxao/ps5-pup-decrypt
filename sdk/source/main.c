#include <stdarg.h>
#include <stdbool.h>
#include "resolve.h"
#include "debug.h"
#include "defines.h"
#include <ps5/kernel.h>

int sceNotificationSend(int userId, bool isLogged, const char* payload);

void decrypt_pups(const char* InputPath, const char* OutputPath);

static int logfd1 = -1, logfd2 = -1;

void plog(const char* fmt, ...) {
  char buf[1024];
  va_list ap;
  va_start(ap, fmt);
  int n = vsnprintf(buf, sizeof(buf), fmt, ap);
  va_end(ap);
  if(n < 0) return;
  if(n >= (int)sizeof(buf)) n = sizeof(buf) - 1;
  if(logfd1 >= 0) { write(logfd1, buf, n); fsync(logfd1); }
  if(logfd2 >= 0) { write(logfd2, buf, n); }
  if(n == 0 || buf[n-1] != '\n') {
    if(logfd1 >= 0) write(logfd1, "\n", 1);
    if(logfd2 >= 0) write(logfd2, "\n", 1);
  }
}

void notify(const char* message) {
  char json[2048];
  snprintf(json, sizeof(json),
    "{\"rawData\":{\"viewTemplateType\":\"InteractiveToastTemplateB\","
    "\"channelType\":\"Downloads\",\"useCaseId\":\"IDC\","
    "\"toastOverwriteType\":\"No\",\"isImmediate\":true,\"priority\":100,"
    "\"viewData\":{\"icon\":{\"type\":\"Predefined\",\"parameters\":{\"icon\":\"download\"}},"
    "\"message\":{\"body\":\"%s\"},\"subMessage\":{\"body\":\"ps5 pup decrypt\"}},"
    "\"platformViews\":{\"previewDisabled\":{\"viewData\":{\"icon\":{\"type\":\"Predefined\","
    "\"parameters\":{\"icon\":\"download\"}},\"message\":{\"body\":\"%s\"}}}}},"
    "\"createdDateTime\":\"2026-10-19T12:00:00.000Z\",\"localNotificationId\":\"588193128\"}",
    message, message);
  sceNotificationSend(0xFE, true, json);
}


/* Raise the process credentials until /dev/pup_update0 can be opened. */
static int raise_privileges(void) {
  uint8_t full[16];
  uint8_t origcaps[16];
  pid_t pid = getpid();
  uint64_t orig = kernel_get_ucred_authid(pid);
  static const uint64_t cands[] = {
    0x4800000000010003ull, 0x4801000000000013ull, 0x4800000000000010ull,
    0x4800000000000007ull, 0x4800000000000002ull, 0x4001000000000002ull,
    0x4800000000000001ull, 0x4801000000000014ull
  };
  memset(full, 0xff, sizeof(full));
  plog("orig authid=0x%llx", (unsigned long long)orig);
  if(kernel_get_ucred_caps(pid, origcaps)) plog("get caps failed");
  if(kernel_set_ucred_caps(pid, full)) plog("set caps failed");
  for(unsigned i = 0; i < sizeof(cands)/sizeof(cands[0]); i++) {
    if(kernel_set_ucred_authid(pid, cands[i])) { plog("set authid 0x%llx failed", (unsigned long long)cands[i]); continue; }
    int fd = open("/dev/pup_update0", O_RDWR, 0);
    plog("authid 0x%llx -> open fd=%d errno=%d", (unsigned long long)cands[i], fd, errno);
    if(fd >= 0) { close(fd); return 0; }
  }
  kernel_set_ucred_authid(pid, orig);
  kernel_set_ucred_caps(pid, origcaps);
  return -1;
}
int main(void) {
  logfd1 = open("/mnt/usb0/pupdec.log", O_WRONLY | O_CREAT | O_TRUNC, 0777);
  logfd2 = open("/data/pupdec.log", O_WRONLY | O_CREAT | O_TRUNC, 0777);
  plog("pupdec start, usb log fd=%d data log fd=%d (errno=%d)", logfd1, logfd2, errno);
  notify("PUP Decrypt started!");
  if(raise_privileges()) { plog("no authid could open pup_update0"); notify("PUP Decrypt: no privileges"); return 1; }

  decrypt_pups(INPUTPATH, OUTPUTPATH);

  plog("done");
  notify("Complete! (see pupdec.log on USB)");
  if(logfd1 >= 0) close(logfd1);
  if(logfd2 >= 0) close(logfd2);
  return 0;
}


