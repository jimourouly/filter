#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if ((unsigned char) s1[i] != (unsigned char) s2[i])
		{
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		}
		i++;
	}
	return (0);
}

void print_error(char *msg)
{
	perror(msg);
}

int main(int ac, char **av)
{
	if (ac != 2)
		return 1;

	char *s = av[1];
	int s_len = strlen(s);

	if (s_len == 0)
		return 1;

	char *buffer = malloc(BUFFER_SIZE);
	if (!buffer)
	{
		print_error("Error : malloc");
		return 1;
	}

	int read_b;
	while((read_b = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0){
		int i = 0;
		while(i < read_b)
		{
			if (i + s_len <= read_b && ft_strncmp(&buffer[i], s, s_len) ==0){
				int j =0;
				while(j < s_len)
				{
					printf("*");
					j++;
				}
				i += s_len;
			}
			else
			{
				printf("%c", buffer[i]);
				i++;
			}
		}

	}
	if (read_b == -1)
	{
		free(buffer);
		print_error("Error: read");
		return 1;
	}
	free(buffer);
	return 0;
}
