CC			= cc
NAME		= minishell
SRCS		= src/minishell.c
OBJS		= $(SRCS:.c=.o)
HEAD		= includes/minishell.h
CFLAGS		= -Wall -Werror -Wextra 
# -Wunreachable-code
LIBFT_DIR	= libft
LIBFT		= $(LIBFT_DIR)/libft.a

all:	$(NAME)

$(NAME): $(OBJS) $(HEAD) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline

$(LIBFT):
	@make -C $(LIBFT_DIR)

clean:
	@rm -f $(OBJS)
	@make clean -C $(LIBFT_DIR)

fclean:	clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

re:		fclean all

.PHONY: all clean fclean re bonus