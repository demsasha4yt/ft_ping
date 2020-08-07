/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 21:36:40 by bharrold          #+#    #+#             */
/*   Updated: 2020/08/07 20:44:17 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static suseconds_t	get_rtt(suseconds_t send_time)
{
	return (ft_gettime() - send_time);
}

static const char	*g_responses[] = {
	[3]			= "Destination Unreachable",
	[4]			= "Source Quench",
	[5]			= "Redirect (change route)",
	[8]			= "Echo Request",
	[11]		= "Time to live exceeded",
	[12]		= "Parameter Problem",
	[13]		= "Timestamp Request",
	[14]		= "Timestamp Reply",
	[15]		= "Information Request",
	[16]		= "Information Reply",
	[17]		= "Address Mask Request",
	[18]		= "Address Mask Reply"
};

static void	handle_no_echoreply(const t_iphdr *ip, const t_icmphdr *icmp)
{
	const char *error;

	if (icmp->icmp__type < sizeof(g_responses))
		error = g_responses[icmp->icmp__type];
	else
		error = NULL;
	printf("From %s icmp_seq=%d %s\n",
		ft_ntoa((t_in_addr){.s_addr = ip->ip_srcaddr}),
		icmp->icmp__sequence,
		error);
}

void		analyze_rcvd_package(uint8_t *packet, t_ping *ping)
{
	const t_iphdr		*ip = (t_iphdr*)packet;
	const t_icmphdr		*icmp = (t_icmphdr*)(packet + sizeof(t_iphdr));
	const suseconds_t	rtt = get_rtt(icmp->icmp__timestamp);

	// printf("pid=%d\n
	// icmp__id=%d\n
	// icmp__type=%d\n
	// icmp__seq=%d\n", getpid(), icmp->icmp__id, icmp->icmp__type, icmp->icmp__sequence);
	if (htons(getpid()) != icmp->icmp__id)
		return ;
	if (icmp->icmp__type != ICMP_ECHOREPLY)
	{
		handle_no_echoreply(ip, icmp);
		return ;
	}
	printf("%u bytes from %s: icmp_seq=%d ttl=%d time=%ld.%02ldms\n",
		htons(ip->ip_totallength) - IP_HDR_SIZE,
		ft_ntoa((t_in_addr){.s_addr = ip->ip_srcaddr}),
		htons(icmp->icmp__sequence), ip->ip_ttl,
		rtt / 1000l, rtt % 1000l);
	(void)*ping;
}
