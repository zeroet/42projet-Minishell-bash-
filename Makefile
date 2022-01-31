
# =============================================================================
# Color Variables
# =============================================================================

BLACK		= 	"\033[0;30m"
GRAY		= 	"\033[1;30m"
RED			=	"\033[0;31m"
GREEN		=	"\033[0;32m"
YELLOW		=	"\033[1;33m"
PURPLE		=	"\033[0;35m"
CYAN		=	"\033[0;36m"
WHITE		=	"\033[1;37m"
EOC			=	"\033[0;0m"
LINE_CLEAR	=	"\x1b[1A\x1b[M"

# =============================================================================
# Command Variables
# =============================================================================

NAME = minishell

CC = gcc
CFLAGS = -Wall -Wextra -Werror

INCS = -I./srcs -I./libft 
INCLIB = -Llibft -lft

LIBFT_D = ./libft
LIBFT_A = ./libft/libft.a

RL = readline
RLL = User/seyun/homebrew/opt/readline/lib
RLI = User/seyun/homebrew/opt/readline/include

FILES = main.c \

SRCS = $(addprefix srcs/, $(FILES))
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME): $(OBJS)
	make -C $(LIBFT_D)
	$(CC) $(CFLAGS) $(INCS) -o $(NAME) $(OBJS) $(INCLIB) -l$(RL) -I $(RLL) -L $(RLI)
	
clean:
	make -C $(LIBFT_D) clean
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(LIBFT_A)

re: fclean all

.PHONY: all clean fclean re
