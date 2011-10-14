#ifndef GETOPTS_GUARD
#define GETOPTS_GUARD

#include <string.h>
#include <netinet/ip.h>
#include <getopt.h>
#include "help.h"
#include <stdlib.h>
#include <errno.h>
#include <arpa/inet.h>
#include <stdio.h>

struct args {
    int daemonize;
    struct sockaddr_in bindaddr;
    struct in_addr recvaddr;
    int noroot;
    int continu;
    char* string;
};

struct args getopts(int argc, char* argv[]);

#endif
