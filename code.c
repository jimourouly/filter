#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>git cl

#define BUFFER_SIZE 1024

int ft_strncmp(char *s1, char *s2, size_t len)
{
	size_t i =0;
	while((s1[i] ||s2[i]) && i < len)
	{
		if (s1[i] != s2[i])
			return(s1[i]-s2[i]);
		i++;
	}
	return 0;
}

void printf_error(char *msg)
{
	perror(msg);
}

int main (int ac, char **av)
{
	if (ac != 2)
		return 1;
	char *s = av [1];
	int len = strlen(s);
	if (len == 0)
		return 0;
	char *buffer = malloc(BUFFER_SIZE);
	if (!buffer)
	{
		printf_error("Error: malloc");
		return 1;
	}
	int read_b;
	while((read_b = read(STDIN_FILENO, buffer, BUFFER_SIZE)) >0)
	{
		int i = 0;
		while(i < read_b)
		{
			if (i + len <= read_b && ft_strncmp(&buffer[i], s, len) ==0)
			{
				int j = 0;
				while (j < len)
				{
					printf("*");
					j++;
				}
				i += len;
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
		printf_error("Errror: read");
		return 1;
	}
	free(buffer);
	return 0;
}
