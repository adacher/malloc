/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adacher <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/02 21:46:42 by adacher           #+#    #+#             */
/*   Updated: 2018/08/02 21:54:04 by adacher          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <unistd.h>
# include <string.h>
# include <sys/mman.h>
# include <sys/resource.h>
# include <stdio.h>
# include <signal.h>
# define TINY 1024
# define SMALL 4096
# define ALIGN(x) ((((x) >> 3) << 3) + 8)
# define BOX sizeof(t_box)
# define HEADER sizeof(t_box_header)

typedef struct		s_box_header
{
	struct s_box	*next;
	struct s_box	*prev;
	void			*end;
	size_t			size;
	int				busy;
	int				type;
	size_t			maxsize;
	long			magik;
}					t_box_header;

typedef struct		s_box
{
	struct s_box	*next;
	struct s_box	*prev;
	void			*end;
	size_t			size;
	int				busy;
	int				type;
	size_t			maxsize;
	long			magik;
	char			data[1];
}					t_box;

typedef struct		s_boxtype
{
	t_box			*tiny;
	t_box			*small;
	t_box			*large;
}					t_boxtype;

void				*realloc(void *ptr, size_t size);
void				*tors_malloc(size_t size, t_box **addr, unsigned int type);
void				free(void *ptr);
void				show_alloc_mem(void);
t_box				*init_box_large(size_t size, void *ptr, unsigned int type);
t_box				*init_box(size_t size, void *ptr, t_box *prev, void *end);
int					check_which_size(size_t size);
void				format_hex(int n);
void				format_addr(long n);
void				display_addr(void *addr);
void				tiny_beginning(t_box *tmp);
void				small_beginning(t_box *tmp);
void				large_beginning(t_box *tmp);
void				intermediate_display(t_box *tmp);
void				end_display(size_t total);
void				*large_malloc(size_t size, t_box **addr);
void				*malloc(size_t size);
void				ft_putchar(char c);
void				ft_putstr(char const *s);
void				ft_putnbr(int n);
void				*ft_memcpy(void *s1, const void *s2, size_t n);

#endif
