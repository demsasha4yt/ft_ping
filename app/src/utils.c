/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 18:33:14 by bharrold          #+#    #+#             */
/*   Updated: 2020/08/07 19:20:29 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

char			*ft_ntoa(t_in_addr in)
{
	static char		buffer[18];
	unsigned char	*bytes = (unsigned char *) &in;

	snprintf(buffer, sizeof(buffer), "%d.%d.%d.%d", \
		bytes[0], bytes[1], bytes[2], bytes[3]);
	return (buffer);
}

suseconds_t	ft_gettime(void)
{
	struct timeval	curr_time;

	if (gettimeofday(&curr_time, NULL) == -1)
	{
		dprintf(2, "failed getting time of day");
		return (0);
	}
	return (curr_time.tv_sec * 1000000 + curr_time.tv_usec);
}