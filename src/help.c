#include "include/help.h"
void help() {
		printf("Usage: identd [-d] [{-k,-n}] [-i <ip>] [-p <port>] [-f] [-r <remote IP>] [-c]\n"
				"Debug:\n"
				"  -v		Verbose\n"
				"  -d		Daemonize\n"
				"  -n		Don't daemonize (negates earlier -d)\n"
				"\n"
				"Bind:\n"
				"  -i <ip>	IP to bind to (0.0.0.0 = INADDR_ANY)\n"
				"  -p <port>	Port to bind to (default 113)\n"
				"\n"
				"Security:\n"
				"  -r <ip>	Only accept connections from IP\n"
				"\n"
				"Miscellaneous:\n"
				"  -f		Run as non-root on privileged port\n"
				"  -c		Continue running after non-fatal error\n"
				);
		exit(EXIT_SUCCESS);
}
