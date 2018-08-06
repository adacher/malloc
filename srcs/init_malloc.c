/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_malloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adacher <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 21:18:24 by adacher           #+#    #+#             */
/*   Updated: 2018/08/02 21:20:06 by adacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

t_box		*init_box(size_t size, void *ptr, t_box *prev, void *end)
{
	t_box	*box;

	box = (t_box *)ptr;
	if (size <= TINY)
		box->type = 1;
	else
		box->type = 2;
	box->size = size;
	box->maxsize = size;
	box->busy = 1;
	box->next = NULL;
	box->magik = 42424242;
	if (end != NULL)
	{
		box->end = end;
		box->prev = NULL;
	}
	else
	{
		box->prev = prev;
		box->end = box->prev->end;
	}
	return (box);
}

t_box		*init_box_large(size_t size, void *ptr, unsigned int type)
{
	t_box	*box;

	box = (t_box *)ptr;
	box->next = NULL;
	box->size = size;
	box->busy = 1;
	box->type = type;
	box->magik = 42424242;
	return (box);
}

int			check_which_size(size_t size)
{
	if (size <= TINY)
		return (1);
	else if (size <= SMALL)
		return (2);
	else
		return (3);
}
