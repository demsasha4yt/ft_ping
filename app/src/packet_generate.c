/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   packet_generate.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 21:00:10 by bharrold          #+#    #+#             */
/*   Updated: 2020/08/01 21:12:38 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

void print_header_by_byte(t_ping *ping)
{
	int i;
	int j;

	j = 0;
	while (j < PACKET_SIZE) {
		i = 7;
		uint8_t a = (uint8_t) ping->packet[j];
		printf("%d:\t", j);
		while (i >= 0)
		{
			printf("%u", a >> i & 1);
			i--;
		}
		printf("\t|\t%#x\t%d", a, a);
		printf("\n");
		j++;
	}
}

static inline void		fill_ip_header(t_ping *ping)
{
	t_ip_hdr *ip;

	ip = (t_ip_hdr*)ping->packet;
	ip->ip_verlen = 4;
	ip->ip_tos = 0;
	ip->ip_totallength = PACKET_SIZE;
	ip->ip_id = 0;
	ip->ip_offset = 0;
	ip->ip_ttl = ping->ttl;
	ip->ip_protocol = IPPROTO_ICMP;
	ip->ip_checksum = 0;
	ip->ip_destaddr = ping->ping_addr.sin_addr.s_addr;
	ip->ip_srcaddr = INADDR_ANY;
}

u_long get_timestamp()
{
	struct timeval time;
	gettimeofday(&time, 0);
	return (time.tv_usec);
}

static inline void		fill_icmp_header(t_ping *ping)
{
	t_icmp_hdr *icmp = (t_icmp_hdr*)(ping->packet + sizeof(t_ip_hdr));

	icmp->icmp_type = 8;
	icmp->icmp_code = 0;
	icmp->icmp_id = htons(0);
	icmp->icmp_sequence = htons(ping->sequence);
	icmp->icmp_checksum = in_cksum(ping->packet + sizeof(t_ip_hdr), sizeof(t_icmp_hdr));
	icmp->icmp_timestamp = get_timestamp();
}

int						gen_packet(t_ping *ping)
{
	memset(ping->packet, 0, PACKET_SIZE);
	fill_ip_header(ping);
	fill_icmp_header(ping);
	memset((void*)(ping->packet + sizeof(t_icmp_hdr) + sizeof(t_ip_hdr)), 21, ICMP_PAYLOAD_SZ - 8);
	return (0);
}