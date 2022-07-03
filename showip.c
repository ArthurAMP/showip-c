/*
    This code was rewritten from the showip.c example on Beej's Guide to Network Programming
    https://beej.us/guide/bgnet/examples/showip.c
*/

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void a_gai(struct addrinfo *x, struct addrinfo **list, char *ip){
    
    int status;
    
    if((status=getaddrinfo(ip, NULL, x, list))!=0){
        
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }
}

int main(int argc, char *argv[]){
    
    struct addrinfo hints, *res, *p;
    char ipstr[INET6_ADDRSTRLEN];
    char *hostname = argv[1];
        
    if(argc!=2){

        fprintf(stderr, "usage: showip hostname");
        return 1;
    }

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    
    a_gai(&hints, &res, hostname);

    printf("IP address for %s\n\n", argv[1]);

    for(p = res; p != NULL; p = p->ai_next){
        
        void *addr; 
        char *ipver;

        if(p->ai_family == AF_INET) {
            
            struct sockaddr_in *ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        }else{
        
            struct sockaddr_in6 *ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }

        inet_ntop(p->ai_family, addr, ipstr, sizeof(ipstr));
        printf("%s: %s\n", ipver, ipstr);
    }
    
    freeaddrinfo(res);

    return 0;
}
