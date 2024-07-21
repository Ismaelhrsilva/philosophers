# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ishenriq <ishenriq@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/12/11 20:08:54 by ishenriq          #+#    #+#              #
#    Updated: 2024/07/20 23:20:00 by ishenriq         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
#CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g3 -O3 -Wunused-variable
#CFLAGS	:=  -Ofast -g3 -O0 -MD -MP
CFLAGS	:=  -g3
#CC	:= cc
BUILD_DIR = objects/
MKDIR  := mkdir -p

HEADERS	:= -I ./include

LDFLAGS	:= $(HEADERS)

SRC_DIR := ./src/
SRCS := principal/main.c \
	principal/routines.c \
	utils/ft_atoi.c \
	utils/ft_putendl_fd.c \

SRC := $(addprefix $(SRC_DIR)/, $(SRCS))

OBJS	+=  $(SRC:%.c=$(BUILD_DIR)%.o)

define create_dir
	$(MKDIR) $(dir $@)
endef

all: $(NAME)

$(BUILD_DIR)%.o: %.c
	$(call create_dir)
	@$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS) && printf "Compiling: $(notdir $<)"

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(LDFLAGS) -o $(NAME) -lpthread

clean:
	@rm -rf $(BUILD_DIR)

fclean: clean
	@rm -rf $(NAME)

re: clean all

norm:
	norminette -R CheckForbiddenSourceHeader $(SRC) ./include

.PHONY: all, clean, fclean, re
.DEFAULT_GOAL := all
