/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgur <mgur@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:18:57 by mgur              #+#    #+#             */
/*   Updated: 2022/11/11 12:46:05 by mgur             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*last(char **s, char **line)
{
	int		len;
	char	*str;

	len = 0;
	while ((*s)[len] != '\n' && (*s)[len] != '\0')
		len++;
	if ((*s)[len] == '\n')
	{
		*line = ft_substr(*s, 0, len + 1);
		str = ft_strdup(&(*s)[len + 1]);
		free(*s);
		*s = str;
		if ((*s)[0] == 0)
		{
			free(*s);
			*s = 0;
		}
	}
	else
	{
		*line = ft_strdup(*s);
		free(*s);
		*s = 0;
	}
	return (*line);
}

char	*check(char **s, char **line, int count)
{
	if (count <= 0 && *s == NULL)
		return (0);
	return (last(&*s, line));
}

char	*get_next_line(int fd)
{
	static char	*s[1024];
	char		*line;
	char		*tmp;
	char		buffer[BUFFER_SIZE + 1];
	int			count;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	count = read(fd, buffer, BUFFER_SIZE);
	while (count > 0)
	{
		buffer[count] = 0;
		if (s[fd] == NULL)
			s[fd] = ft_strdup(buffer);
		else
		{
			tmp = ft_strjoin(s[fd], buffer);
			free(s[fd]);
			s[fd] = tmp;
		}
		if (ft_strchr(s[fd], '\n'))
			break ;
		count = read(fd, buffer, BUFFER_SIZE);
	}
	return (check(&s[fd], &line, count));
}
