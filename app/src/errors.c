/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/14 17:11:29 by bharrold          #+#    #+#             */
/*   Updated: 2020/11/14 17:50:44 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

const char	*g_usage = "Usage: ping [-afhvq] [-i interval] [-t ttl] host\n\n\
Usage: ping -h for help\n";

void		print_usage(void)
{
	dprintf(2, g_usage);
}

void		print_error(int code)
{
	if (code == USAGE_ERROR)
		print_usage();
	else
		dprintf(2, "The program was exited with error code %d", code);
}
