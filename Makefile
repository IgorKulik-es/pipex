NAME = pipex
TNAME = test
LIBRARY = lib_pipex.a

SRCS = pipex_main.c forker.c pipex_utils.c parse_cmd.c ft_split.c basic_utils.c \
initializer.c error_handler.c
TSRCS = test1.c

HEADER = pipex.h

OBJS = $(SRCS:.c=.o)
TOBJS = $(TSRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

all: $(NAME)
test: $(TNAME)

$(TNAME) : $(TOBJS)
	cc -o $(TNAME) $(TOBJS)

$(NAME): $(LIBRARY)
	cc -o $(NAME) $(LIBRARY) -g

$(LIBRARY): $(OBJS)
	ar -rcs -o $(LIBRARY) $(OBJS) $(HEADER)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -g

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(LIBRARY)

re: fclean all
