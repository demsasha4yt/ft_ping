/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 15:01:15 by bharrold          #+#    #+#             */
/*   Updated: 2020/08/06 21:38:21 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <stdio.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netinet/ip_icmp.h>
# include <netinet/ip.h>
# include <netdb.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <time.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/time.h>

# include "ft_ping_types.h"

t_ping	g_ping;

int			check_input(int argc, char **argv);
int			parse_input(int argc, char **argv, t_ping *ping);
int			create_socket();
void		close_socket(int sockfd);
void		send_ping_pckt(t_ping_pckt *pckt);
void		recv_ping_response(int sockfd, uint8_t *packet, t_sockaddr_in addr,
				int options);
int			genpacket(t_ping *ping);
void		print_msg_by_byte(uint8_t *packet);
uint16_t	in_cksum(uint8_t *data, size_t length);
void		analyze_rcvd_package(uint8_t *packet, t_ping *ping);

#endif

/*
** FT_PING_H
*/