# Program name
NAME        = minishell

# Compiler
CC          = cc

# Compiling flags
CFLAGS      = -Wall -Wextra -Werror

# Includes
INCLUDES    = includes/minishell.h

# Directories
SRC_DIR     = src
OBJ_DIR     = obj
LIBFT_DIR   = libft

# Libft and source files
LIBFT       = $(LIBFT_DIR)/libft.a
SRCS        = 	$(SRC_DIR)/minishell.c \
				$(SRC_DIR)/redirections.c \
				$(SRC_DIR)/signals.c \
				$(SRC_DIR)/cleanup.c \
				$(SRC_DIR)/parsing.c \
				$(SRC_DIR)/split.c \
				$(SRC_DIR)/split_cont.c \
				$(SRC_DIR)/token_count.c \
				$(SRC_DIR)/fill_tokens.c \
				$(SRC_DIR)/path.c \
				$(SRC_DIR)/path_cont.c \
				$(SRC_DIR)/execute.c \
				$(SRC_DIR)/builtins.c \
				$(SRC_DIR)/export.c \
				$(SRC_DIR)/builtins_exec.c \
				$(SRC_DIR)/final_cmd.c \
				$(SRC_DIR)/exit.c \
				$(SRC_DIR)/export_utils.c \
				$(SRC_DIR)/unset.c \
				$(SRC_DIR)/execute_utils.c \
				$(SRC_DIR)/heredoc.c \
				$(SRC_DIR)/expand_dollar.c \
				$(SRC_DIR)/expand_quotes_exit_code.c \
				$(SRC_DIR)/input_error.c \
				$(SRC_DIR)/redirections_utils.c \
				$(SRC_DIR)/cd.c \
				$(SRC_DIR)/shlvl.c \
				$(SRC_DIR)/copy_redir_names.c \


# Objects
OBJS        = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(NAME)
	@echo "$(NAME) built successfully!"

# Build the project
$(NAME): $(OBJS) $(INCLUDES) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lreadline

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Compile libft
$(LIBFT):
	@make -C $(LIBFT_DIR)

# Clean the project
clean:
	@rm -f $(OBJS)
	@make clean -C $(LIBFT_DIR)
	@rmdir $(OBJ_DIR) 2>/dev/null || true

# Clean project and object files
fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

# Clean and rebuild project rule
re: fclean all

.PHONY: all clean fclean re bonus
