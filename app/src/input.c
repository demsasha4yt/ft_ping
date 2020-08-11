/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 15:21:27 by bharrold          #+#    #+#             */
/*   Updated: 2020/08/11 18:33:11 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"


int		parse_input(int argc, char **argv, t_ping *ping)
{
	t_addrinfo hints = {.ai_family = AF_INET};
	t_addrinfo *addrinfo;

	if (argc > 2 && argv[1][0] == '-' && argv[1][1] == 'v' && argv[1][2] == '\0')
	{
		ping->s_vmode = 1;
		argv++;
	}
	if (getaddrinfo(argv[1], NULL, &hints, &addrinfo))
	{
		dprintf(2, "ft_ping: Can't resolve host %s\n", argv[1]);
		return (1);
	}
	ping->s_addr = ((t_sockaddr_in*)addrinfo->ai_addr)->sin_addr.s_addr;
	ping->addr = argv[1];
	freeaddrinfo(addrinfo);
	return (0);
}

int		check_input(int argc, char **argv)
{
	return (argc < 2 ||
		(argv[1][0] == '-' && argv[1][1] == 'v' && argv[1][2] == '\0' && argc == 2));
}