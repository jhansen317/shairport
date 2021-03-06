#ifndef _COMMON_H
#define _COMMON_H

#include <openssl/rsa.h>
#include <stdint.h>
#include <sys/socket.h>
#include "audio.h"
#include "mdns.h"

// struct sockaddr_in6 is bigger than struct sockaddr. derp
#ifdef AF_INET6
    #define SOCKADDR struct sockaddr_storage
    #define SAFAMILY ss_family
#else
    #define SOCKADDR struct sockaddr
    #define SAFAMILY sa_family
#endif


typedef struct {
    char *password;
    char *apname;
    uint8_t hw_addr[6];
    int port;
    char *output_name;
    audio_output *output;
    char *mdns_name;
    mdns_backend *mdns;
    int buffer_start_fill;
    int daemonise;
    int cmd_blocking;
    char *cmd_start, *cmd_stop;
    char *pidfile;
    char *logfile;
    char *errfile;
    char *timefile;
    char *lpfile;
} shairport_cfg;

extern int debuglev;
void strfnow(char *timestring);
void print_log(FILE *fp, char *format, ...);
void die(char *format, ...);
void warn(char *format, ...);
void debug(int level, char *format, ...);

uint8_t *base64_dec(char *input, int *outlen);
char *base64_enc(uint8_t *input, int length);

#define RSA_MODE_AUTH (0)
#define RSA_MODE_KEY  (1)
uint8_t *rsa_apply(uint8_t *input, int inlen, int *outlen, int mode);

extern shairport_cfg config;

void command_start(void);
void command_stop(void);

void shairport_shutdown(int retval);
void shairport_startup_complete(void);

#endif // _COMMON_H
