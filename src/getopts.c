#include "include/getopts.h"

struct args getopts(int argc, char* argv[]) {
		int c;
		char* ip;
		struct args retval;
		printv("Parsing arguments");
		memset(&retval, 0, sizeof(struct args));
		memset(&(retval.bindaddr), 0, sizeof(struct sockaddr_in));
				retval.daemonize = 1;
				retval.noroot = 0;
				retval.bindaddr.sin_port = 113;
				retval.bindaddr.sin_family = AF_INET;
		printv("Initialized retval");
		if (argc == 1) {
				printv("getopt() returning early; argc < 2");
				retval.bindaddr.sin_addr.s_addr = INADDR_ANY;
				return retval;
		}
		ip = "0.0.0.0";
		while ((c = getopt (argc, argv, "vdni:p:fr:c")) != -1) {
				switch (c) {
						case 'v':
								printv("Enabling verbose output");
								retval.verbose = 1;
								break;
						case 'd':
								printv("Daemonizing");
								retval.daemonize = 1;
								break;
						case 'n':
								printv("Not daemonizing");
								retval.daemonize = 0;
								break;
						case 'i':
								vprintv("Setting listening IP to %s\n", optarg);
								ip = optarg;
								break;
						case 'p':
								errno = 0;
								long int tmpport = strtol(optarg, (char**)NULL, 10);
								if (errno || tmpport > 65535 || tmpport < 1) {
										printf("Port cannot be over 65535 or under 1.");
										exit(EXIT_FAILURE);
								} else {
										vprintv("Setting listening port to %d\n", (int)tmpport);
										retval.bindaddr.sin_port = (int)tmpport;
								}
								break;
						case 'f':
								retval.noroot = 1;
						case 'r':
								
						case '?':
								if (c == 'i' || c == 'p') {
										printf("Option -%c requires an argument.\n", optopt);
								} else {
										printf("Unknown option: %c\n", optopt);
								}
								exit(EXIT_FAILURE);
				}
		}
		if (strcmp(ip, "0.0.0.0") == 0) {
				retval.bindaddr.sin_addr.s_addr = INADDR_ANY;
		} else {
				if (inet_aton(ip, &retval.bindaddr.sin_addr) == 0) {
						printf("Invalid bind IP address\n");
						exit(EXIT_FAILURE);
				}
		}
		return retval;
		
}
