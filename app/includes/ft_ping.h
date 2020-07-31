/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ping.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 16:54:44 by bharrold          #+#    #+#             */
/*   Updated: 2020/07/31 19:57:08 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PING_H
# define FT_PING_H

# include <stdio.h>
# include "libft.h"

/*
** Main structure for FT_PING program
*/

typedef struct	s_ping
{
	int			flags;
}				t_ping;


t_ping			*make_ping();
void			destroy_ping(t_ping **);

int				validate_input(int, char **, t_ping*);

void			terminate(int code, t_ping *ping);
void			terminate_usage(t_ping *ping);
void			terminate_error(int code, t_ping *ping);

#endif
