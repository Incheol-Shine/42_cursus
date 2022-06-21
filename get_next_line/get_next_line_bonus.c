/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incshin <incshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:03:30 by incshin           #+#    #+#             */
/*   Updated: 2022/06/07 12:15:02 by incshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(ssize_t fd)
{
	t_list			*head;
	t_list			*tail;
	static t_backup	backup;
	char			*line;
	ssize_t			size;

	head = backup.head;
	tail = backup.tail;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	size = get_size(&head, &tail, fd);
	line = 0;
	if (size <= 0)
		lstclear(&head, &tail, fd);
	else
	{
		line = cpy_line(&head, &tail, size, fd);
		if (!line)
			lstclear(&head, &tail, fd);
	}
	backup.head = head;
	backup.tail = tail;
	return (line);
}

ssize_t	get_size(t_list **head, t_list **tail, ssize_t fd)
{
	t_list	*temp;
	ssize_t	size;

	temp = *head;
	size = 0;
	while (1)
	{
		while (temp && (fd != temp->fd))
			temp = temp->next;
		if (!temp)
		{
			temp = lstnew(fd);
			if (!temp)
				return (-1);
			if (temp->ret_read == 0)
			{
				free(temp->buff);
				free(temp);
				return (size);
			}
			lstadd_back(head, tail, temp);
		}
		if (get_size_find_nl(&temp, &size))
			return (size);
	}
}

ssize_t	get_size_find_nl(t_list **temp, ssize_t *size)
{
	ssize_t	i;

	i = (*temp)->offset;
	while (i < (*temp)->ret_read)
	{
		if ((*temp)->buff[i] == '\n')
			return (++(*size));
		i++;
		(*size)++;
	}
	*temp = (*temp)->next;
	return (0);
}

char	*cpy_line(t_list **head, t_list **tail, ssize_t size, ssize_t fd)
{
	char	*line;
	size_t	i;
	t_list	*cur;
	t_list	*temp;

	i = 0;
	cur = *head;
	line = (char *)malloc(size + 1);
	if (!line)
		return (0);
	line[size] = '\0';
	while (1)
	{
		while (fd != (cur)->fd)
			cur = (cur)->next;
		while ((cur)->offset < (size_t)(cur)->ret_read)
		{
			line[i++] = (cur)->buff[(cur)->offset++];
			if (!(--size))
				return (line);
		}
		temp = cur->next;
		lstdel(cur, head, tail);
		cur = temp;
	}
}
