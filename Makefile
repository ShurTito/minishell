#//= Colors =//#
BOLD	:= \033[1m
BLACK	:= \033[30;1m
RED		:= \033[31;1m
GREEN	:= \033[32;1m
YELLOW	:= \033[33;1m
BLUE	:= \033[34;1m
MAGENTA	:= \033[35;1m
CYAN	:= \033[36;1m
WHITE	:= \033[37;1m
RESET	:= \033[0m

NAME = minishell

#NAME_BONUS = pipex_bonus

CC = gcc

CFLAGS = -g -Wall -Werror -Wextra

LIBFT_PATH = ./libft

LIBFT = $(LIBFT_PATH)/libft.a

MINISHELL = minishell.a

INCLUDES = -I ./include -I /Users/anttorre/.brew/opt/readline/include

LIBRARIES = -L /Users/anttorre/.brew/opt/readline/lib -lreadline

#PIPEX_BONUS = pipex_bonus.a

LIB = ar rcs

SRCS =  src/main.c src/minishell_utils.c src/free_program.c src/init_struct.c \
		src/ft_split_mini.c src/minishell_utils_2.c src/builtins/builtins.c \
		src/builtins/env_utils.c src/builtins/export_utils.c src/builtins/export_utils_2.c \
		src/builtins/export_utils_3.c src/builtins/builtins_2.c src/builtins/cd_utils.c \
		src/minishell_utils_3.c src/parser.c src/free_program_2.c src/here_doc.c \
		src/error_messages.c src/parser_2.c src/parser_3.c src/executer.c src/lexer_copy.c \
		src/builtins/unset_utils.c src/parser_4.c src/signal.c src/builtins/env_utils_2.c \
		src/executer_2.c

OBJS = $(SRCS:.c=.o)

#SRCS_BONUS =

#OBJS_BONUS = $(SRCS_BONUS:.c=.o)

$(NAME) :	$(LIBFT) $(OBJS) 
			@echo "$(MAGENTA)$(BOLD)Compiling minishell...$(RESET)"
			@$(LIB) $(MINISHELL) $(OBJS)
			@$(CC) $(INCLUDES) $(LIBRARIES) $(CFLAGS) $(LIBFT) $(MINISHELL) -o $(NAME)
			@echo "$(CYAN)$(BOLD)Done$(RESET)"

$(OBJS):	src/%.o : src/%.c 
			@$(CC) $(INCLUDES) $(CFLAGS) -c $< -o $@

#$(NAME_BONUS): $(OBJS_BONUS) $(LIBFT)
#			@echo "$(YELLOW)$(BOLD)Compiling pipex bonus...$(RESET)"
#			@$(LIB) $(PIPEX_BONUS) $(OBJS_BONUS)
#			@$(CC) $(CFLAGS) $(PIPEX_BONUS) $(LIBFT) -o $(NAME_BONUS)
#			@echo "$(CYAN)$(BOLD)Done$(RESET)"

#$(OBJS_BONUS):	srcb/%.o : srcb/%.c
#			@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
			@make -s -C $(LIBFT_PATH)
			@make bonus -s -C $(LIBFT_PATH)

all : $(NAME)

bonus : $(NAME_BONUS)

clean:
			@echo "$(RED)$(BOLD)Cleaning objects from minishell...$(RESET)"
			@rm -f $(OBJS) $(OBJS_BONUS)
			@echo "$(GREEN)$(BOLD)Done.$(RESET)"
			@make clean -s -C $(LIBFT_PATH)

fclean:
			@echo "$(RED)$(BOLD)Cleaning all files from minishell...$(RESET)"
			@rm -f $(NAME) $(NAME_BONUS) $(OBJS) $(OBJS_BONUS) $(LIBFT) $(MINISHELL) $(PIPEX_BONUS)
			@echo "$(GREEN)$(BOLD)Done.$(RESET)"
			@make fclean -s -C $(LIBFT_PATH)

re : fclean all

mini : fclean all clean

.PHONY : all re fclean clean bonus mini
