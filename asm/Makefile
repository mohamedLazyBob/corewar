# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/01/20 13:51:29 by mesafi            #+#    #+#              #
#    Updated: 2021/02/26 07:22:39 by tbareich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Usage:
# make			# compile all binary
# make clean	# remove all binaries and objects
# make fclean	# remove created library
# make re		# Get recompiled


# TODO: Delete this line
SHELL:=/bin/zsh

# Standard variables
NAME		= asm
PREBUILD			= prebuild
LIBFT		= libft/libft.a
FT_PRINTF	= libft/libftprintf.a
HEADERS		= headers/asm.h \
				headers/op.h
OBJSDIR	=	obj
SRCSDIR	=	src
HANDLERSDIR	= handlers

ASM_SRC	=	asm.c
ASM_OBJ =	$(OBJSDIR)/asm.o 

SRC		=	reader.c \
			parser.c \
			error.c \
			usage.c \
			compiler.c \
			spliter.c \
			player_spliter.c \
			checker.c \
			op.c \
			create_exe.c \
			player_reader.c

HANDLERS= op_memo_handlers.c \
			is_valid_label_handler.c \
			get_op_index_handler.c \
			get_label_handler.c \
			is_valid_register_handler.c \
			op_type_handler.c \
			check_file_name_handler.c \
			construct_op_handler.c \
			free_tab_handler.c \
			get_arg_type_code_handler.c


SRC_OBJS		= $(patsubst %.c, $(OBJSDIR)/$(SRCSDIR)/%.o, $(SRC))
HANDLERS_OBJS	= $(patsubst %.c, $(OBJSDIR)/$(SRCSDIR)/$(HANDLERSDIR)/%.o, $(HANDLERS))


CC			= clang
# TODO: change flags
# CFLAGS		= -I./headers/ -I./libft/headers
CFLAGS		= -Wall -Wextra -Werror -I./headers/ -I./libft/headers

# Colors
GREEN = \033[32m
YELLOW = \033[33m
RED = \033[91m
BLUE = \033[96m
RESET = \033[0m

# Start rules
all:  $(NAME)

$(NAME): $(PREBUILD) $(SRC_OBJS) $(HANDLERS_OBJS) $(ASM_OBJ) $(HEADERS)
	@if [ ! -f $(NAME) ] ; then \
		echo "$(BLUE)→ $(GREEN)$(NAME) $(GREEN)done$(RESET)"; \
	fi;
	@$(CC) $(CFLAGS) $(ASM_OBJ) $(SRC_OBJS) $(HANDLERS_OBJS) $(LIBFT) $(FT_PRINTF) -o $(NAME)

$(SRC_OBJS): $(OBJSDIR)/$(SRCSDIR)/%.o : $(SRCSDIR)/%.c
	@$(CC) -c $(CFLAGS) $< -o $@
	@if [[ -f $(NAME) ]] ; then \
		echo "$(BLUE)→ $(GREEN)$@ $(GREEN)updated$(RESET)" ; \
	fi;
	
$(HANDLERS_OBJS): $(OBJSDIR)/$(SRCSDIR)/$(HANDLERSDIR)/%.o : $(SRCSDIR)/$(HANDLERSDIR)/%.c
	@$(CC) -c $(CFLAGS) $< -o $@
	@if [[ -f $(NAME) ]] ; then \
		echo "$(BLUE)→ $(GREEN)$@ $(GREEN)updated$(RESET)" ; \
	fi;

$(ASM_OBJ): $(OBJSDIR)/%.o : %.c
	@$(CC) -c $(CFLAGS) $< -o $@
	@if [[ -f $(NAME) ]] ; then \
		echo "$(BLUE)→ $(GREEN)$@ $(GREEN)updated$(RESET)" ; \
	fi;

$(PREBUILD):
	@make -s -C libft
	@mkdir -p $(OBJSDIR)
	@mkdir -p $(OBJSDIR)/$(SRCSDIR)
	@mkdir -p $(OBJSDIR)/$(SRCSDIR)
	@mkdir -p $(OBJSDIR)/$(SRCSDIR)/$(HANDLERSDIR)
	@if [ ! -f $(NAME) ] ; then \
		echo "$(BLUE)→ $(YELLOW)Creating $(NAME)...$(RESET)" ; \
	fi;

clean:
	@make -s clean -C libft
	@rm -rf $(OBJSDIR)
	@echo "$(BLUE)→ $(RED)$(NAME) $(RED)clean$(RESET)"
	
fclean: clean
	@rm -f $(FT_PRINTF)
	@rm -f $(LIBFT)
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
