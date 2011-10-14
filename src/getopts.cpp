#include "include/getopts.h"

struct args getopts(int argc, char* argv[]) {
    int c;
    struct args retval;
    memset(&retval, 0, sizeof(struct args));
        retval.daemonize = 1;
        retval.noroot = 0;
        retval.continu = 0;
    memset(&(retval.bindaddr), 0, sizeof(struct sockaddr_in));
        retval.bindaddr.sin_port = htons(113);
        retval.bindaddr.sin_family = AF_INET;
        retval.bindaddr.sin_addr.s_addr = INADDR_ANY;
    memset(&(retval.recvaddr), 0, sizeof(struct in_addr));
        retval.recvaddr.s_addr = INADDR_ANY;
    if (argc == 1) {
        retval.bindaddr.sin_addr.s_addr = INADDR_ANY;
        return retval;
    }
    while (1) {
        struct option long_options[] = {
            {"daemon", no_argument, &(retval.daemonize), 1},
            {"no-daemon", no_argument, &(retval.daemonize), 0},
            {"no-root", no_argument, &(retval.noroot), 1},
            {"continue", no_argument, &(retval.continu), 1},
            {"help", no_argument, 0, 'h'},
            {"bind-ip", required_argument, 0, 'i'},
            {"bind-port", required_argument, 0, 'p'},
            {"remote-ip", required_argument, 0, 'r'},
            {0, 0, 0, 0}
        };
        int option_index = 0;

        c = getopt_long(argc, argv, "vdnuci:p:r:", long_options, &option_index);

        if (c == -1) break;

        switch (c) {
            case 0:
                if (long_options[option_index].flag != 0) {
                    break;
                }
                break;

            case 'd':
                retval.daemonize = 1;
                break;

            case 'n':
                retval.daemonize = 0;
                break;

            case 'u':
                retval.noroot = 1;
                break;

            case 'c':
                retval.continu = 1;
                break;

            case 'h':
                help();
                break;

            case 'i':
                if (strcmp(optarg, "0.0.0.0") == 0) {
                    retval.bindaddr.sin_addr.s_addr = INADDR_ANY;
                } else {
                    if (inet_aton(optarg, &retval.bindaddr.sin_addr) == 0) {
                        puts("Invalid bind IP address\n");
                        exit(EXIT_FAILURE);
                    }
                }
                break;

            case 'p':
                errno = 0;
                long int tmpport;
                tmpport = strtol(optarg, (char**)NULL, 10);
                if (errno || tmpport > 65535 || tmpport < 1) {
                    printf("Port cannot be over 65535 or under 1.");
                    exit(EXIT_FAILURE);
                } else {
                    retval.bindaddr.sin_port = htons((int)tmpport);
                }
                break;

            case 'r':
                if (strcmp(optarg, "0.0.0.0") == 0) {
                    retval.recvaddr.s_addr = INADDR_ANY;
                } else {
                    if (inet_aton(optarg, &retval.recvaddr) == 0) {
                        puts("Invalid receive filter IP");
                        exit(EXIT_FAILURE);
                    }
                }
                break;

            case '?':
                printf("Try `%s --help' for more information.\n", argv[0]);
                exit(EXIT_FAILURE);
                break;
                
            default:
                abort();
        }
        if (optind < argc) {
            retval.string = (char*) malloc(strlen(argv[optind]));
            sprintf(retval.string, "%s", argv[optind]);
        } else {
            printf("You must provide a string to return.\n");
            exit(EXIT_FAILURE);
        }
    }
    return retval;
}
