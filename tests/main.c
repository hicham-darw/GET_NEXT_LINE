#include <fcntl.h>    // for open()
#include <stdio.h>    // for printf(), perror()
#include <stdlib.h>   // for free()
#include <unistd.h>   // for close()

// Your get_next_line prototype (adjust if different)
int get_next_line(int fd, char **line);

int main(int argc, char **argv)
{
    int fd;
    char *line;
    int ret;

    if (argc != 2)
    {
        printf("Usage: %s <filename>\n", argv[0]);
        return (1);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file");
        return (1);
    }

    while ((ret = get_next_line(fd, &line)) > 0)
    {
        printf("Line: %s\n", line);
        free(line);
    }
    if (ret == 0) // EOF reached
    {
        printf("Line: %s\n", line); // print last line
        free(line);
    }
    else if (ret == -1)
    {
        printf("Error while reading\n");
    }

    close(fd);
    return (0);
}

