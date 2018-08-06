/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_steps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adacher <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 21:11:46 by adacher           #+#    #+#             */
/*   Updated: 2018/08/02 21:11:47 by adacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_boxtype	*g_val;

void		tiny_beginning(t_box *tmp)
{
	if (g_val->tiny)
		ft_putstr("TINY : ");
	display_addr(tmp);
	ft_putchar('\n');
}

void		small_beginning(t_box *tmp)
{
	if (g_val->small)
		ft_putstr("SMALL : ");
	display_addr(tmp);
	ft_putchar('\n');
}

void		large_beginning(t_box *tmp)
{
	if (g_val->large)
		ft_putstr("LARGE : ");
	display_addr(tmp);
	ft_putchar('\n');
}

void		intermediate_display(t_box *tmp)
{
	display_addr(tmp->data);
	ft_putstr(" - ");
	display_addr((char *)tmp->data + tmp->size);
	ft_putstr(" : ");
	ft_putnbr((int)tmp->size);
	ft_putstr(" bytes");
	ft_putchar('\n');
}

void		end_display(size_t total)
{
	ft_putstr("Total : ");
	ft_putnbr((int)total);
	ft_putstr(" bytes");
	ft_putchar('\n');
}
