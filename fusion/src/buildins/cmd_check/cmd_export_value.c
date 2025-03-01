/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_export_value.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tbahin <tbahin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 18:02:37 by tbahin            #+#    #+#             */
/*   Updated: 2025/03/01 17:26:20 by tbahin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/buildins.h"

int	ft_space(char c)
{
	if (c == 32 || (c >= 9 && c <= 13))
	{
		printf("error export value");
		exit(0);
	}
	return (0);
}

void	ft_check_space(char *value)
{
	int	i;

	i = 0;
	while (value[i])
	{
		 if (value[i] == '=')
		{
			i++;
			while (value[i])
			{
				ft_space(value[i]);
				i++;
			}
			break ;
		}
		i++;
	}
}

void	ft_export_value(char *value)
{
	// if (value [0] != '\'' && value[0] != '\"');
	// else
	// {
	ft_check_space(value);
	// 	if (value[0] == '\'')
			
	// 	if (value[0] == '\"')
		
	// }

}