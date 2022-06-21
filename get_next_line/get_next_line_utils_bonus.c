/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: incshin <incshin@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 11:03:51 by incshin           #+#    #+#             */
/*   Updated: 2022/06/21 13:34:29 by incshin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list	*lstnew(ssize_t fd)
{
	t_list	*temp;

	temp = (t_list *)malloc(sizeof(t_list));
	if (!temp)
		return (0);
	temp->next = 0;
	temp->prev = 0;
	temp->offset = 0;
	temp->fd = fd;
	temp->buff = (char *)malloc(BUFFER_SIZE);
	if (!temp->buff)
	{
		free(temp);
		return (0);
	}
	temp->ret_read = read(fd, temp->buff, BUFFER_SIZE);
	if (temp->ret_read < 0)
	{
		free(temp->buff);
		free(temp);
		return (0);
	}
	return (temp);
}

void	lstadd_back(t_list **head, t_list **tail, t_list *new)
{
	if (!*head)
	{
		*head = new;
		*tail = new;
	}
	else
	{
		(*tail)->next = new;
		new->prev = *tail;
		*tail = new;
	}
}

void	lstdel(t_list *cur, t_list **phead, t_list **ptail)
{
	if (!cur)
		return ;
	if (cur->prev)
		cur->prev->next = cur->next;
	else
		*phead = cur->next;
	if (cur->next)
		cur->next->prev = cur->prev;
	else
		*ptail = cur->prev;
	cur->prev = 0;
	cur->next = 0;
	free(cur->buff);
	free(cur);
}

void	lstclear(t_list **head, t_list **tail, ssize_t fd)
{
	t_list	*cur;
	t_list	*temp;

	if (!head)
		return ;
	if (!*head)
		return ;
	cur = *head;
	while (cur)
	{
		if (fd == cur->fd)
		{
			temp = cur->next;
			lstdel(cur, head, tail);
			cur = temp;
		}
		else
			cur = cur->next;
	}
}
