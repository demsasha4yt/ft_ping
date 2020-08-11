/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 21:36:40 by bharrold          #+#    #+#             */
/*   Updated: 2020/08/11 19:06:45 by bharrold         ###   ########.fr       */
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
};

static void			handle_no_echoreply(const t_iphdr *ip,
	const t_icmphdr *icmp, uint8_t *packet)
{
	const char		*error;
	t_icmphdr		*orig_icmp;

	orig_icmp = (t_icmphdr*)(packet + 2 * sizeof(t_iphdr) + 8);
	if (htons(getpid()) != orig_icmp->icmp__id)
		return ;
	if (icmp->icmp__type < sizeof(g_responses))
		error = g_responses[icmp->icmp__type];
	else
		error = NULL;
	g_ping.errors += 1;
	printf("From %s icmp_seq=%d %s\n",
		ft_ntoa((t_in_addr){.s_addr = ip->ip_srcaddr}),
		htons(orig_icmp->icmp__sequence),
		error);
}

void				debug_rcvd_package(const t_iphdr *ip, const t_icmphdr *icmp)
{
	printf("DEBUG RCVD PACKAGE: \n");
	printf("IP\n\
	ip_verlen=%d\n\
	ip_tos=%d\n\
	ip_totallength=%d\n\n",
	ip->ip_verlen,
	ip->ip_tos,
	ip->ip_totallength);
	printf("ICMP:\n\
	icmp_type=%d\n\
	icmp_code=%d\n\
	icmp__id=%d\n\
	icmp__sequence=%d\n\
	icmp__timestamp=%ld\n",
	icmp->icmp__type,
	icmp->icmp__code,
	icmp->icmp__id,
	icmp->icmp__sequence,
	icmp->icmp__timestamp);
}

void				analyze_rcvd_package(uint8_t *packet, t_ping *ping)
{
	const t_iphdr		*ip = (t_iphdr*)packet;
	const t_icmphdr		*icmp = (t_icmphdr*)(packet + sizeof(t_iphdr));
	const suseconds_t	rtt = get_rtt(icmp->icmp__timestamp);

	if (icmp->icmp__type != ICMP_ECHOREPLY)
	{
		handle_no_echoreply(ip, icmp, packet);
		return ;
	}
	if (htons(getpid()) != icmp->icmp__id)
		return ;
	g_ping.rcvd_pckgs += 1;
	printf("%u bytes from %s: icmp_seq=%d ttl=%d time=%ld.%02ldms\n",
		htons(ip->ip_totallength) - IP_HDR_SIZE,
		ft_ntoa((t_in_addr){.s_addr = ip->ip_srcaddr}),
		htons(icmp->icmp__sequence), ip->ip_ttl,
		rtt / 1000l, rtt % 1000l);
	(void)*ping;
}
