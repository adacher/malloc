/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_malloc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adacher <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 21:05:52 by adacher           #+#    #+#             */
/*   Updated: 2018/08/02 21:11:40 by adacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"

static void	*zone_mmap(int i)
{
	t_box	*box;

	if ((box = mmap(NULL, i, PROT_READ | PROT_WRITE,
			MAP_ANON | MAP_SHARED, -1, 0)) == (void *)-1)
		return (NULL);
	return (box);
}

static int	calculate_zone_size(unsigned int type)
{
	int		i;

	if (type == 1)
		i = (TINY + sizeof(t_box)) * 100;
	else
		i = (SMALL + sizeof(t_box)) * 100;
	i = (i / 4096) + 1;
	return (getpagesize() * i);
}

static void	*create_first_page(t_box **addr, size_t size, unsigned int type)
{
	int		l_zone;
	void	*zone;
	t_box	*tmp;

	l_zone = calculate_zone_size(type);
	if ((zone = zone_mmap(l_zone)) == NULL)
		return (NULL);
	tmp = init_box(size, zone, NULL, zone + l_zone);
	*addr = tmp;
	return (&(tmp->data));
}

static void	*add_box_or_new_page(t_box *last, size_t size, unsigned int type)
{
	t_box	*next;
	void	*end;
	int		l_zone;
	void	*zone;

	next = (t_box *)((void *)last + BOX + last->size);
	next = (void *)ALIGN((long)next);
	end = last->end;
	if (((void *)next + BOX + size) <= end)
	{
		next = init_box(size, next, last, NULL);
		last->next = next;
		return (&(next)->data);
	}
	else
	{
		l_zone = calculate_zone_size(type);
		if ((zone = zone_mmap(l_zone)) == NULL)
			return (NULL);
		next = init_box(size, zone, NULL, zone + l_zone);
		last->next = next;
		return (&(next->data));
	}
}

void		*tors_malloc(size_t size, t_box **addr, unsigned int type)
{
	t_box	*tmp;
	t_box	*last;

	if (!(*addr))
		return (create_first_page(addr, size, type));
	tmp = *addr;
	while (tmp)
	{
		if (!(tmp->busy) && tmp->maxsize >= size)
		{
			tmp->busy = 1;
			tmp->size = size;
			return (&(tmp->data));
		}
		last = tmp;
		tmp = tmp->next;
	}
	return (add_box_or_new_page(last, size, type));
}
