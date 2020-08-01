/* ************************************************************************** */
/*                                      */
/*                            :::     ::::::::   */
/*   ft_ping.h                      :+:   :+:    :+:   */
/*                          +:+ +:+       +:+    */
/*   By: bharrold <bharrold@student.42.fr>      +#+  +:+       +#+    */
/*                        +#+#+#+#+#+   +#+     */
/*   Created: 2020/07/31 20:17:21 by bharrold        #+#  #+#          */
/*   Updated: 2020/07/31 21:27:53 by bharrold       ###   ########.fr    */
/*                                      */
/* ************************************************************************** */

#ifndef FT_PING_H
#define FT_PING_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in_systm.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netdb.h>
# include <sys/time.h>
# include <signal.h>

# define IP_HEADER_SZ  20
# define ICMP_HEADER_SZ 8
# define ICMP_PAYLOAD_SZ 56
# define DEFAULT_TTL 61
# define DEFAULT_PING_DELAY 4
# define PACKET_SIZE (IP_HEADER_SZ + ICMP_HEADER_SZ + ICMP_PAYLOAD_SZ)


typedef struct      s_icmp_hdr
{
    uint8_t   icmp_type;
    uint8_t   icmp_code;
    uint16_t  icmp_checksum;
    uint16_t  icmp_id;
    uint16_t  icmp_sequence;
    unsigned long   icmp_timestamp;
}                   t_icmp_hdr;

/*
** [IP HEADER FORMAT]
** 4-bit IPv4 version 4-bit header length (in 32-bit words)
** IP type of service
** Total length
** Unique identifier
** Fragment offset field
** Time to live
** Protocol(TCP,UDP etc)
** IP checksum
** Source address
** Dest address
*/
typedef struct      s_ip_hdr
{
    uint8_t   ip_verlen;
    uint8_t   ip_tos;
    uint16_t  ip_totallength;
    uint16_t  ip_id;
    uint16_t  ip_offset;
    uint8_t   ip_ttl;
    uint8_t   ip_protocol;
    uint16_t  ip_checksum;
    uint32_t   ip_srcaddr;
    uint32_t   ip_destaddr;
}                   t_ip_hdr;

typedef struct  s_ping
{
    int v_mode;
    uint32_t            ttl;
    uint32_t            ping_delay;
    uint32_t            sequence;
    char                *dest_addr;
    struct sockaddr_in  ping_addr;
    uint8_t             packet[PACKET_SIZE];
    int             sock;
}            t_ping;
int         check_input(int argc, char **argv);
char*	    parse_input(int argc, char **argv, t_ping *ping);
int         gen_packet(t_ping *ping);
uint16_t	in_cksum(uint8_t *data, size_t length);
void        print_header_by_byte(t_ping *ping);
int         init_socket();
void	    close_socket(int sig);
void	    rcv_echo_response(int sockfd, struct sockaddr_in *addr, uint8_t *packet, int options);
void	    send_echo_request(int sockfd, const struct sockaddr *dest, uint8_t *packet, int options);

#endif