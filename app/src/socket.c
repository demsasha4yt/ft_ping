/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 15:54:16 by bharrold          #+#    #+#             */
/*   Updated: 2020/11/06 18:08:28 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int		create_socket(void)
{
	int	sockfd;

	if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0)
	{
		dprintf(2, "Can't initialize socket\n");
		return (sockfd);
	}
	if (setsockopt(sockfd, IPPROTO_UDP, IP_HDRINCL, (int[1]){1},
		sizeof(int32_t)) != -1)
	{
		dprintf(2, "Can't set socket options.");
		close_socket(sockfd);
		return (-1);
	}
	if (setsockopt(sockfd, IPPROTO_IP, IP_TTL, &g_ping.s_ttl,
		sizeof(g_ping.s_ttl)))
	{
		dprintf(2, "Can't set socket options.");
		close_socket(sockfd);
	}
	return (sockfd);
}

void	close_socket(int sockfd)
{
	close(sockfd);
}

void	send_ping_pckt(t_ping_pckt *pckt)
{
	ssize_t	ret;

	ret = sendto(pckt->sockfd, pckt->msg, pckt->len, pckt->flags,
		(struct sockaddr*)&pckt->to, sizeof(pckt->to));
	if (ret < 0)
	{
		dprintf(2, "ft_printf: sendto failed\n");
		close_socket(0);
		exit(EXIT_FAILURE);
	}
}

void	recv_ping_response(int sockfd, uint8_t *packet,
				t_sockaddr_in addr, int options)
{
	ssize_t		ret;
	t_msghdr	msg;
	t_iovec		io;
	uint8_t		buffer[512];

	ret = 0;
	ft_memset(&msg, 0, sizeof(msg));
	ft_memset(&io, 0, sizeof(io));
	ft_memset(buffer, 0, 512);
	io.iov_base = (void*)packet;
	io.iov_len = PACKET_SIZE;
	msg.msg_name = &addr;
	msg.msg_namelen = sizeof(addr);
	msg.msg_iov = &io;
	msg.msg_iovlen = 1;
	msg.msg_control = (void*)buffer;
	msg.msg_controllen = 512;
	ret = recvmsg(sockfd, &msg, 0);
	if (ret < 0)
		exit(EXIT_FAILURE);
	(void)options;
}
