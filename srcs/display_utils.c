/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adacher <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 21:05:16 by adacher           #+#    #+#             */
/*   Updated: 2018/08/02 21:05:38 by adacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

void		format_hex(int n)
{
	char	c;

	if (n >= 10)
		c = n + 55;
	else
		c = n + 48;
	write(1, &c, 1);
}

void		format_addr(long n)
{
	if (n < 16)
		format_hex(n);
	else
	{
		format_addr(n / 16);
		format_hex(n % 16);
	}
}

void		display_addr(void *addr)
{
	ft_putstr("0x");
	format_addr((long)addr);
}
