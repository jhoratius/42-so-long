/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhoratiu <jhoratiu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 15:01:15 by jhoratiu          #+#    #+#             */
/*   Updated: 2024/03/22 14:10:57 by jhoratiu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FTPRINTF_H
# define FTPRINTF_H

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
int		ft_write_string(char *str, char **buff);
void	ft_write_pointer(void *ptr, char **buff);
int 	ft_write_decimal(int n, char **buff);
int 	ft_write_unsigned_decimal(unsigned int n, char *buff);
void	ft_write_hexadecimal(unsigned int n, char c, char *buff);
void	ft_putnbr_base(unsigned long n, char *base, char *buff);
void	ft_putchar(char c, char **buff);
char	*ft_verifications(char c, va_list *args, char **buff, int *j);
int		ft_strlen(char *str);

#endif