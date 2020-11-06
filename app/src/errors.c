/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/05 23:57:41 by bharrold          #+#    #+#             */
/*   Updated: 2020/11/06 18:07:06 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void print_usage(void) 
{
	dprintf(2, "Usage: ping [-afhvq] [-i interval] [-t ttl] host\n\n\
Usage: ping -h for help\n");
}

void	print_error(int code)
{
	if (code == USAGE_ERROR) 
		print_usage();
	else {
		dprintf(2, "The program was exited with error code %d", code);
	}
}