#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

int	main(int ac, char **av)
{
	int			fd;
	char		*line;
	static int	i = 1;

	if (ac != 2)
		return (1);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
	{
		fprintf(stderr, "error: open failed\n");
		return (1);
	}
	while (get_next_line(fd, &line) > 0)
	{
		printf("%d - %s\n", i, line);
		i++;
		free (line);
	}
}
