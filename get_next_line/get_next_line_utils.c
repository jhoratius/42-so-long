/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/13 15:50:43 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/02/07 17:05:30 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*ptr;
	unsigned char	*c;
	size_t			i;

	i = 0;
	if (nmemb == 0 || size == 0)
		return (malloc(1));
	if (ULONG_MAX / nmemb < size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	c = ptr;
	while (i < size * nmemb)
	{
		*c = 0;
		c++;
		i++;
	}
	return (ptr);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	str = (char *)malloc((ft_strlen((char *)s1)) + (ft_strlen((char *)s2)) + 1);
	if (!str)
		return (NULL);
	while (s1 != NULL && s1[j] != '\0')
		str[i++] = s1[j++];
	j = 0;
	while (s2 != NULL && s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}

char	*ft_free_join(char *buffer, char *str)
{
	char	*tmp;

	tmp = ft_strjoin((char *)buffer, (char *)str);
	free(buffer);
	return (tmp);
}
