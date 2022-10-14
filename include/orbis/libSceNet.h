/*
#  ____   ____    ____         ___ ____   ____ _     _
# |    |  ____>   ____>  |    |        | <____  \   /
# |____| |    \   ____>  | ___|    ____| <____   \_/	ORBISDEV Open Source Project.
#------------------------------------------------------------------------------------
# Copyright 2010-2020, orbisdev - http://orbisdev.github.io
# Licenced under MIT License
# Review README & LICENSE files for further details.
*/

#ifndef _ORBIS_LIBSCENET_H_
#define _ORBIS_LIBSCENET_H_

#ifdef __cplusplus
extern "C" {
#endif


#pragma once

#include <stdint.h>
#include <netinet/in.h>



/* useless C / POSIX wrappers */
char sceNetInetNtop(int af, const void *src, char *dst, int size);
int sceNetAccept(int, struct sockaddr *, unsigned int *);
int sceNetBind(int, struct sockaddr *, int);
int sceNetConnect(int, struct sockaddr *, int);
int sceNetGetsockname(int, struct sockaddr *, unsigned int *);
int sceNetGetsockopt(int s, int level, int optname, void * optval, socklen_t * optlen);
int sceNetInetPton(int af, const char *src, void *dst);
int sceNetListen(int, int);
int sceNetRecv(int, void *, size_t, int);
int sceNetSend(int, const void *, size_t, int);
int sceNetSetsockopt(int s, int level, int optname, const void *optval, socklen_t optlen);
int sceNetSocket(const char *, int, int, int);
int sceNetSocketAbort(int , int );
int sceNetSocketClose(int);
uint16_t sceNetHtons(uint16_t host16);
uint16_t sceNetNtohs(uint16_t net16);
uint32_t sceNetHtonl(uint32_t host32);
uint32_t sceNetNtohl(uint32_t net32);
uint64_t sceNetHtonll(uint64_t host64);
uint64_t sceNetNtohll(uint64_t net64);

#define SCE_NET_CTL_SSID_LEN		(32 + 1)
#define SCE_NET_CTL_HOSTNAME_LEN	(255 + 1)
#define SCE_NET_CTL_AUTH_NAME_LEN	(127 + 1)
#define SCE_NET_CTL_IPV4_ADDR_STR_LEN	(16)

#define SCE_NET_ETHER_ADDR_LEN 6

typedef struct SceNetEtherAddr {
	uint8_t data[SCE_NET_ETHER_ADDR_LEN];
} SceNetEtherAddr;

typedef union SceNetCtlInfo {
	uint32_t device;
	SceNetEtherAddr ether_addr;
	uint32_t mtu;
	uint32_t link;
	SceNetEtherAddr bssid;
	char ssid[SCE_NET_CTL_SSID_LEN];
	uint32_t wifi_security;
	uint8_t rssi_dbm;
	uint8_t rssi_percentage;
	uint8_t channel;
	uint32_t ip_config;
	char dhcp_hostname[SCE_NET_CTL_HOSTNAME_LEN];
	char pppoe_auth_name[SCE_NET_CTL_AUTH_NAME_LEN];
	char ip_address[SCE_NET_CTL_IPV4_ADDR_STR_LEN];
	char netmask[SCE_NET_CTL_IPV4_ADDR_STR_LEN];
	char default_route[SCE_NET_CTL_IPV4_ADDR_STR_LEN];
	char primary_dns[SCE_NET_CTL_IPV4_ADDR_STR_LEN];
	char secondary_dns[SCE_NET_CTL_IPV4_ADDR_STR_LEN];
	uint32_t http_proxy_config;
	char http_proxy_server[SCE_NET_CTL_HOSTNAME_LEN];
	uint16_t http_proxy_port;
} SceNetCtlInfo;

#ifdef __cplusplus
}
#endif

#endif
