/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:50:40 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/02/28 17:57:06 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_check(char *str, char c)
{
	int	i;

	i = 0;
	if (ft_strlen(str) == 0)
		return (-1);
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

char	*fd_read(int fd, char *buffer)
{
	int			readbytes;
	char		*str;

	if (!buffer)
		buffer = ft_calloc(1, sizeof(char));
	str = malloc(BUFFER_SIZE + 1);
	if (!str)
		return (NULL);
	readbytes = 1;
	while (readbytes > 0)
	{
		readbytes = read(fd, str, BUFFER_SIZE);
		if (readbytes == -1)
			return (free(buffer), free(str), NULL);
		str[readbytes] = '\0';
		buffer = ft_free_join(buffer, str);
		if (!buffer)
			return (NULL);
		if (ft_check(str, '\n') != -1)
			break ;
	}
	free(str);
	return (buffer);
}

char	*sub_line(char *buffer)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	j = 0;
	line = NULL;
	if (!buffer || buffer[0] == '\0')
		return (NULL);
	while (buffer[i] != '\n' && buffer[i])
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] != '\n' && buffer[i])
		line[j++] = buffer[i++];
	if (buffer[i] == '\n')
		line[j++] = '\n';
	line[j] = '\0';
	return (line);
}

char	*get_rest(char *buffer)
{
	int		i;
	int		j;
	char	*rest;

	i = ft_check(buffer, '\n');
	j = 0;
	if (i == -1 || *buffer == '\0')
	{
		free(buffer);
		return (NULL);
	}
	rest = ft_calloc(ft_strlen(buffer) - i + 1, sizeof(char));
	if (!rest)
		return (NULL);
	i++;
	while (buffer[i])
		rest[j++] = buffer[i++];
	rest[j] = '\0';
	free(buffer);
	return (rest);
}

char	*get_next_line(int fd, void **result)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = fd_read(fd, buffer);
	if (!buffer)
		return (NULL);
	line = sub_line(buffer);
	buffer = get_rest(buffer);
	*result = line;
	return (line);
}
