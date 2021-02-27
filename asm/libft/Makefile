# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/27 09:37:59 by tbareich          #+#    #+#              #
#    Updated: 2021/02/27 09:38:05 by tbareich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

FTPRINTF = ft_printf

HEADER = headers/libft.h

GRAPH = graph/graph.h

HEADERS = $(HEADER) $(GRAPH)

OBJS = lib/bst_delete.o \
			lib/bst_deletenode.o \
			lib/bst_find.o \
			lib/bst_inorder.o \
			lib/bst_insert.o \
			lib/bst_max.o \
			lib/bst_min.o \
			lib/bst_modify_addr.o \
			lib/bst_newnode.o \
			lib/ft_atoi.o \
			lib/ft_bzero.o \
			lib/ft_delcontent.o \
			lib/ft_isalnum.o \
			lib/ft_isalpha.o \
			lib/ft_isascii.o \
			lib/ft_isdigit.o \
			lib/ft_isprint.o \
			lib/ft_itoa.o \
			lib/ft_lstadd.o \
			lib/ft_lstaddat.o \
			lib/ft_lstdel.o \
			lib/ft_lstdelat.o \
			lib/ft_lstdelone.o \
			lib/ft_lstiter.o \
			lib/ft_lstlen.o \
			lib/ft_lstmap.o \
			lib/ft_lstnew.o \
			lib/ft_lstpop.o \
			lib/ft_lstpush.o \
			lib/ft_lstshift.o \
			lib/ft_memalloc.o \
			lib/ft_memccpy.o \
			lib/ft_memchr.o \
			lib/ft_memcmp.o \
			lib/ft_memcpy.o \
			lib/ft_memrcpy.o \
			lib/ft_memdel.o \
			lib/ft_memmove.o \
			lib/ft_memset.o \
			lib/ft_putchar.o \
			lib/ft_putchar_fd.o \
			lib/ft_putendl.o \
			lib/ft_putendl_fd.o \
			lib/ft_putlst.o \
			lib/ft_putnbr.o \
			lib/ft_putnbr_fd.o \
			lib/ft_putstr.o \
			lib/ft_putstr_fd.o \
			lib/ft_strcat.o \
			lib/ft_strchr.o \
			lib/ft_strclr.o \
			lib/ft_strcmp.o \
			lib/ft_strcpy.o \
			lib/ft_strdel.o \
			lib/ft_strdup.o \
			lib/ft_strdup_free.o \
			lib/ft_strequ.o \
			lib/ft_striter.o \
			lib/ft_striteri.o \
			lib/ft_strjoin.o \
			lib/ft_strjoin_free.o \
			lib/ft_strlcat.o \
			lib/ft_strlen.o \
			lib/ft_strmap.o \
			lib/ft_strmapi.o \
			lib/ft_strncat.o \
			lib/ft_strncmp.o \
			lib/ft_strncpy.o \
			lib/ft_strnequ.o \
			lib/ft_strnew.o \
			lib/ft_strnstr.o \
			lib/ft_strrchr.o \
			lib/ft_strsplit.o \
			lib/ft_strstr.o \
			lib/ft_strsub.o \
			lib/ft_strtrim.o \
			lib/ft_tolower.o \
			lib/ft_toupper.o \
			lib/get_int_len.o \
			lib/ft_realloc.o \
			lib/get_next_line.o \
			lib/ft_strip.o \
			lib/ft_is_number.o \
			queue/dequeue.o \
			queue/enqueue.o \
			queue/init_queue.o \
			queue/free_queue.o \
			array_list/append.o \
			array_list/init_array_list.o \
			math/max.o \
			math/min.o \
			math/abs.o

GRAPH_OBJS = graph/add_edge.o \
			graph/create_graph.o \
			graph/print_graph.o \
			graph/delete_graph.o \

CC = gcc

CFLAGS = -Wall -Wextra -Werror -I./headers

# ****************
# **** COLORS ****
# ****************
GREEN = \033[32m
YELLOW = \033[33m
RED = \033[91m
BLUE = \033[96m
RESET = \033[0m
# ****************
# ****************

all: build $(NAME)

build: 
	@if [ ! -f $(NAME) ] ; then \
		echo "$(BLUE)→ $(YELLOW)Creating $(NAME) ...$(RESET)" ; \
	fi;

$(NAME): $(OBJS) $(GRAPH_OBJS) $(HEADER) $(GRAPH)
	@if [ ! -f $(NAME) ] ; then \
		echo "$(BLUE)→ $(GREEN)$(NAME) done $(RESET)" ; \
	fi;
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)
	@make -C ft_printf
	
$(OBJS) : %.o: %.c $(HEADER)
	@$(CC) -I$(HEADER) $(CFLAGS) -c -o $@ $<
	@if [[ -f $(NAME) ]] ; then \
		echo "$(BLUE)→ $(GREEN)$@ updated$(RESET)" ; \
	fi;

$(GRAPH_OBJS) : %.o: %.c $(GRAPH)
	@$(CC) -I$(GRAPH) $(CFLAGS) -c -o $@ $<
	@if [[ -f $(NAME) ]] ; then \
		echo "$(BLUE)→ $(GREEN)$@ updated$(RESET)" ; \
	fi;

clean:
	@make clean -C ft_printf
	@rm -f $(OBJS)
	@echo "$(BLUE)→ $(RED)$(NAME) clean$(RESET)"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(FTPRINTF)

re: fclean all

.PHONY: all clean fclean re build
