/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socket.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 17:23:28 by bharrold          #+#    #+#             */
/*   Updated: 2020/08/01 21:05:13 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int		init_socket()
{
	int sockfd;

	if((sockfd = socket(AF_INET, SOCK_RAW ,IPPROTO_UDP)) < 0)
	{
		dprintf(2, "Can't initialize socket");
		perror("socket");
		return (sockfd);
	}
	if(setsockopt(sockfd, IPPROTO_UDP, IP_HDRINCL, (int[1]){1},
		 sizeof(int32_t)) != -1) {
		dprintf(2, "Can't set socket options.");
		close_socket(sockfd);
		return (-1);
	}
	printf("return socket %d\n", sockfd);
	return (sockfd);
}

void	send_echo_request(int sockfd, const struct sockaddr *dest, uint8_t *packet, int options)
{
	ssize_t ret;

	printf("send_echo_request: sockfd = %d\n", sockfd);
	ret = sendto(sockfd, (void*)packet, PACKET_SIZE, 0, dest, sizeof(struct sockaddr *));
	if (ret == -1)
	{
		perror("sendto");
		dprintf(2, "sendto failed.\n");
		close_socket(0);
	}
	if (options > 0)
		{}
}

void	rcv_echo_response(int sockfd, struct sockaddr_in *addr, uint8_t *packet, int options)
{
	uint8_t	buffer[512];
	struct iovec iov;
	struct msghdr msg;
	ssize_t ret;

	printf("rcv_echo_response: sockfd = %d\n", sockfd);
	iov.iov_base = packet;
	iov.iov_len = PACKET_SIZE;
	msg.msg_name = &addr;
	msg.msg_namelen = sizeof(addr);
	msg.msg_iov = &iov;
	msg.msg_iovlen = sizeof(iov);
	msg.msg_control = buffer;
	msg.msg_controllen = sizeof(buffer);
	msg.msg_flags = 0;
	ret = recvmsg(sockfd, &msg, 0);
	printf("rcv_echo_response: ret = %ld\n", ret);
	if (ret == -1)
	{
		perror("recvmsg");
		dprintf(2, "recvmsg failed.\n");
		close_socket(0);
	}
	printf("%ld\n", ret);
	if (options)
	{

	}
}