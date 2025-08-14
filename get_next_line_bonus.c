/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/06 14:40:06 by equintas          #+#    #+#             */
/*   Updated: 2025/08/08 14:18:33 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*read_until_newline(int fd, char *saved, char *buffer)
{
	ssize_t	byte_read;
	char	*tmp;

	if (saved == NULL)
		saved = ft_strdup("");
	byte_read = 1;
	while (!ft_strchr(saved, '\n') && byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(saved);
			return (NULL);
		}
		if (byte_read == 0)
			break ;
		buffer[byte_read] = '\0';
		tmp = saved;
		saved = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (saved == (void *)0)
			return (NULL);
	}
	return (saved);
}

static char	*get_and_extract_line(char *line, int c)
{
	char	*saved;
	size_t	i;

	if (line == (void *)0)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	if (c == 1)
	{
		saved = ft_strdup(line + i);
		if (saved == (void *)0 || *saved == '\0')
		{
			free(saved);
			return (NULL);
		}
		return (saved);
	}
	else if (c == 2)
	{
		return ((ft_substr(line, 0, i)));
	}
	return (NULL);
}

static t_fd_list	*get_fd_node(t_fd_list **head, int fd)
{
	t_fd_list	*pres;

	pres = *head;
	while (pres)
	{
		if (pres->fd == fd)
			return (pres);
		pres = pres->next;
	}
	pres = malloc(sizeof(t_fd_list));
	if (!pres)
		return (NULL);
	pres->fd = fd;
	pres->str = NULL;
	pres->next = *head;
	*head = pres;
	return (pres);
}

static void	free_fd_list(t_fd_list **head_list, int fd)
{
	t_fd_list	*current;
	t_fd_list	*prev;

	current = *head_list;
	prev = NULL;
	while (current)
	{
		if (current->fd == fd)
		{
			if (prev)
				prev->next = current->next;
			else
				*head_list = current->next;
			if (current->str)
				free(current->str);
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

char	*get_next_line(int fd)
{
	static t_fd_list	*head_list = NULL;
	t_fd_list			*node;
	char				*buffer;
	char				*line;
	char				*rest;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == (void *)0)
		return (NULL);
	node = get_fd_node(&head_list, fd);
	if (node == (void *)0)
		return (free(buffer), NULL);
	node->str = read_until_newline(node->fd, node->str, buffer);
	free(buffer);
	if (node->str == (void *)0 || *(node->str) == '\0')
		return (free_fd_list(&head_list, fd), NULL);
	line = get_and_extract_line(node->str, 2);
	rest = get_and_extract_line(node->str, 1);
	free(node->str);
	node->str = rest;
	if (!rest)
		free_fd_list(&head_list, fd);
	return (line);
}
