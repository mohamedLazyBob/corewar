# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tbareich <tbareich@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/24 14:13:12 by tbareich          #+#    #+#              #
#    Updated: 2021/02/26 15:12:28 by tbareich         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME = ../libftprintf.a

FT_PRINTF = libftprintf.a

HEADER = ../headers/ft_printf.h 

LIBFTOBJS = ../lib/bst_delete.o \
			../lib/bst_deletenode.o \
			../lib/bst_find.o \
			../lib/bst_inorder.o \
			../lib/bst_insert.o \
			../lib/bst_max.o \
			../lib/bst_min.o \
			../lib/bst_modify_addr.o \
			../lib/bst_newnode.o \
			../lib/ft_atoi.o \
			../lib/ft_bzero.o \
			../lib/ft_delcontent.o \
			../lib/ft_isalnum.o \
			../lib/ft_isalpha.o \
			../lib/ft_isascii.o \
			../lib/ft_isdigit.o \
			../lib/ft_isprint.o \
			../lib/ft_itoa.o \
			../lib/ft_lstadd.o \
			../lib/ft_lstaddat.o \
			../lib/ft_lstdel.o \
			../lib/ft_lstdelat.o \
			../lib/ft_lstdelone.o \
			../lib/ft_lstiter.o \
			../lib/ft_lstlen.o \
			../lib/ft_lstmap.o \
			../lib/ft_lstnew.o \
			../lib/ft_lstpop.o \
			../lib/ft_lstpush.o \
			../lib/ft_lstshift.o \
			../lib/ft_memalloc.o \
			../lib/ft_memccpy.o \
			../lib/ft_memchr.o \
			../lib/ft_memcmp.o \
			../lib/ft_memcpy.o \
			../lib/ft_memdel.o \
			../lib/ft_memmove.o \
			../lib/ft_memset.o \
			../lib/ft_putchar.o \
			../lib/ft_putchar_fd.o \
			../lib/ft_putendl.o \
			../lib/ft_putendl_fd.o \
			../lib/ft_putlst.o \
			../lib/ft_putnbr.o \
			../lib/ft_putnbr_fd.o \
			../lib/ft_putstr.o \
			../lib/ft_putstr_fd.o \
			../lib/ft_realloc.o \
			../lib/ft_strcat.o \
			../lib/ft_strchr.o \
			../lib/ft_strclr.o \
			../lib/ft_strcmp.o \
			../lib/ft_strcpy.o \
			../lib/ft_strdel.o \
			../lib/ft_strdup.o \
			../lib/ft_strdup_free.o \
			../lib/ft_strequ.o \
			../lib/ft_striter.o \
			../lib/ft_striteri.o \
			../lib/ft_strjoin.o \
			../lib/ft_strjoin_free.o \
			../lib/ft_strlcat.o \
			../lib/ft_strlen.o \
			../lib/ft_strmap.o \
			../lib/ft_strmapi.o \
			../lib/ft_strncat.o \
			../lib/ft_strncmp.o \
			../lib/ft_strncpy.o \
			../lib/ft_strnequ.o \
			../lib/ft_strnew.o \
			../lib/ft_strnstr.o \
			../lib/ft_strrchr.o \
			../lib/ft_strsplit.o \
			../lib/ft_strstr.o \
			../lib/ft_strsub.o \
			../lib/ft_strtrim.o \
			../lib/ft_tolower.o \
			../lib/ft_toupper.o \
			../lib/get_int_len.o \
			../lib/get_next_line.o\
			../math/abs.o

OBJS = ft_printf.o \
			specifiers/ft_specifier_char.o \
			specifiers/ft_specifier_double.o \
			specifiers/ft_specifier_hex.o \
			specifiers/ft_specifier_int.o \
			specifiers/ft_specifier_octal.o \
			specifiers/ft_specifier_pointer.o \
			specifiers/ft_specifier_string.o \
			specifiers/ft_specifier_binary.o \
			specifiers/ft_specifier_uint.o \
			parsers/ft_parse_flags.o \
			parsers/ft_parse_format.o \
			parsers/ft_parse_length.o \
			parsers/ft_parse_parameter.o \
			parsers/ft_parse_precision.o \
			parsers/ft_parse_specifier.o \
			parsers/ft_parse_width.o \
			helpers/ft_snumtoa.o \
			helpers/ft_unumtoa.o \
			helpers/pad_spaces.o \
			helpers/pad_zeros.o \
			helpers/ft_percent.o \
			helpers/ft_multiplication.o \
			helpers/ft_fast_power.o \
			helpers/ft_addition.o \
			helpers/ft_round.o \
			helpers/print_double.o \
			helpers/ft_fraction.o \
			helpers/ft_whole.o \
			helpers/omit_zero.o \
			helpers/is_flag.o \
			helpers/error_handler.o \
			helpers/separated_number.o

CC = gcc

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

CFLAGS = -Wall -Werror -Wextra -I../headers/

all: build $(NAME)

build: 
	@if [ ! -f $(NAME) ] ; then \
		echo "$(BLUE)→ $(YELLOW)Creating $(FT_PRINTF) ...$(RESET)" ; \
	fi;

$(NAME): $(OBJS) $(HEADER)
	@if [ ! -f $(NAME) ] ; then \
		echo "$(BLUE)→ $(GREEN)$(FT_PRINTF) done $(RESET)" ; \
	fi;
	@ar rc $(NAME) $(OBJS) $(LIBFTOBJS)
	@ranlib $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@if [[ $? && -f $(NAME) ]] ; then \
		echo "$(BLUE)→ $(GREEN)$@ updated$(RESET)" ; \
	fi;

clean:
	@rm -rf $(OBJS)
	@echo "$(BLUE)→ $(RED)$(FT_PRINTF) clean$(RESET)"

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re build
