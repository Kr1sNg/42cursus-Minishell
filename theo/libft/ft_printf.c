/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 13:53:17 by tbahin            #+#    #+#             */
/*   Updated: 2025/02/16 21:34:41 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//check if it's end of string or double %
static int	ft_loop(int fd, char c, int	*count)
{
	if (!c)
	{
		write(fd, "%", 1);
		(*count)++;
		return (1);
	}
	if (c == '%')
	{
		write(fd, "%", 1);
		(*count)++;
	}
	return (0);
}

//check option after %
static int	ft_convert(int fd, char spe, va_list args)
{
	int	count;

	count = 0;
	if (spe == 'd')
		count = ft_iprints(fd, va_arg(args, int));
	else if (spe == 'c')
		count = ft_cprints(fd, va_arg(args, int));
	else if (spe == 'i')
		count = ft_iprints(fd, va_arg(args, int));
	else if (spe == 'x')
		count = ft_lowxprints(fd, va_arg(args, int));
	else if (spe == 'X')
		count = ft_upxprints(fd, va_arg(args, int));
	else if (spe == 'p')
		count = ft_pprints(fd, va_arg(args, void *));
	else if (spe == 'u')
		count = ft_uprints(fd, va_arg(args, unsigned int));
	else if (spe == 's')
		count = ft_sprints(fd, va_arg(args, char *));
	return (count);
}

int	ft_printf(int fd, const char *format, ...)
{
	size_t	i;
	int		count;
	va_list	args;

	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i] != '\0')
	{
		while (format[i] != '%' && format[i] != '\0')
		{
			ft_putchar_fd(format[i], fd);
			i++;
			count++;
		}
		if (format[i] == '%')
		{
			i++;
			if (ft_loop(fd, format[i], &count) == 1)
				break ;
			count += ft_convert(fd, format[i], args);
			i++;
		}
	}
	return (count);
}
