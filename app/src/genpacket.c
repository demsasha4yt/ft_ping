/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genpacket.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:39:23 by bharrold          #+#    #+#             */
/*   Updated: 2020/08/06 21:48:56 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void print_msg_by_byte(uint8_t *packet)
{
	int i;
	int j;

	j = 0;
	while (j < PACKET_SIZE) {
		i = 7;
		uint8_t a = (uint8_t)packet[j];
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

static inline void	fill_ip_header(t_iphdr *ip, t_ping *ping)
{
	ip->ip_verlen = 4;
	ip->ip_tos = 0;
	ip->ip_totallength = IP_HDR_SIZE;
	ip->ip_id = 0;
	ip->ip_offset = 0;
	ip->ip_ttl = 255;
	ip->ip_protocol = IPPROTO_ICMP,
	ip->ip_checksum = 0;
	ip->ip_destaddr = ping->s_addr;
	ip->ip_srcaddr = INADDR_ANY;
}

static inline void fill_icmp_header(t_icmphdr *icmp, t_ping *ping)
{
	t_timeval time;

	icmp->icmp__type = ICMP_ECHO;
	icmp->icmp__code = 0;
	icmp->icmp__id = htons(getpid());
	icmp->icmp__sequence = htons(ping->sequence);
	gettimeofday(&time, 0);
	icmp->icmp__timestamp = time.tv_usec;
	icmp->icmp__cksum = 0;
	icmp->icmp__cksum = in_cksum(ping->packet.msg, PAYLOAD_SIZE + ICMP_HDR_SIZE);
	(void)ping;
}

int		genpacket(t_ping *ping)
{
	ping->sequence += 1;
	memset(&ping->packet, 0, sizeof(ping->packet));
	memset((void*)(ping->packet.msg + sizeof(t_icmphdr) + sizeof(t_iphdr)), 21, PAYLOAD_MEMSET);
	fill_ip_header((t_iphdr*)(ping->packet.msg + sizeof(t_icmphdr)), ping);
	fill_icmp_header((t_icmphdr*)(ping->packet.msg), ping);
	ping->packet.flags = 0;
	ping->packet.sockfd = ping->sockfd,
	ping->packet.len = PACKET_SIZE - IP_HDR_SIZE;
	memset((void*)&ping->packet.to, 0, sizeof(ping->packet.to));
	ping->packet.to.sin_family = AF_INET;
	ping->packet.to.sin_addr.s_addr = ping->s_addr;
	ping->packet.to.sin_port = htons(0);
	// print_msg_by_byte(ping->packet.msg);
	return (0);
}