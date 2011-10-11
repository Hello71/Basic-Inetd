#include "include/help.h"
void help() {
    puts("Usage: identd [OPTION] [USER] STRING\n"
        "STRING: A string to return in the socket. Must be a single argument.\n"
        " Precede with -- if the string begins with a hyphen.\n"
        "Debug:\n"
        "  -v, --verbose             Verbose\n"
        "  -d, --daemon              Daemonize\n"
        "  -n, --no-daemon           Don't daemonize (negates earlier -d)\n"
        "\n"
        "Bind:\n"
        "  -i, --bind-ip <ip>        IP to bind to (0.0.0.0 = all)\n"
        "  -p, --bind-port <port>    Port to bind to (default 113)\n"
        "\n"
        "Security:\n"
        "  -r, --remote-ip <ip>      Only accept connections from IP (0.0.0.0 = all)\n"
        "\n"
        "Miscellaneous:\n"
        "  -u, --no-root             Run as non-root on privileged port\n"
        "  -c, --continue            Continue running after non-fatal error\n"
        "  --help                    Show help"
        );
    exit(EXIT_SUCCESS);
}
