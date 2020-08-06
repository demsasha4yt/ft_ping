/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   in_cksum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bharrold <bharrold@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 16:31:49 by bharrold          #+#    #+#             */
/*   Updated: 2020/08/06 20:01:27 by bharrold         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ping.h"

uint32_t	compute_acc(uint16_t word, uint32_t acc)
{
	acc += ntohs(word);
	if (acc > 0xffff)
		acc -= 0xffff;
	return acc;
}

uint16_t	in_cksum(uint8_t *data, size_t length)
{
	uint32_t	acc;
	uint16_t	word;
	size_t		i;

	i = 0;
	acc = 0xffff;
	word = 0;
	while (i < length)
	{
		memcpy(&word, data + i, 2);
		acc = compute_acc(word, acc);
		i += 2;
	}
	if (length & 1)
	{
		memcpy(&word, data + length, 1);
		acc = compute_acc(word, acc);
	}
	return (htons(~acc));
}