# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mesafi <mesafi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/29 23:34:49 by mesafi            #+#    #+#              #
#    Updated: 2020/02/04 09:30:16 by mesafi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Usage:
# make			# compile all binary
# make clean	# remove all binaries and objects
# make fclean	# remove created library
# make re		# Get recompiled

# Standard variables
NAME		= visualizer.a
HEADER		= visualizer.h

OBJS		= visualizer.o \
				helpers/drawing.o \
				helpers/rectangle.o \
				helpers/renderBitmapString.o
			

CC			= gcc

CFLAGS		= -I . -Wno-deprecated

# Colors
BLACK		= \033[30m
RED			= \033[31m
GREEN		= \033[32m
YELLOW		= \033[93m
BLUE		= \033[34m
MAGENTA		= \033[35m
CYAN		= \033[36m
WHITE		= \033[37m
RESET		= \033[0m

# Start rules
all: build $(NAME)

build:
	@if [ ! -f $(NAME) ] ; then \
		echo "⇾ building $(NAME)..." ; \
	fi;

$(NAME): $(OBJS) $(HEADER)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@echo "⇾ $(NAME) $(GREEN)done ( ˆᴗˆ )$(RESET)"

%.o: %.c
	@$(CC) -c $(CFLAGS) $< -o $@
	@if [[ -f $(NAME) ]] ; then \
		echo "⇾ $@ $(GREEN)updated$(RESET)" ; \
	fi;

clean:
	@rm -f $(OBJS)
	@echo "⇾ $(NAME) $(RED)cleaned$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@echo "⇾ $(NAME) $(RED)deleted$(RESET)"

re: fclean all
