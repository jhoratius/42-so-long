/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftsprintf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:01:15 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/04/02 15:06:17 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTSPRINTF_H
# define FTSPRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <bsd/string.h>
# include <stdio.h>
# include <ctype.h>
# include <limits.h>
# include <stdarg.h>
# include <stddef.h>

char	*ft_sprintf(char *buf, const char *str, ...);
int		ft_swrite_string(char *str, char **buff);
void	ft_swrite_pointer(void *ptr, char **buff);
int		ft_swrite_decimal(int n, char **buff);
int		ft_swrite_unsigned_decimal(unsigned int n, char *buff);
void	ft_swrite_hexadecimal(unsigned int n, char c, char *buff);
int		ft_shexa_conditions(int n, int next);
void	ft_sputnbr_base(unsigned long n, char *base, char *buff);
void	ft_sputchar(char c, char **buff);
char	*ft_sverifications(char c, va_list *args, char **buff, int *j);

#endif