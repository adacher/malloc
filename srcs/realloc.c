/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   realloc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adacher <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 21:20:19 by adacher           #+#    #+#             */
/*   Updated: 2018/08/02 21:22:07 by adacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void		*malloc_cpy_free(t_box *box, void *ptr, size_t size)
{
	void		*tmp;
	size_t		size_two;

	tmp = malloc(size);
	size_two = (box->size > size) ? size : box->size;
	ft_memcpy(tmp, ptr, size_two);
	free(ptr);
	return (tmp);
}

static void		*large_realloc(t_box *box, size_t size, void *ptr)
{
	if (size <= box->size)
	{
		if (size > SMALL)
		{
			box->size = size;
			return (ptr);
		}
		else
			return (malloc_cpy_free(box, ptr, size));
	}
	else
		return (malloc_cpy_free(box, ptr, size));
}

static void		*default_realloc(t_box *box, size_t size, void *ptr)
{
	void		*tmp;
	size_t		size_two;

	if (size <= box->maxsize)
	{
		box->size = size;
		return (ptr);
	}
	else
	{
		tmp = malloc(size);
		if (tmp == NULL)
			return (NULL);
		size_two = (box->size > size) ? size : box->size;
		ft_memcpy(tmp, ptr, size_two);
		free(ptr);
		return (tmp);
	}
}

void			*realloc(void *ptr, size_t size)
{
	void		*tmp;
	t_box		*box;

	if (!ptr)
	{
		tmp = malloc(size);
		return (tmp);
	}
	if (size == 0)
	{
		if (ptr != NULL)
			free(ptr);
		tmp = malloc(1);
		return (tmp);
	}
	box = (t_box *)((void *)ptr - HEADER);
	if (box->magik != 42424242)
		return (NULL);
	if ((box->type == 1) || (box->type == 2))
		return (default_realloc(box, size, ptr));
	else
		return (large_realloc(box, size, ptr));
	return (NULL);
}
