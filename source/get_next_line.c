/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ssantiag <ssantiag@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/26 14:18:50 by ssantiag          #+#    #+#             */
/*   Updated: 2021/06/26 14:18:50 by ssantiag         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	void	*dest;

	dest = dst;
	while (n-- > 0)
		*(char *)(dst++) = *(const char *)(src++);
	return (dest);
}

static char	*ft_strcpy(char *dest, char *src)
{
	char	*dest_pointer;

	dest_pointer = dest;
	while (true)
	{
		*dest_pointer++ = *src;
		if (*src++ == '\0')
			break ;
	}
	return (dest);
}

static void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	new_ptr = malloc(new_size);
	if (old_size != 0 && new_ptr != NULL)
		ft_memcpy(new_ptr, ptr, old_size);
	if (old_size != 0)
		free(ptr);
	return (new_ptr);
}

static bool	flush_buffer(char *buffer, char **line, size_t *line_len)
{
	size_t	eol_index;
	int		rezult;

	eol_index = 0;
	while (buffer[eol_index] != '\n' && buffer[eol_index] != '\0')
		eol_index++;
	rezult = 0;
	if (buffer[eol_index] == '\n')
		rezult = 1;
	*line = ft_realloc(*line, *line_len, *line_len + eol_index + rezult * 2);
	if (*line == NULL)
		return (true);
	ft_memcpy(*line + *line_len, buffer, eol_index + rezult);
	ft_strcpy(buffer, buffer + eol_index + rezult);
	*line_len += eol_index + rezult;
	if (rezult == 1)
		(*line)[*line_len] = '\0';
	return (rezult == 1);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	size_t		line_len;
	ssize_t		read_len;
	char		*line;

	line = NULL;
	line_len = 0;
	read_len = 1;
	while (read_len > 0)
	{
		if (*buffer != '\0' && flush_buffer(buffer, &line, &line_len))
			return (line);
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len >= 0)
			buffer[read_len] = '\0';
	}
	if (read_len <= 0 && line_len == 0)
		return (NULL);
	line = ft_realloc(line, line_len, line_len + 1);
	line[line_len] = '\0';
	return (line);
}
