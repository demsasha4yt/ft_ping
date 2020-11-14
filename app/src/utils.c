/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 18:33:14 by bharrold          #+#    #+#             */
/*   Updated: 2020/11/14 17:01:11 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

int			ft_atoi(const char *str)
{
	int		i;
	int		num;
	int		sign;

	i = 0;
	num = 0;
	sign = 1;
	while (*(str + i) == '\n' ||
		*(str + i) == '\t' ||
		*(str + i) == '\r' ||
		*(str + i) == '\v' ||
		*(str + i) == '\f' ||
		*(str + i) == ' ')
		i++;
	if (*(str + i) == '-')
		sign = -1;
	if (*(str + i) == '-' || *(str + i) == '+')
		i++;
	while (*(str + i) && *(str + i) >= '0' && *(str + i) <= '9')
		num = num * 10 + (*(str + i++) - '0');
	return (num * sign);
}

int			ft_isnumeric(char *str)
{
	if (str == NULL)
		return (0);
	while (str && *str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		str++;
	}
	return (1);
}

void		*ft_memset(void *b, int c, size_t len)
{
	char	*ptr;
	size_t	i;

	ptr = b;
	i = 0;
	while (i < len)
		*(ptr + i++) = c;
	return (b);
}

char		*ft_ntoa(t_in_addr in)
{
	static char		buffer[18];
	unsigned char	*bytes;

	bytes = (unsigned char *)&in;
	snprintf(buffer, sizeof(buffer), "%d.%d.%d.%d", \
		bytes[0], bytes[1], bytes[2], bytes[3]);
	return (buffer);
}

suseconds_t	ft_gettime(void)
{
	t_timeval	curr_time;

	if (gettimeofday(&curr_time, NULL) == -1)
	{
		dprintf(2, "failed getting time of day");
		return (0);
	}
	return (curr_time.tv_sec * 1000000 + curr_time.tv_usec);
}
