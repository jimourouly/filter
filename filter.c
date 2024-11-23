/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jim <jim@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 15:07:05 by jim               #+#    #+#             */
/*   Updated: 2024/11/23 17:13:39 by jim              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#define BUFFER_SIZE 9999

void	print_error(char *str)
{
	if (errno == ENOMEM)
		fprintf(stderr, "%s: Out of memory\n", str);
	if (errno == EIO)
		fprintf(stderr, "%s: Input/output error\n", str);
	if (errno == EBADF)
		fprintf(stderr, "%s: Bad file descriptor\n", str);
	else
		fprintf(stderr, "%s: something broken\n", str);
}

char	*deletion(char *str, char *filter)
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

	if (ac != 2)
		return (fprintf(stderr, "Error: Incorrect number of arguments\n"),1);
	str = (char *)malloc(BUFFER_SIZE);
	// if (open(0, O_RDONLY) < 0)
	// 	printf("KC\n");
	if (!str)
	{
		errno = ENOMEM;
		print_error("Error: Memory allocation failed");
		return (1);
	}
	if (!fgets(str, BUFFER_SIZE, stdin)) // BUG fgets wait for something, i dont know why but well see later
	{
		printf("sdas\n");
		if (feof(stdin))
			print_error("Error: End of file reached unexpectedly");
		else
		{
			errno = EIO;
			print_error("Error: Read error");
		}
		free(str);
		exit(1);
	}
	deletion(str, av[1]);
	if (fputs(str, stdout) == EOF)
	{
		errno = EBADF;
		print_error("Error: Write error");
		free(str);
		exit(1);
	}
	free(str);
	return (0);
}
