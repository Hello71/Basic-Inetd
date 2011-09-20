#include "include/help.h"
void help() {
		puts("Usage: identd [-v] [{-d,-n}] [-i <ip>] [-p <port>] [-f] [-r <remote IP>] [-c]\n"
				"Debug:\n"
				"  -v, --verbose			Verbose\n"
				"  -d, --daemon			Daemonize\n"
				"  -n, --no-daemon		Don't daemonize (negates earlier -d)\n"
				"\n"
				"Bind:\n"
				"  -i, --bind-ip <ip>		IP to bind to (0.0.0.0 = INADDR_ANY)\n"
				"  -p, --bind-port <port>	Port to bind to (default 113)\n"
				"\n"
				"Security:\n"
				"  -u, --recv-ip <ip>		Only accept connections from IP\n"
				"\n"
				"Miscellaneous:\n"
				"  -r, --no-root			Run as non-root on privileged port\n"
				"  -f, --force			Continue running after non-fatal error\n"
				"  --help			Show help"
				);
		exit(EXIT_SUCCESS);
}
