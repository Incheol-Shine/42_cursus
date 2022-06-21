/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incshin <incshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:03:54 by incshin           #+#    #+#             */
/*   Updated: 2022/06/02 17:11:15 by incshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	struct s_list	*next;
	struct s_list	*prev;
	size_t			offset;
	ssize_t			fd;
	ssize_t			ret_read;
	char			*buff;
}				t_list;
typedef struct s_backup
{
	t_list	*head;
	t_list	*tail;
}				t_backup;
char	*get_next_line(ssize_t fd);
ssize_t	get_size(t_list **head, t_list **tail, ssize_t fd);
ssize_t	get_size_find_nl(t_list **temp, ssize_t *size);
char	*cpy_line(t_list **head, t_list **tail, ssize_t size, ssize_t fd);
t_list	*lstnew(ssize_t fd);
void	lstadd_back(t_list **head, t_list **tail, t_list *new);
void	lstdel(t_list *node, t_list **phead, t_list **ptail);
void	lstclear(t_list **head, t_list **tail, ssize_t fd);
#endif
