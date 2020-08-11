/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 15:00:55 by bharrold          #+#    #+#             */
/*   Updated: 2020/08/11 18:56:59 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void		sigint(int sig)
{
	if (g_ping.sockfd > 0)
		close_socket(g_ping.sockfd);
	write(1, "\n", 1);
	printf("--- %s ping statistics ---\n",
	ft_ntoa((t_in_addr){.s_addr = g_ping.s_addr}));
	printf("%d packets transmitted, %d received, ",
	g_ping.transd_pckg, g_ping.rcvd_pckgs);
	if (g_ping.errors)
		printf("+%d errors, ", g_ping.errors);
	printf("%d%% packet loss, time %ldms\n\n",
		(g_ping.transd_pckg - g_ping.rcvd_pckgs) / g_ping.transd_pckg * 100,
		ft_gettime() / 1000l - g_ping.start_time / 1000l);
	exit(EXIT_SUCCESS);
	(void)sig;
}

void		mainloop(int sig)
{
	if (genpacket(&g_ping))
		sigint(0);
	send_ping_pckt(&g_ping.packet);
	g_ping.transd_pckg += 1;
	alarm(g_ping.s_delay);
	(void)sig;
}

void		recvloop(void)
{
	t_sockaddr_in	addr;
	uint8_t			packet[PACKET_SIZE];

	memset(&addr, 0, sizeof(addr));
	addr.sin_addr.s_addr = g_ping.s_addr;
	addr.sin_family = PF_INET;
	printf("PING %s (%s) %d(%d) bytes of data.\n", g_ping.addr,
		ft_ntoa((t_in_addr){.s_addr = g_ping.s_addr}),
		PAYLOAD_SIZE, PACKET_SIZE);
	while (1)
	{
		recv_ping_response(g_ping.sockfd, packet, addr, 0);
		analyze_rcvd_package(packet, &g_ping);
	}
}

static int	makesignals(void)
{
	return (signal(SIGALRM, &mainloop) == SIG_ERR ||
		signal(SIGINT, &sigint) == SIG_ERR);
}

int			main(int argc, char **argv)
{
	memset(&g_ping, 0, sizeof(g_ping));
	g_ping.s_ttl = DEFAULT_PING_TTL;
	g_ping.s_delay = DEFAULT_PING_DELAY;
	if (check_input(argc, argv))
	{
		dprintf(2, "Usage: ping [-v] host\n");
		exit(EXIT_SUCCESS);
	}
	if (makesignals())
	{
		dprintf(2, "ft_ping: Alarm failed\n");
		exit(EXIT_FAILURE);
	}
	if ((g_ping.sockfd = create_socket()) < 0)
		exit(EXIT_FAILURE);
	if (parse_input(argc, argv, &g_ping))
		exit(EXIT_FAILURE);
	g_ping.start_time = ft_gettime();
	mainloop(0);
	recvloop();
	return (0);
}
