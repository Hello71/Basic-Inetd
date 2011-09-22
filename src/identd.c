#include <unistd.h>
#include <netinet/ip.h>
#include "include/printv.h"
#include "include/getopts.h"

int debug = 1;

int verboseflag;

int main(int argc, char* argv[]) {
	struct args options;
	int sock;
	struct sockaddr_in bindaddr;

	verboseflag = !debug;

	options = getopts(argc, argv);

	if (debug) options.daemonize = 0;

	verboseflag = options.verbose || debug;
	options.continu = options.continu || debug;

	if (!options.noroot && ntohs(options.bindaddr.sin_port) < 1024 && geteuid() != 0) {
		puts("Binding as non-root to port <1024\n"
			"You may need to use `sudo' or similar.\n"
			"To override this warning, use -u.");
		exit(EXIT_FAILURE);
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
		if (errno == EACCES && geteuid() != 0) {
			putsv("Are you trying to bind to a port under 1024?\n"
				"You may need to use `sudo' or similar.");
		}
		exit(errno);
	}

	listen(sock, 10);

	while (1) {
		struct sockaddr_in remoteaddr;
		int remotesock;

		unsigned int remoteaddrlen = sizeof(struct sockaddr_in);
		putsv("accept()");
		remotesock = accept(sock, (struct sockaddr *) &remoteaddr, &remoteaddrlen);
		if (remotesock == -1) {
			perror("accept()");
			exit(errno);
		} else {
			if (memcmp(&remoteaddr.sin_addr, &(options.recvaddr), sizeof(struct in_addr)) != 0) {
				printf("Unauthorized connection from %s\n", inet_ntoa(remoteaddr.sin_addr));
				if (!options.continu) {
					exit(EXIT_SUCCESS);
				}
			}
			int pid = fork();
			if (pid != 0) {
				continue;
			}
			printv("Received connection from %s\n", inet_ntoa(remoteaddr.sin_addr));
			putsv("Reading until \\n is received");
			char* buf[1];
			while (1) {
				read(remotesock, &buf, 1);
				if (strcmp((const char*) &buf, "\n") == 0) {
					break;
				}
			}
			putsv("Sending test message");
			send(remotesock, "Test", 4, 0);
			putsv("Sending EOF and closing remote socket");
			close(remotesock);
		}
	}

	return 0;
}
