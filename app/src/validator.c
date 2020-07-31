/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validator.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 17:48:22 by bharrold          #+#    #+#             */
/*   Updated: 2020/07/31 19:35:57 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"


int validate_input(int argc, char **argv, t_ping *ping)
{
	int	i;

	i = 0;
	if (argc < 2)
		terminate_usage(ping);
	while(++i < argc)
		printf("%s\n", argv[i]);
	return (0);
}
