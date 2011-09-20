#include <unistd.h>
#include <netinet/ip.h>
#include "include/printv.h"
#include "include/help.h"
#include "include/getopts.h"

int debug = 1;

int verboseflag = 0;

struct args getopts(int argc, char* argv[]);
void help();
int identd(int sock);

int main(int argc, char* argv[]) {
		struct args options;
		int sock;
		struct sockaddr_in bindaddr;
		if (debug) {
				verboseflag = 1;
		}

		if (argc > 1 && (strcmp(argv[1], "--help") == 0 || strcmp(argv[1], "-?") == 0 || strcmp(argv[1], "-h") == 0)) {
				printv("Showing help text");
				help();
		}

		options = getopts(argc, argv);

		if (debug) options.daemonize = 0;

		if (options.verbose) {
				verboseflag = 1;
		}

		if (options.daemonize) {
				int f;
				f = fork();
				if (f != -1) {
						exit(EXIT_SUCCESS);
				}
		}

		sock = socket(PF_INET, SOCK_STREAM, 0);
		if (sock == -1) {
				perror("socket()");
				exit(errno);
		}

		bindaddr = options.bindaddr;
		if (bind(sock, (struct sockaddr*) &bindaddr, sizeof(struct sockaddr_in)) == -1) {
				perror("bind()");
				exit(errno);
		}

		listen(sock, 10);
		return identd(sock);
}

int identd(int sock) {
		while (1) {
				struct sockaddr_in remoteaddr;
				int remotesock;

				unsigned int remoteaddrlen = sizeof(struct sockaddr_in);
				printv("accept()");
				remotesock = accept(sock, (struct sockaddr *) &remoteaddr, &remoteaddrlen);
				if (remotesock == -1) {
						perror("accept()");
						exit(errno);
				} else {
						int pid = fork();
						if (pid != 0) {
								continue;
						}
						vprintv("Received connection from %s\n", inet_ntoa(remoteaddr.sin_addr));
						printv("Sending test string on socket");
						send(remotesock, "Test", 4, 0);
						printv("Closing remote socket");
						close(remotesock);
				}
		}

		return 0;
}
