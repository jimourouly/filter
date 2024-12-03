#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define BUFFER_SIZE 1024

void	handle_error(const char *message)
{
	perror(message);
	exit(1);
}

//ft_strcmp
int	ft_strcmp(const char *buffer, const char *search, size_t search_len)
{
	for (size_t i = 0; i < search_len; i++)
	{
		if (buffer[i] != search[i])
			return (0);
	}
	return 1;
}

int	main(int argc, char **argv)
{
	ssize_t	bytes_read;
	size_t	j;
	size_t	search_len;
	size_t	i;
	char	*buffer;
	char	*search;

	if (argc != 2 || strlen(argv[1]) == 0)
	{
		printf("Error: Invalid arguments\n");
		return 1;
	}
	search = argv[1];
	search_len = strlen(search);
	buffer = malloc(BUFFER_SIZE);
	if (!buffer)
		handle_error("malloc");
	while ((bytes_read = read(STDIN_FILENO, buffer, BUFFER_SIZE)) > 0)
	{
		i = 0;
		while (i < (size_t)bytes_read)
		{
			if (i + search_len <= (size_t)bytes_read && ft_strcmp(&buffer[i], search, search_len))
			{
				j = 0;
				while (j < search_len)
				{
					if (write(STDOUT_FILENO, "*", 1) == -1)
					{
						free(buffer);
						handle_error("write");
					}
					j++;
				}
				i += search_len;
			}
			else
			{
				if (write(STDOUT_FILENO, &buffer[i], 1) == -1)
				{
					free(buffer);
					handle_error("write");
				}
				i++;
			}
		}
	}
	if (bytes_read == -1)
	{
		free(buffer);
		handle_error("read");
	}
	free(buffer);
	return 0;
}
