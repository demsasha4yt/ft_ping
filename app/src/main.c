/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 16:43:24 by bharrold          #+#    #+#             */
/*   Updated: 2020/08/01 21:16:56 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_ping.h"

static t_ping g_ping = {
	.ttl = DEFAULT_TTL,
	.ping_delay = DEFAULT_PING_DELAY,
	.sequence = 0,
	.dest_addr = NULL,
	.ping_addr = {
		.sin_family = PF_INET,
		.sin_port = 0
	},
	.packet = ""
};

void	 close_socket(int sig)
{
	printf("close_socket: g_ping addr %p\n", &g_ping);
	printf("close_socket: g_ping.sock = %d\n", g_ping.sock);
	close(g_ping.sock);
	g_ping.sock = 0;
	exit (0);
	(void)sig;
}

void	sendloop(int sig)
{
	printf("sendloop: g_ping addr %p\n", &g_ping);
	printf("sendloop: g_ping.sock = %d\n", g_ping.sock);

	if (gen_packet(&g_ping))
		exit(EXIT_FAILURE);
	print_header_by_byte(&g_ping);
	printf("sendloop [2]: g_ping addr %p\n", &g_ping);
	printf("sendloop [2]: g_ping.sock = %d\n", g_ping.sock);
	send_echo_request(g_ping.sock, (const struct sockaddr*)&g_ping.ping_addr,
		g_ping.packet, 0);
	alarm(10);
	(void)sig;
}

void	recvloop(void)
{
	uint8_t packet[PACKET_SIZE];

	while (1) {
		printf("sendloop: g_ping addr %p\n", &g_ping);
		printf("sendloop: g_ping.sock = %d\n", g_ping.sock);
		rcv_echo_response(g_ping.sock, &g_ping.ping_addr, packet, 0);
	}
}

int		main(int argc, char **argv)
{
	if (check_input(argc, argv))
	{
		dprintf(2, "Usage: ping [-v] host\n");
		exit(0);
	}
	if (signal(SIGALRM, &sendloop) == SIG_ERR
	|| signal(SIGINT, &close_socket) == SIG_ERR) {
		dprintf(2, "alarm failed");
		exit(EXIT_FAILURE);
	}
	if ((g_ping.sock = init_socket()) == -1)
		exit(EXIT_FAILURE);
	if ((g_ping.dest_addr = parse_input(argc, argv, &g_ping)) == NULL)
		exit(EXIT_FAILURE);

	printf("main: g_ping addr %p\n", &g_ping);
	printf("main: g_ping.sock = %d\n", g_ping.sock);
	sendloop(0);
	recvloop();
	return (0);
}
