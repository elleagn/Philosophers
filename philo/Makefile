# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gozon <gozon@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/27 13:33:00 by gozon             #+#    #+#              #
#    Updated: 2024/10/16 13:00:24 by gozon            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_DIR = srcs
SRC_FILES =	parsing.c structs.c main.c utils.c actions.c forks.c threads.c \
			utils2.c monitor.c
SRC = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJ_DIR = objects
SRC_DIR = srcs
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Symboles Unicode
CHECK_MARK = ✔

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -lpthread -o $(NAME)
	@echo "$(NAME) a été créé avec succès ($(CHECK_MARK))"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -Iincludes -c $< -o $@

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "Nettoyage réussi ($(CHECK_MARK))"

fclean:
	@rm -f $(NAME)
	@rm -rf $(OBJ_DIR)
	@echo "Nettoyage complet réussi ($(CHECK_MARK))"

re: fclean all

.PHONY: all clean fclean re
