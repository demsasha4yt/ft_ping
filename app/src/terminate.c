/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminate.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:50:36 by bharrold          #+#    #+#             */
/*   Updated: 2020/07/31 17:59:50 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void	terminate(int code, t_ping *ping)
{
	if (ping) {
		destroy_ping(&ping);
	}
	exit(code);
}

void 	terminate_usage(t_ping *ping)
{
	printf("Usage: ./ft_ping [-v] host\n");
	terminate(0, ping);
}

void 	terminate_error(int code, t_ping *ping)
{
	printf("Error code: %d\n", code);
	terminate(code, ping);
}
