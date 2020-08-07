/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   genpacket.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 16:39:23 by bharrold          #+#    #+#             */
/*   Updated: 2020/08/07 20:45:10 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void print_msg_by_byte(uint8_t *packet, int size)
{
	int i;
	int j;

	j = 0;
	while (j < size) {
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

static inline void fill_icmp_header(t_icmphdr *icmp, t_ping *ping)
{
	icmp->icmp__type = ICMP_ECHO;
	icmp->icmp__code = 0;
	icmp->icmp__id = htons(getpid());
	icmp->icmp__sequence = htons(ping->sequence);
	icmp->icmp__timestamp = ft_gettime();
	icmp->icmp__cksum = 0;
	icmp->icmp__cksum = in_cksum(ping->packet.msg, PAYLOAD_SIZE + ICMP_HDR_SIZE);
	(void)ping;
}

int		genpacket(t_ping *ping)
{
	ping->sequence += 1;
	memset(&ping->packet, 0, sizeof(ping->packet));
	memset((void*)(ping->packet.msg + sizeof(t_icmphdr)), 21, PAYLOAD_MEMSET);
	fill_icmp_header((t_icmphdr*)(ping->packet.msg), ping);
	ping->packet.flags = 0;
	ping->packet.sockfd = ping->sockfd,
	ping->packet.len = ICMP_PACKET_SIZE;
	memset((void*)&ping->packet.to, 0, sizeof(ping->packet.to));
	ping->packet.to.sin_family = AF_INET;
	ping->packet.to.sin_addr.s_addr = ping->s_addr;
	ping->packet.to.sin_port = htons(0);
	return (0);
}