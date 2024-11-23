/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:07:05 by jim               #+#    #+#             */
/*   Updated: 2024/11/23 15:14:19 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void	print_error(char *str)
{
	perror(str);
}

char	*deletion(char *str,char *filter)
{
	int	i;
	int	j;
	int	len;
	int	k;

	i = 0;
	len = strlen(filter);
	while (str[i])
	{
		if (str[i] == filter[0])
		{
			j = 0;
			while (str[i + j] == filter[j] && filter[j] != '\0')
				j++;
			if (j == len)
			{
				k = i;
				while (k < i + len)
					str[k++] = '*';
			}
		}
		i++;
	}
	return (str);
}

int	main(int ac, char **av)
{
	char	*str;

	if (ac == 2)
	{
		str = (char *)malloc(sizeof(char) * BUFFER_SIZE);
		if (!str)
			return (print_error("Error: Memory allocation failed\n"), 1);
		if (!fgets(str, BUFFER_SIZE, stdin))
			return (print_error("Error: Read error\n"), 1);
		deletion(str, av[1]);
		if (fputs(str, stdout) == EOF)
			return (print_error("Error: Write error\n"), 1);
		free(str);
	}
	else
		return (fprintf(stderr, "Error: Incorrect number of arguments\n"), 1);
	return (0);
}
