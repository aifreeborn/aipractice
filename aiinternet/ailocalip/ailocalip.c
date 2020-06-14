#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#define MAXINTERFACES 6

static int get_host_ip(char *ipaddr, int size )
{
    int i;
    int sockfd;
    char *localip;
    struct ifconf ifconfs;
    struct ifreq ifreqs[MAXINTERFACES];

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
        return -1;

    ifconfs.ifc_len = (sizeof(struct ifreq)) * MAXINTERFACES;
    ifconfs.ifc_req = ifreqs;
    if (ioctl(sockfd, SIOCGIFCONF, &ifconfs) < 0) {
        close(sockfd);
        return -1;
    } else {
        for (i = 0; i < (int)(ifconfs.ifc_len / sizeof(struct ifreq)); i++) {
            if (0 == ioctl(sockfd, SIOCGIFFLAGS, &ifconfs.ifc_req[i])) {
                if (ifconfs.ifc_req[i].ifr_flags & IFF_UP) {
                    if (0 != strcmp(ifconfs.ifc_req[i].ifr_name, "lo")) {
                        printf("device[%d]:%s\n", i, ifconfs.ifc_req[i].ifr_name);
                        localip = inet_ntoa(((struct sockaddr_in *)&(ifconfs.ifc_req[i].ifr_addr))->sin_addr);
                        snprintf(ipaddr, size, "%s", localip);
                        printf("IP %s\n", ipaddr);
                        if(0 == strcmp(ifconfs.ifc_req[i].ifr_name, "eth0"))
                            break;
                        if(0 == strcmp(ifconfs.ifc_req[i].ifr_name, "wlan0"))
                            break;

                    }
                }
            }
        }
    }

    close(sockfd);
    return 0;
}

static int sw_upgrade_udp_server(const char *ip, const uint16_t port)
{
    int sockfd;
    char recv_buf[1024] = {0};
    struct sockaddr_in local, sender;
    socklen_t sender_len = sizeof(sender);

    if (!ip)
        return -1;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        return -1;
    bzero(&local, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_addr.s_addr = inet_addr(ip);
    local.sin_port = htons(port);
    if(bind(sockfd, (struct sockaddr *)&local, sizeof(local)) < 0)
        return -1;

    while (1) {
        bzero(recv_buf, sizeof(recv_buf));

        recvfrom(sockfd, recv_buf, sizeof(recv_buf), 0,
                 (struct sockaddr *)&sender, &sender_len);
        printf("Get a cilent:%s: %d : %s\n",
                inet_ntoa(sender.sin_addr), ntohs(sender.sin_port), recv_buf);
        sendto(sockfd, recv_buf, sizeof(recv_buf), 0,
               (struct sockaddr*)&sender, sender_len);
        if (!strncmp(recv_buf, "quit", strlen("quit")))
            break;
    }
    close(sockfd);
    return 0;
}

int main(int argc,char *argv[])
{
    char ipaddr[32] = {0};
    get_host_ip(ipaddr, sizeof(ipaddr));
    sw_upgrade_udp_server(ipaddr, 8888);

    return 0;
}
