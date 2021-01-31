NAME= libftprintf.a

SRC_PATH= src
SRC_NAME=	apply_signs.c					fetch_by_sizem.c \
			apply_hash.c					apply_width.c \
			ft_putonbr.c					save_precision.c \
			ft_printf.c						ft_putunbr.c \
			save_width.c					apply_precision.c \
			build_result.c					ft_putxnbr.c \
			apply_quote.c					ft_putdnbr.c \
			save_flags.c					main_original.c\
			ft_putfnbr.c 					ft_putc_and_s.c \
			set_color.c						ft_putxstr.c\
			float_bigint_add_sub_comp.c		float_all_bigint_functions.c \
			float_bigint_initial_tools.c	float_construction_functions.c \
			float_bigint_add_sub_comp.c		float_helper_functions_unnecessary.c \
			float_bigint_initial_tools.c	float_main_functions.c \
			float_bigint_shift_functs.c		float_mini_dragon4.c \
			float_scientific_construction.c	float_mini_dragon4_2.c \
			old_macros_functions.c			ft_dprintf.c \
			old_macors_functions_2.c 

HDR_PATH= headers
HDR_NAME= float_bigint.h	ft_printf.h

OBJ_PATH= obj
OBJ_NAME= $(SRC_NAME:.c=.o)

OBJ= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))
SRC= $(addprefix $(SRC_PATH)/,$(SRC_NAME))
HDR= $(addprefix $(HDR_PATH)/,$(HDR_NAME))


# **************************************************************************** #

COMP= clang
CFLAGES= -Wall -Wextra -Werror

# **************************************************************************** #
# to-do we should change this !!!!
LIB_OBJ_PATH= libft/obj/*.o

LIB_PATH= libft
LIB= libft.a

LD_FLAGS= -L$(LIB_PATH)
LD_LIBS= -l$(patsubst lib%.a,%, $(LIB))

HDR_FLAGS= $(HDR_PATH)

# **************************************************************************** #

all: lib $(NAME)

$(NAME): $(LIB_PATH)/$(LIB) $(OBJ)
	@ar rc $(NAME) $(OBJ) $(LIB_OBJ_PATH)
	@ranlib $(NAME)
	@echo "\033[1;34m>>\033[0m ft_printf: \033[1;32m Library compilled.\033[0m"

lib:
	@make -sC libft

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HDR) | $(OBJ_PATH)
	@$(COMP) $(CFLAGES) -I $(HDR_FLAGS) -o $@ -c $<

$(OBJ_PATH):
	@mkdir $@

clean:
	@rm -fr $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@make -C libft clean
	@echo "\033[1;34m>>\033[0m $(NAME): \033[1;33m Library object files deleted.\033[0m"

fclean: 
	@rm -fr $(OBJ)
	@rmdir $(OBJ_PATH) 2> /dev/null || true
	@echo "\033[1;34m>>\033[0m $(NAME): \033[1;33m Library object files deleted.\033[0m"
	@rm -fr $(NAME)
	@make -C libft fclean
	@echo "\033[0;34m>>\033[0m $(NAME): \033[0;31m Library deleted.\033[0m"


re: fclean all
