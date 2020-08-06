/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyze.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 21:36:40 by bharrold          #+#    #+#             */
/*   Updated: 2020/08/06 21:40:12 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

void		analyze_rcvd_package(uint8_t *packet, t_ping *ping)
{
	printf("analyze_rcvd_package: START\n");
	print_msg_by_byte(packet);
	printf("analyze_rcvd_package: END\n");
	(void)ping;
}