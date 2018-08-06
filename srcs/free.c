/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adacher <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 21:12:00 by adacher           #+#    #+#             */
/*   Updated: 2018/08/02 21:13:11 by adacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_boxtype	*g_val;

static void	use_munmap(t_box *tmp)
{
	t_box *ptr;

	if (tmp)
	{
		ptr = tmp->next;
		if (tmp->prev)
			tmp->prev->next = ptr;
		else
			g_val->large = ptr;
		if (ptr)
			ptr->prev = tmp->prev;
		tmp->busy = 0;
		munmap(tmp, tmp->size);
	}
}

void		free(void *ptr)
{
	t_box	*box;
	t_box	*tmp;

	if (!ptr)
		return ;
	box = (t_box *)((void *)ptr - HEADER);
	if (box->type != 3)
		box->busy = 0;
	else
	{
		tmp = g_val->large;
		while (tmp)
		{
			if (tmp == box)
				break ;
			else
				tmp = tmp->next;
		}
		use_munmap(tmp);
	}
	return ;
}
