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

# define IP_HEADER_SZ  20
# define ICMP_HEADER_SZ 8
# define ICMP_PAYLOAD_SZ 56
# define DEFAULT_TTL 61
# define PACKET_SIZE (IP_HEADER_SZ + ICMP_HEADER_SZ + ICMP_PAYLOAD_SZ)


typedef struct      s_icmp_hdr
{
    unsigned char   icmp_type;
    unsigned char   icmp_code;
    unsigned short  icmp_checksum;
    unsigned short  icmp_id;
    unsigned short  icmp_sequence;
    unsigned long   icmp_timestamp;
}                   t_icmp_hdr;

typedef struct      s_ip_hdr
{
    unsigned char   ip_verlen;        // 4-bit IPv4 version 4-bit header length (in 32-bit words)
    unsigned char   ip_tos;           // IP type of service
    unsigned short  ip_totallength;   // Total length
    unsigned short  ip_id;            // Unique identifier
    unsigned short  ip_offset;        // Fragment offset field
    unsigned char   ip_ttl;           // Time to live
    unsigned char   ip_protocol;      // Protocol(TCP,UDP etc)
    unsigned short  ip_checksum;      // IP checksum
    unsigned int    ip_srcaddr;       // Source address
    unsigned int    ip_destaddr;      // Source address
}                   t_ip_hdr;

typedef struct  s_ping
{
    int v_mode;
    uint32_t            ttl;
    uint32_t            sequence;
    char                *dest_addr;
    struct sockaddr_in  ping_addr;
    t_icmp_hdr          icmp_hdr;
    t_ip_hdr            ip_hdr;
    int                 payload;
    char                packet[PACKET_SIZE];
}            t_ping;

int         gen_packet(t_ping *ping);
void        terminate();
#endif