/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 21:15:21 by bharrold          #+#    #+#             */
/*   Updated: 2020/08/01 21:16:15 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

char*	parse_input(int argc, char **argv, t_ping *ping)
{
	struct addrinfo	hints = {.ai_family = AF_INET};
	struct addrinfo *ainfo;

	if (argc > 2 && argv[1][0] == '-' && argv[1][1] == 'v' && argv[1][2] == '\0')
	{
		ping->v_mode = 1;
		argv++;
	}
	if (getaddrinfo(argv[1], NULL, &hints, &ainfo))
	{
		dprintf(2, "ft_ping: Can't resolve host %s", argv[1]);
		return (NULL);
	}
	ping->ping_addr.sin_family = PF_INET;
	ping->ping_addr.sin_port = 0;
	ping->ping_addr.sin_addr.s_addr = ((struct sockaddr_in*)ainfo->ai_addr)->sin_addr.s_addr;
	freeaddrinfo(ainfo);
	return (argv[1]);
}

int check_input(int argc, char **argv)
{
	return (argc < 2 ||
		(argv[1][0] == '-' && argv[1][1] == 'v' && argv[1][2] == '\0' && argc == 2));
}