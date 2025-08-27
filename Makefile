CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c, %.o, $(SRCS))
LIB = get_next_line.a

$(LIB): $(OBJS)
	ar rcs $(LIB) $(OBJS)
%.c:%.o
	$(CC) $(CFLAGS) -c $< -o $@ -I.
all: $(LIB)

clean:
	rm -f $(OBJS) *.o
	make -C libft/ clean
fclean: clean
	rm -rf $(LIB) test_gnl
re: fclean all

.PHONY: all clean fclean re
