/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 15:00:55 by bharrold          #+#    #+#             */
/*   Updated: 2020/11/06 18:47:43 by bharrold         ###   ########.fr       */
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
	printf("%d%% packet loss, time %ldms\n",
		(g_ping.transd_pckg - g_ping.rcvd_pckgs) * 100 / g_ping.transd_pckg,
		ft_gettime() / 1000l - g_ping.start_time / 1000l);
	if (!g_ping.errors && g_ping.min_tm > 0l && g_ping.max_tm > 0l)
		printf("rtt min/avg/max = %ld.%02ld/%ld.%02ld/%ld.%02ld ms", 
			g_ping.min_tm / 1000l, g_ping.min_tm % 1000l,
			g_ping.avg_tm / 1000l, g_ping.avg_tm % 1000l,
			g_ping.max_tm / 1000l, g_ping.max_tm % 1000l
			);
	printf("\n");
	exit(EXIT_SUCCESS);
	(void)sig;
}

void		mainloop(int sig)
{
	if (genpacket(&g_ping))
		sigint(0);
	send_ping_pckt(&g_ping.packet);
	g_ping.transd_pckg += 1;
	if (!g_ping.s_flood)
		alarm(g_ping.s_delay);
	(void)sig;
}

void		recvloop(void)
{
	t_sockaddr_in	addr;
	uint8_t			packet[PACKET_SIZE];

	ft_memset(&addr, 0, sizeof(addr));
	addr.sin_addr.s_addr = g_ping.s_addr;
	addr.sin_family = PF_INET;
	printf("PING %s (%s) %d(%d) bytes of data.\n", g_ping.addr,
		ft_ntoa((t_in_addr){.s_addr = g_ping.s_addr}),
		PAYLOAD_SIZE, PACKET_SIZE);
	while (1)
	{
		recv_ping_response(g_ping.sockfd, packet, addr, 0);
		analyze_rcvd_package(packet, &g_ping);
		if (g_ping.s_flood)
			mainloop(0);
	}
}

static int	makesignals(void)
{
	return (signal(SIGALRM, &mainloop) == SIG_ERR ||
		signal(SIGINT, &sigint) == SIG_ERR);
}

int			main(int argc, char **argv)
{
	ft_memset(&g_ping, 0, sizeof(g_ping));
	g_ping.s_ttl = DEFAULT_PING_TTL;
	g_ping.s_delay = DEFAULT_PING_DELAY;
	if (check_input(argc, argv))
	{
		print_error(USAGE_ERROR);
		exit(EXIT_SUCCESS);
	}
	if (makesignals())
	{
		dprintf(2, "ft_ping: Alarm failed\n");
		exit(EXIT_FAILURE);
	}
	if (parse_input(argv, &g_ping))
		exit(EXIT_FAILURE);
	if ((g_ping.sockfd = create_socket()) < 0)
		exit(EXIT_FAILURE);
	g_ping.start_time = ft_gettime();
	mainloop(0);
	recvloop();
	return (0);
}
