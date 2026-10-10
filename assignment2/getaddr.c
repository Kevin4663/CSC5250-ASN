#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/time.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <hostname>\n", argv[0]);
        return 1;
    }

    struct timeval start, end;
    gettimeofday(&start, NULL);

    struct hostent *host = gethostbyname(argv[1]);

    gettimeofday(&end, NULL);

    if (host == NULL) {
        herror("Error resolving host");
        return 1;
    }

    double elapsed_ms = (end.tv_sec - start.tv_sec) * 1000.0 +
                        (end.tv_usec - start.tv_usec) / 1000.0;

    printf("execution time: %.3f milliseconds\n", elapsed_ms);
    printf("Official name: %s\n", host->h_name);

    // Print Aliases
    printf("Aliases: ");
    if (host->h_aliases == NULL || host->h_aliases[0] == NULL) {
        printf("none");
    } else {
        for (int i = 0; host->h_aliases[i] != NULL; i++) {
            printf("%s%s", (i > 0) ? ", " : "", host->h_aliases[i]);
        }
    }
    printf("\n");

    // Print Addresses
    printf("Addresses: ");
    if (host->h_addr_list == NULL || host->h_addr_list[0] == NULL) {
        printf("none");
    } else {
        for (int i = 0; host->h_addr_list[i] != NULL; i++) {
            struct in_addr *addr = (struct in_addr *)host->h_addr_list[i];
            printf("%s%s", (i > 0) ? ", " : "", inet_ntoa(*addr));
        }
    }
    printf("\n");

    return 0;
}
