/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ampjimen <ampjimen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:21:44 by ampjimen          #+#    #+#             */
/*   Updated: 2023/12/04 19:02:11 by ampjimen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*str[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	str[fd] = ft_read(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = ft_line(str[fd]);
	if (!line)
		return (free(str[fd]), str[fd] = NULL, NULL);
	str[fd] = ft_next_line(str[fd]);
	return (line);
}

void friki()
{
	system("leaks a.out");
}
 int	main(void)
{
	atexit(friki);
 	char	*line;
 	int		fd1;
 	fd1 = open("text1.txt", O_RDONLY);
 	 while (1)
 	 {
 		line = get_next_line(fd1);
		printf("line : %s", line); 		
		if (line == NULL)
			break;
 		free(line);	
		
}	
	return (0);
}