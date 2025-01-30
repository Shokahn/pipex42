# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stdevis <stdevis@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/27 19:08:27 by stdevis           #+#    #+#              #
#    Updated: 2025/01/30 16:32:01 by stdevis          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[36m
RESET = \033[0m
RED = \033[31m

BOLD = \033[1m
UNDERLINE = \033[4m
ITALIC = \033[3m

NAME = pipex

SRC_FILES =  pipex utils


OBJ_DIR = obj/
SRC_DIR = src/
CFLAGS = -Wall -Wextra -Werror
FSANITIZE = -fsanitize=address -g3
MAKE = make --no-print-directory

LIBFT_DIR = libft/libft_original
PRINTF_DIR = libft/Printf
GNL_DIR = libft/GNL


LIBFT = $(LIBFT_DIR)/libft.a
PRINTF = $(PRINTF_DIR)/libftprintf.a
GNL = $(GNL_DIR)/GNL.a

OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))


all: $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	@mkdir -p $(OBJ_DIR)
	@echo "📦 $(ITALIC)$(YELLOW)Compiling $< $(RESET)"
	@cc $(CFLAGS) -c $< -o $@

$(NAME): $(LIBFT) $(PRINTF) $(OBJ)
	@echo ""
	@echo "		🚀 $(BOLD)$(YELLOW)Linking $(NAME)...$(RESET)"
	@cc $(CFLAGS) $(OBJ) -o $(NAME) -L $(LIBFT_DIR) -L $(PRINTF_DIR) -lft -lftprintf
	@touch infile
	@echo ""
	@echo "	🎉 $(BOLD)$(GREEN)SUCCESS: $(NAME) has been created$(RESET) ✅ "
	@echo ""

$(LIBFT):
	@echo ""
	@echo "		⚙ $(UNDERLINE)$(BOLD)Building libft$(RESET) ⚙"
	@echo ""
	@$(MAKE) -C $(LIBFT_DIR)
	
$(GNL):
	@echo ""
	@echo "		⚙ $(UNDERLINE)$(BOLD)Building GNL$(RESET) ⚙"
	@echo ""
	@$(MAKE) -C $(GNL_DIR)

$(PRINTF):
	@echo ""
	@echo "		⚙ $(UNDERLINE)$(BOLD)Building printf$(RESET) ⚙"
	@echo ""
	@$(MAKE) -C $(PRINTF_DIR)
	@echo ""
	@echo "		⚙ $(UNDERLINE)$(BOLD)Building $(NAME) $(RESET) ⚙"
	@echo ""


run : $(NAME)
	@echo ""
	@touch $(FILE)
	@echo "		Running push_swap with arguments: $(ITALIC)$(ARGS)$(RESET) in ⏩ $(BOLD)$(FILE)$(RESET)"
	@./$(NAME) $(ARGS) > $(FILE)
	@echo ""
		
clean:
	@echo ""
	@echo "		🧹 $(BOLD)$(BLUE)Cleaning object files 🧹$(RESET)"
	@echo ""
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(PRINTF_DIR) clean
	@$(MAKE) -C $(GNL_DIR) clean
	@rm -rf $(OBJ_DIR)
	@rm -rf outfile
	@rm -rf infile
	@echo "💾 $(YELLOW)Cleaning $(NAME) object files$(RESET)"
	@echo "   ↪️ $(GREEN)$(NAME) object files have been deleted$(RESET)"
	@echo ""
	@echo "	👉 $(BOLD)$(GREEN)Object files have been deleted$(RESET) ❎"


fclean: clean
	@echo ""
	@echo "		🧹 $(BOLD)$(BLUE)Cleaning everything 🧹$(RESET)"
	@echo ""
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(PRINTF_DIR) fclean
	@$(MAKE) -C $(GNL_DIR) fclean
	@echo "💾 $(YELLOW)Cleaning $(NAME)$(RESET)"
	@echo "   ↪️ $(GREEN)$(NAME) has been deleted$(RESET)"
	@rm -f $(NAME)
	@echo ""
	@echo "	👉 $(BOLD)$(GREEN)Everything has been cleaned$(RESET) ❎"

re: fclean $(NAME)

.PHONY: all clean fclean re