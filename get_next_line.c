/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:38:00 by ampjimen          #+#    #+#             */
/*   Updated: 2023/12/04 18:34:43 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *str)
{
	char	*buf;
	int		bytes;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free(str), NULL);
	bytes = 1;
	while (!ft_strchr(str, '\n') && bytes > 0)
	{
		bytes = read(fd, buf, BUFFER_SIZE);
		if (bytes == -1)
		{
			free(buf);
			free(str);
			return (NULL);
		}
		buf[bytes] = '\0';
		str = ft_strjoin(str, buf);
	}
	free(buf);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*str;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	str = ft_read(fd, str);
	if (!str)
		return (NULL);
	line = ft_line(str);
	if (!line)
		return (free(str), str = NULL, NULL);
	str = ft_next_line(str);
	return (line);
}

int main (void)
{
	char	*line;
	int		fd1;
	
	fd1 = open("text.txt", O_RDONLY);
	
	while (1)
	{
		line = get_next_line(fd1);
		printf("line : %s", line);
		if (line == NULL)
		{
			break;
		}
		free(line);
	}
	system("leaks -q a.out");
	return(0);
} 