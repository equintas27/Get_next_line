/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: equintas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 09:09:29 by equintas          #+#    #+#             */
/*   Updated: 2025/08/07 15:41:43 by equintas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_until_newline(int fd, char *saved, char *buffer)
{
	ssize_t	byte_read;
	char	*tmp;

	byte_read = 1;
	while (byte_read > 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
		{
			free(saved);
			return (NULL);
		}
		else if (byte_read == 0)
			break ;
		buffer[byte_read] = 0;
		if (saved == (void *)0)
			saved = ft_strdup("");
		tmp = saved;
		saved = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (saved);
}

static char	*extract_line_after_nl(char *line)
{
	char	*saved;
	size_t	i;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	saved = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (*saved == 0)
	{
		free(saved);
		saved = NULL;
	}
	return (saved);
}

static char	*get_only_one_line(char *line)
{
	size_t	i;

	if (line == (void *)0)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	return (ft_substr(line, 0, i));
}

char	*get_next_line(int fd)
{
	static char	*saved = NULL;
	char		*buffer;
	char		*line_read;
	char		*short_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == (void *)0)
		return (NULL);
	line_read = read_until_newline(fd, saved, buffer);
	free(buffer);
	if (line_read == (void *)0)
		return (NULL);
	short_line = get_only_one_line(line_read);
	saved = extract_line_after_nl(line_read);
	free(line_read);
	return (short_line);
}
