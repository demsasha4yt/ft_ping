/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 15:00:55 by bharrold          #+#    #+#             */
/*   Updated: 2020/08/06 21:41:41 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	sigint(int sig)
{
	if (g_ping.sockfd > 0)
		close_socket(g_ping.sockfd);
	write(0, "\n", 1);
	exit(EXIT_SUCCESS);
	(void)sig;
}

void	mainloop(int sig)
{
	printf("mainloop: g_ping addr %p\n", &g_ping);
	printf("mainloop: g_ping.sockfd = %d\n", g_ping.sockfd);
	if (genpacket(&g_ping))
		sigint(0);
	send_ping_pckt(&g_ping.packet);
	printf("mainloop: SENT_PACKET:\n");
	print_msg_by_byte(g_ping.packet.msg);
	printf("mainloop: success\n");
	alarm(5);
	(void)sig;
}

void	recvloop(void)
{
	t_sockaddr_in	addr;
	uint8_t			packet[PACKET_SIZE];

	memset(&addr, 0, sizeof(addr));
	addr.sin_addr.s_addr = g_ping.s_addr;
	addr.sin_family = PF_INET;
	while (1)
	{
		recv_ping_response(g_ping.sockfd, packet, addr, 0);
		analyze_rcvd_package(packet, &g_ping);
	}
}

static int		makesignals(void)
{
	return (signal(SIGALRM, &mainloop) == SIG_ERR ||
		signal(SIGINT, &sigint) == SIG_ERR);
}

int		main(int argc, char **argv)
{
	memset(&g_ping, 0, sizeof(g_ping));
	if (check_input(argc, argv))
	{
		dprintf(2, "Usage: ping [-v] host\n");
		exit(EXIT_SUCCESS);
	}
	if (makesignals()) {
		dprintf(2, "ft_ping: Alarm failed\n");
		exit(EXIT_FAILURE);
	}
	if ((g_ping.sockfd = create_socket()) < 0)
		exit(EXIT_FAILURE);
	if (parse_input(argc, argv, &g_ping))
		exit(EXIT_FAILURE);
	printf("main: g_ping addr %p\n", &g_ping);
	printf("main: g_ping.sockfd = %d\n", g_ping.sockfd);
	mainloop(0);
	recvloop();
	return (0);
}