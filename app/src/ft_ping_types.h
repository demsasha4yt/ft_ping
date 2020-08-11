/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping_types.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 15:31:27 by bharrold          #+#    #+#             */
/*   Updated: 2020/08/11 18:17:32 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_TYPES_H
# define FT_PING_TYPES_H

# include <stdlib.h>

typedef struct addrinfo		t_addrinfo;
typedef struct sockaddr_in	t_sockaddr_in;
typedef struct in_addr		t_in_addr;
typedef struct sockaddr		t_sockaddr;
typedef struct timeval		t_timeval;
typedef struct timezone		t_timezone;
typedef struct msghdr		t_msghdr;
typedef struct iovec		t_iovec;

/*
** [Packet format]:
** IP Header - 20 bytes
** ICMP Header - 8 bytes + timestamp 8 bytes
** PAYLOAD - 56 bytes (It includes 8 byte timestamp)
*/

/*
** [Packet constants]:
*/

# define PACKET_SIZE 84
# define ICMP_PACKET_SIZE 64
# define IP_HDR_SIZE 20
# define ICMP_HDR_SIZE 8
# define PAYLOAD_SIZE 56
# define TIMESTAMP_SIZE sizeof(suseconds_t)
# define PAYLOAD_MEMSET (PAYLOAD_SIZE - TIMESTAMP_SIZE)

/*
** [ICMP HEADER FORMAT]
** Version/ihl
** Type of service
** Length of packet
** Packet ID
** Packet offset
** Checksum
** Sequence
** + TIMESTAMP [NEED TO EASY GENERATE BY CASTING uint8_t* to t_icmphdr*]
*/

typedef struct				s_icmphdr
{
	uint8_t					icmp__type;
	uint8_t					icmp__code;
	uint16_t				icmp__cksum;
	uint16_t				icmp__id;
	uint16_t				icmp__sequence;
	suseconds_t				icmp__timestamp;
}							t_icmphdr;

/*
** [IP HEADER FORMAT]:
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

typedef struct				s_iphdr {
	uint8_t					ip_verlen;
	uint8_t					ip_tos;
	uint16_t				ip_totallength;
	uint16_t				ip_id;
	uint16_t				ip_offset;
	uint8_t					ip_ttl;
	uint8_t					ip_protocol;
	uint16_t				ip_checksum;
	uint32_t				ip_srcaddr;
	uint32_t				ip_destaddr;
}							t_iphdr;


/*
** [t_ping_pckt format]:
** Opened socket fd
** Flags
** Destination
** Data length
** Data
*/
typedef struct				s_ping_pckt
{
	int						sockfd;
	int						flags;
	t_sockaddr_in		to;
	size_t					len;
	uint8_t					msg[PACKET_SIZE];
}							t_ping_pckt;


typedef struct				s_ping
{
	uint8_t					s_vmode;
	uint32_t				s_ttl;
	uint32_t				s_delay;
	uint32_t				sequence;
	char					*addr;
	t_ping_pckt				packet;
	uint32_t				s_addr;
	t_ping_pckt				t_ping_pckt;
	int						sockfd;
	int						transd_pckg;
	int 					rcvd_pckgs;
	int						errors;
	suseconds_t				start_time;
}							t_ping;

#endif

/*
** FT_PING_TYPES
*/