#ifndef GETOPTS_GUARD
#define GETOPTS_GUARD

#include "printv.h"
#include "help.h"
#include <stdio.h>
#include <getopt.h>
#include <netinet/ip.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <arpa/inet.h>

struct args {
	int verbose;
	int daemonize;
	struct sockaddr_in bindaddr;
	struct in_addr recvaddr;
	int noroot;
	int continu;
};

struct args getopts(int argc, char* argv[]);

#endif
