# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aheitz <aheitz@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/08 13:09:20 by aheitz            #+#    #+#              #
#    Updated: 2024/07/24 13:34:59 by aheitz           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell
CFLAGS		= -Wall -Wextra -Werror -lreadline

BINARIES	= ./binaries
UTILITIES	= ./utilities
SET			= ./set

SRCS		= ./main.c \
			./memory.c \
			./prompt.c \
			./termination.c \
			$(SET)/commands.c \
			$(SET)/tokens.c \
			$(UTILITIES)/append_character.c \
			$(UTILITIES)/append_string.c \
			$(UTILITIES)/get_length.c \
			$(UTILITIES)/is_alphanumeric.c \
			$(UTILITIES)/is_inside.c \
			$(UTILITIES)/is_space.c
OBJS		= $(SRCS:%.c=$(BINARIES)/%.o)

RED			= \033[31m
GREEN		= \033[32m
YELLOW		= \033[33m
BLUE		= \033[34m
MAGENTA		= \033[35m
CYAN		= \033[36m
RESET		= \033[0m

all: $(NAME)
	@echo "⭐ $(YELLOW)The minishell project is ready to launch!$(RESET)"

$(NAME): $(OBJS)
	@echo -n "↪️  Compiling the executable $(CYAN)$(NAME)$(RESET): "
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -lreadline
	@echo "$(GREEN)done!$(RESET)"

$(BINARIES)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo -n "➡️  Compilation of the file $(BLUE)$<$(RESET): "
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GREEN)done!$(RESET)"

clean:
	@echo -n "🗑 $(RED)Cleaning up$(RESET) binaries: "
	@$(RM) -r $(BINARIES)
	@echo "$(GREEN)done!$(RESET)"

fclean: clean
	@echo -n "🗑 $(RED)Deleting$(RESET) the executable $(CYAN)$(NAME)$(RESET): "
	@$(RM) $(NAME)
	@echo "$(GREEN)done!$(RESET)"

re: fclean all
	@echo "🧱 $(MAGENTA)Recompilation$(RESET) completed!"

execute: re
	@echo "🚀 Launch of recompiled $(CYAN)$(NAME)$(RESET)!"
	@./minishell

clear: fclean
	@clear

.PHONY: all clean fclean re