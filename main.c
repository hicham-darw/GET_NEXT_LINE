#include "get_next_line.h"
#include <stdio.h>


int	main(int ac, char **av)
{
	int		fd;
	char	*line;

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
		static int i = 1;
		printf("%d - %s\n", i++, line);
		free(line);
	}
}
