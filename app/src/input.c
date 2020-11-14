/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 15:21:27 by bharrold          #+#    #+#             */
/*   Updated: 2020/11/14 17:04:07 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

static int		iflag(char *src, uint32_t *dest)
{
	int		value;

	if (!ft_isnumeric(src))
		return (1);
	value = ft_atoi(src);
	if (value <= 0 || value >= 255)
		return (1);
	*dest = value;
	return (0);
}

static int		parse_flags(char ***av, t_ping *ping)
{
	while ((*av)[1] && (*av)[1][0] == '-')
	{
		if ((*av)[1][0] == '-' && (*av)[1][1] == 'h')
			return (1);
		else if ((*av)[1][0] == '-' && (*av)[1][1] == 'v')
			ping->s_vmode = 1;
		else if ((*av)[1][0] == '-' && (*av)[1][1] == 'q')
			ping->s_quite = 1;
		else if ((*av)[1][0] == '-' && (*av)[1][1] == 'a')
			ping->s_audibble = 1;
		else if ((*av)[1][0] == '-' && (*av)[1][1] == 'f')
			ping->s_flood = 1;
		else if ((*av)[1][0] == '-' && (*av)[1][1] == 't' &&
			iflag((++(*av))[1], &ping->s_ttl))
			return (1);
		else if ((*av)[1][0] == '-' && (*av)[1][1] == 'i' &&
			iflag((++(*av))[1], &ping->s_delay))
			return (1);
		(*av)++;
	}
	return ((*av)[1] == NULL);
}

int				parse_input(char **av, t_ping *ping)
{
	t_addrinfo	hints;
	t_addrinfo	*addrinfo;

	memset(&hints, 0, sizeof(hints));
	hints.ai_family = AF_INET;
	if (parse_flags(&av, ping))
	{
		print_error(USAGE_ERROR);
		return (USAGE_ERROR);
	}
	if (av[1] == NULL)
	{
		print_error(USAGE_ERROR);
		return (USAGE_ERROR);
	}
	if (getaddrinfo(av[1], NULL, &hints, &addrinfo))
	{
		dprintf(2, "ft_ping: Can't resolve host %s\n", av[1]);
		return (1);
	}
	ping->s_addr = ((t_sockaddr_in*)addrinfo->ai_addr)->sin_addr.s_addr;
	ping->addr = av[1];
	freeaddrinfo(addrinfo);
	return (0);
}

int				check_input(int ac, char **av)
{
	return (ac < 2 ||
		(av[1][0] == '-' && av[1][1] == 'v' && av[1][2] == '\0' && ac == 2) ||
		(av[1][0] == '-' && av[1][1] == 'h' && av[1][2] == '\0' && ac == 2));
}
