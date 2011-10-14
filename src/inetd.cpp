#include <unistd.h>
#include <netinet/ip.h>
#include "include/getopts.h"
#include "include/inetd.h"

int main(int argc, char* argv[]) {
    struct args options;
    int sock;
    struct sockaddr_in bindaddr;

    options = getopts(argc, argv);

    options.continu = options.continu;

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
        abort();
    }

    int one = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &(one), sizeof(int)) == -1) {
        abort();
    }

    bindaddr = options.bindaddr;
    if (bind(sock, (struct sockaddr*) &bindaddr, sizeof(struct sockaddr_in)) == -1) {
        perror("bind()");
        if (errno == EACCES && geteuid() != 0) {
            puts("Are you trying to bind to a port under 1024?\n"
                "You may need to use `sudo' or similar.");
            exit(EXIT_FAILURE);
        }
        abort();
    }

    listen(sock, 10);

    while (1) {
        struct sockaddr_in remoteaddr;
        int remotesock;
        unsigned int remoteaddrlen = sizeof (struct sockaddr_in);

        unsigned int s_addr = options.recvaddr.s_addr;
        remotesock = accept(sock, (struct sockaddr *) &remoteaddr, &remoteaddrlen);
        if (remotesock == -1) {
            perror("accept()");
            abort();
        } else {
            if (remoteaddr.sin_addr.s_addr != s_addr && s_addr != INADDR_ANY) {
                printf("Unauthorized connection from %s\n", inet_ntoa(remoteaddr.sin_addr));
                if (!options.continu) {
                    exit(EXIT_FAILURE);
                }
            }
            int pid = fork();
            if (pid != 0) {
                continue;
            }
            printf("Received connection from %s\n", inet_ntoa(remoteaddr.sin_addr));
            char* buf[1];
            while (1) {
                if (read(remotesock, &buf, 1) == -1) {
                    printf("error reading from socket connected to: %s:", inet_ntoa(remoteaddr.sin_addr));
                    perror("");
                    if (!options.continu) {
                        abort();
                    }
                }
                if (strcmp((const char*) &buf, "\n") == 0) {
                    break;
                }
            }
            puts("Sending string");
            send(remotesock, options.string, strlen(options.string), 0);
            puts("Closing remote socket");
            if (shutdown(remotesock, SHUT_RDWR) == -1) {
                perror("shutdown()");
                abort();
            }
            if (close(remotesock) == -1) {
                perror("close()");
                abort();
            }
        }
    }

    return 0;
}
