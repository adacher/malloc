/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_mem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adacher <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 21:16:09 by adacher           #+#    #+#             */
/*   Updated: 2018/08/02 21:18:03 by adacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_boxtype		*g_val;

static size_t	display_tiny(t_box *tmp)
{
	size_t		count;

	count = 0;
	tiny_beginning(tmp);
	while (tmp)
	{
		if (tmp->busy == 1)
		{
			count += tmp->size;
			intermediate_display(tmp);
		}
		tmp = tmp->next;
	}
	return (count);
}

static size_t	display_small(t_box *tmp)
{
	size_t		count;

	count = 0;
	small_beginning(tmp);
	while (tmp)
	{
		if (tmp->busy == 1)
		{
			count += tmp->size;
			intermediate_display(tmp);
		}
		tmp = tmp->next;
	}
	return (count);
}

static size_t	display_large(t_box *tmp)
{
	size_t		count;

	count = 0;
	large_beginning(tmp);
	while (tmp)
	{
		count += tmp->size;
		intermediate_display(tmp);
		tmp = tmp->next;
	}
	return (count);
}

void			show_alloc_mem(void)
{
	size_t		total;

	total = 0;
	if (!g_val || !(g_val->tiny || g_val->small || g_val->large))
		return ;
	if (g_val->tiny)
		total += display_tiny(g_val->tiny);
	if (g_val->small)
		total += display_small(g_val->small);
	if (g_val->large)
		total += display_large(g_val->large);
	end_display(total);
}
