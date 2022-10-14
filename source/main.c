#include "defines.h"
#include "debug.h"
#include "resolve.h"

// https://github.com/OSM-Made/PS4-Notify
void printf_notification(const char* fmt, ...) {
    SceNotificationRequest noti_buffer;

    va_list args;
    va_start(args, fmt);
    f_vsprintf(noti_buffer.message, fmt, args);
    va_end(args);

    noti_buffer.type = 0;
    noti_buffer.unk3 = 0;
    noti_buffer.use_icon_image_uri = 1;
    noti_buffer.target_id = -1;
    f_strcpy(noti_buffer.uri, "cxml://psnotification/tex_icon_system");

    f_sceKernelSendNotificationRequest(0, (SceNotificationRequest * ) & noti_buffer, sizeof(noti_buffer), 0);
}


void decrypt_pups();

int sock;

int payload_main(struct payload_args *args) {
    dlsym_t* dlsym = args->dlsym;
	
	
	
	int libKernel = 0x2001;

	dlsym(libKernel, "sceKernelLoadStartModule", &f_sceKernelLoadStartModule);
	dlsym(libKernel, "sceKernelDebugOutText", &f_sceKernelDebugOutText);
	dlsym(libKernel, "sceKernelSendNotificationRequest", &f_sceKernelSendNotificationRequest);
	dlsym(libKernel, "sceKernelUsleep", &f_sceKernelUsleep);
	dlsym(libKernel, "scePthreadMutexLock", &f_scePthreadMutexLock);
	dlsym(libKernel, "scePthreadMutexUnlock", &f_scePthreadMutexUnlock);
	dlsym(libKernel, "scePthreadExit", &f_scePthreadExit);
	dlsym(libKernel, "scePthreadMutexInit", &f_scePthreadMutexInit);
	dlsym(libKernel, "scePthreadCreate", &f_scePthreadCreate);
	dlsym(libKernel, "scePthreadMutexDestroy", &f_scePthreadMutexDestroy);
	dlsym(libKernel, "scePthreadJoin", &f_scePthreadJoin);
	dlsym(libKernel, "socket", &f_socket);
	dlsym(libKernel, "bind", &f_bind);
	dlsym(libKernel, "listen", &f_listen);
	dlsym(libKernel, "accept", &f_accept);
	dlsym(libKernel, "ioctl", &f_ioctl);
	dlsym(libKernel, "open", &f_open);
	dlsym(libKernel, "read", &f_read);
	dlsym(libKernel, "write", &f_write);
	dlsym(libKernel, "close", &f_close);
	dlsym(libKernel, "stat", &f_stat);
	dlsym(libKernel, "fstat", &f_fstat);
	dlsym(libKernel, "rename", &f_rename);
	dlsym(libKernel, "rmdir", &f_rmdir);
	dlsym(libKernel, "mkdir", &f_mkdir);
	dlsym(libKernel, "getdents", &f_getdents);
	dlsym(libKernel, "unlink", &f_unlink);
	dlsym(libKernel, "readlink", &f_readlink);
	dlsym(libKernel, "lseek", &f_lseek);
	dlsym(libKernel, "puts", &f_puts);
	dlsym(libKernel, "mmap", &f_mmap);
	dlsym(libKernel, "munmap", &f_munmap);
	dlsym(libKernel, "__error", &f___error);
	

	int libNet = f_sceKernelLoadStartModule("libSceNet.sprx", 0, 0, 0, 0, 0);
	dlsym(libNet, "sceNetSocket", &f_sceNetSocket);
	dlsym(libNet, "sceNetConnect", &f_sceNetConnect);
	dlsym(libNet, "sceNetHtons", &f_sceNetHtons);
	dlsym(libNet, "sceNetAccept", &f_sceNetAccept);
	dlsym(libNet, "sceNetSend", &f_sceNetSend);
	dlsym(libNet, "sceNetInetNtop", &f_sceNetInetNtop);
	dlsym(libNet, "sceNetSocketAbort", &f_sceNetSocketAbort);
	dlsym(libNet, "sceNetBind", &f_sceNetBind);
	dlsym(libNet, "sceNetListen", &f_sceNetListen);
	dlsym(libNet, "sceNetSocketClose", &f_sceNetSocketClose);
	dlsym(libNet, "sceNetHtonl", &f_sceNetHtonl);
	dlsym(libNet, "sceNetInetPton", &f_sceNetInetPton);
	dlsym(libNet, "sceNetGetsockname", &f_sceNetGetsockname);
	dlsym(libNet, "sceNetRecv", &f_sceNetRecv);
	dlsym(libNet, "sceNetErrnoLoc", &f_sceNetErrnoLoc);
	dlsym(libNet, "sceNetSetsockopt", &f_sceNetSetsockopt);

	int libC = f_sceKernelLoadStartModule("libSceLibcInternal.sprx", 0, 0, 0, 0, 0);
	dlsym(libC, "vsprintf", &f_vsprintf);
	dlsym(libC, "memset", &f_memset);
	dlsym(libC, "memalign", &f_memalign);
	dlsym(libC, "sprintf", &f_sprintf);
	dlsym(libC, "snprintf", &f_snprintf);
	dlsym(libC, "snprintf_s", &f_snprintf_s);
	dlsym(libC, "strcat", &f_strcat);
	dlsym(libC, "free", &f_free);
	dlsym(libC, "memcpy", &f_memcpy);
	dlsym(libC, "strcpy", &f_strcpy);
	dlsym(libC, "strncpy", &f_strncpy);
	dlsym(libC, "sscanf", &f_sscanf);
	dlsym(libC, "malloc", &f_malloc);
	dlsym(libC, "calloc", &f_calloc);
	dlsym(libC, "strlen", &f_strlen);
	dlsym(libC, "strcmp", &f_strcmp);
	dlsym(libC, "strchr", &f_strchr);
	dlsym(libC, "strrchr", &f_strrchr);
	dlsym(libC, "gmtime_s", &f_gmtime_s);
	dlsym(libC, "time", &f_time);
	dlsym(libC, "localtime", &f_localtime);
	dlsym(libC, "strerror", &f_strerror);
	
	int libNetCtl = f_sceKernelLoadStartModule("libSceNetCtl.sprx", 0, 0, 0, 0, 0);
	dlsym(libNetCtl, "sceNetCtlInit", &f_sceNetCtlInit);
	dlsym(libNetCtl, "sceNetCtlTerm", &f_sceNetCtlTerm);
	dlsym(libNetCtl, "sceNetCtlGetInfo", &f_sceNetCtlGetInfo);

	printf_notification("PUP Decrypt started!");
  
	struct sockaddr_in server;

	server.sin_len = sizeof(server);
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = DEBUG_ADDR;                //in defines.h
	server.sin_port = f_sceNetHtons(DEBUG_PORT);          //in defines.h
	f_memset(server.sin_zero, 0, sizeof(server.sin_zero));
	sock = f_sceNetSocket("debug", AF_INET, SOCK_STREAM, 0);
	f_sceNetConnect(sock, (struct sockaddr *)&server, sizeof(server));

	int flag = 1;
	f_sceNetSetsockopt(sock, IPPROTO_TCP, TCP_NODELAY, (char *)&flag, sizeof(int));

	//Output paths must already exist!
	decrypt_pups("/mnt/usb0/safe.PS5UPDATE.PUP", "/mnt/usb0/%s.dec");

	printf_notification("Complete!");
  
	return 0;
}
