/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 16:43:24 by bharrold          #+#    #+#             */
/*   Updated: 2020/07/31 19:33:55 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_ping.h"
# include "libft.h"

t_ping	*make_ping()
{
	t_ping	*obj;

	if ((obj = ft_memalloc(sizeof(t_ping))) == NULL)
		exit(1);
	return (obj);
}

void	destroy_ping(t_ping **ping)
{
	ft_memdel((void**)ping);
}


int		main(int argc, char **argv)
{
	t_ping	*ping;

	(void) argv;
	(void) argc;
	ping = make_ping();
	if (validate_input(argc, argv, ping))
		terminate_error(1, ping);
	terminate(0, ping);
	return (0);
}
