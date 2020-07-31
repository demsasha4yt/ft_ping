/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   headers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 21:00:10 by bharrold          #+#    #+#             */
/*   Updated: 2020/07/31 23:14:24 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"


static inline void		fill_ip_header(t_ping *ping)
{
	t_ip_hdr *ip;

	ip = (t_ip_hdr*)ping->packet;
	ip->ip_verlen = (4 << 4) | (sizeof(t_ip_hdr) / sizeof(u_long));
	ip->ip_tos = 0;
	ip->ip_totallength = PACKET_SIZE;
	ip->ip_id = 0;
	ip->ip_offset = 0;
	ip->ip_ttl = ping->ttl;
	ip->ip_protocol = IPPROTO_UDP;
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
	icmp->icmp_id = 0;
	icmp->icmp_sequence = htons(ping->sequence);
	icmp->icmp_checksum = 0; // CHECKSUM???? [TODO]
	icmp->icmp_timestamp = get_timestamp();
}

int						gen_packet(t_ping *ping)
{
	fill_ip_header(ping);
	fill_icmp_header(ping);
	memset((void*)(ping->packet + sizeof(t_icmp_hdr) + sizeof(t_ip_hdr)), 21, ICMP_PAYLOAD_SZ);
	return (0);
}