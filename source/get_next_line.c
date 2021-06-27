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
typedef unsigned char	t_uchar;

static void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		*(char *)(dst + i) = *(const char *)(src + i);
		i++;
	}
	return (dst);
}

static void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	new_ptr = malloc(new_size);
	if (old_size != 0 && new_ptr != NULL)
		ft_memcpy(new_ptr, ptr, new_size);
	if (old_size != 0)
		free(ptr);
	return (new_ptr);
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

static bool	flush_buffer(char *buffer, char **line, size_t *line_len)
{
	size_t	eol_index;
	bool	rezult;

	eol_index = 0;
	while (buffer[eol_index] != '\n' && buffer[eol_index] != '\0')
		eol_index++;
	rezult = false;
	if (buffer[eol_index] == '\n')
	{
		rezult = true;
		buffer[eol_index++] = '\0';
	}
	*line = ft_realloc(*line, *line_len, *line_len + eol_index);
	if (*line == NULL)
		return (false);
	ft_memcpy(*line + *line_len, buffer, eol_index);
	ft_strcpy(buffer, buffer + eol_index);
	*line_len += eol_index;
	return (rezult);
}

int	get_next_line(int fd, char **line)
{
	static char	buffer[BUFFER_SIZE + 1];
	size_t		line_len;
	ssize_t		read_len;

	line_len = 0;
	read_len = 1;
	while (read_len > 0)
	{
		if (*buffer != '\0')
		{
			if (flush_buffer(buffer, line, &line_len))
				return (1);
		}
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len >= 0)
			buffer[read_len] = '\0';
	}
	return ((int)read_len);
}
