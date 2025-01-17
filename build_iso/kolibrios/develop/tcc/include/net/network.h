#ifndef __NETWORK_H
#define __NETWORK_H

#include <net/socket.h>

#define EAI_ADDRFAMILY 1
#define EAI_AGAIN      2
#define EAI_BADFLAGS   3
#define EAI_FAIL       4
#define EAI_FAMILY     5
#define EAI_MEMORY     6
#define EAI_NONAME     8
#define EAI_SERVICE    9
#define EAI_SOCKTYPE   10
#define EAI_BADHINTS   12
#define EAI_PROTOCOL   13
#define EAI_OVERFLOW   14

// Flags for addrinfo
#define AI_PASSIVE     1
#define AI_CANONNAME   2
#define AI_NUMERICHOST 4
#define AI_NUMERICSERV 8
#define AI_ADDRCONFIG  0x400

#pragma pack(push, 1)
struct ARP_entry{
unsigned int IP;
unsigned char MAC[6];
unsigned short status;
unsigned short TTL;
};
#pragma pack(pop)

#pragma pack(push, 1)  
struct addrinfo {
    int     ai_flags;
    int     ai_family;
    int     ai_socktype;
    int     ai_protocol;
    int     ai_addrlen;
    char   *ai_canonname;
    sockaddr *ai_addr;
    struct addrinfo *ai_next;
};  
#pragma pack(pop)

extern int networklib_init ();
extern int  (*inet_addr __attribute__ ((stdcall)))(const char* hostname);
extern char* (*inet_ntoa __attribute__ ((stdcall)))(int ip_addr);
extern int (*getaddrinfo __attribute__ ((stdcall)))(char* hostname, int servname, struct addrinfo* hints, struct addrinfo** res);
extern void (*freeaddrinfo __attribute__ ((stdcall)))(struct addrinfo* ai);

#endif
