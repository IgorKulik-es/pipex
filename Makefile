NAME = pipex
BONUSNAME = pipex_bonus
#TNAME = test
LIBRARY = lib_pipex.a
BLIBRARY = lib_pipex_bonus.a

SRCS = pipex_main.c forker.c parse_cmd.c ft_split.c basic_utils.c \
initializer.c error_handler.c parse_files.c
BONUSSRCS = pipex_main_bonus.c initializer_bonus.c forker_bonus.c parse_cmd_bonus.c \
ft_split.c basic_utils.c pipex_utils.c parse_files_bonus.c error_handler_bonus.c
#TSRCS = test1.c

HEADER = pipex.h
BONUSHEADER = pipex_bonus.h

OBJS = $(SRCS:.c=.o)
BONUSOBJS = $(BONUSSRCS:.c=.o)
#TOBJS = $(TSRCS:.c=.o)

CFLAGS = -Wall -Wextra -Werror

RM = rm -f

all: $(NAME)
test: $(TNAME)
bonus: $(BONUSNAME)

#$(TNAME) : $(TOBJS)
#	cc -o $(TNAME) $(TOBJS)

$(BONUSNAME): $(BLIBRARY)
	cc -o $(NAME) $(BLIBRARY) -g

$(NAME): $(LIBRARY)
	cc -o $(NAME) $(LIBRARY) -g

$(LIBRARY): $(OBJS)
	ar -rcs -o $(LIBRARY) $(OBJS) $(HEADER)

$(BLIBRARY): $(BONUSOBJS)
	ar -rcs -o $(BLIBRARY) $(BONUSOBJS) $(BONUSHEADER)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -g

clean:
	$(RM) $(OBJS) $(BONUSOBJS)

fclean: clean
	$(RM) $(NAME) $(LIBRARY) $(BLIBRARY)

re: fclean all
