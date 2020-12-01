# this is the empty template
NAME= corewar

SRC_PATH= src
SRC_NAME=	main_vm_parse.c			read_players.c	ft_read_champion.c \
			arena_initialization.c	op.c			logical_operators_and_jmp.c \
			operations_tools.c 		operations_fork_live.c	ft_operations_add.c	\
			ft_operations_ld.c		ft_any_player.c	ft_chek.c	\
			

HDR_PATH= includes
HDR_NAME= virtual_machine.h op.h

LIB_PATH= libft
LIB= libft.a

OBJ_PATH= .obj
OBJ_NAME= $(SRC_NAME:.c=.o)

SRC= $(addprefix $(SRC_PATH)/,$(SRC_NAME))
HDR= $(addprefix $(HDR_PATH)/,$(HDR_NAME))
OBJ= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

# **************************************************************************** #

COMP=	gcc
CFLAGES= -Wall -Wextra -Werror

LD_FLAGS= -L$(LIB_PATH)
LD_LIBS= -l$(patsubst lib%.a,%, $(LIB))

HDR_FLAGS= $(HDR_PATH)

# **************************************************************************** #
.PHONY: all lib clean fclean re 

all: lib $(NAME) 


$(NAME): $(LIB_PATH)/$(LIB) $(OBJ)
	@$(COMP) $(OBJ) $(LD_FLAGS) $(LD_LIBS) -o $@
	@ echo "\033[1;34m>>\033[0m $(NAME)\033[1;32m binary is ready.\033[0m"

lib:
	@make -sC $(LIB_PATH)

$(LIB_PATH)/$(LIB): lib

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HDR) | $(OBJ_PATH)
	@$(COMP) $(CFLAGS) -I $(HDR_FLAGS) -o $@ -c $<

$(OBJ_PATH):
	@mkdir $@

clean:
	@rm -fr $(OBJ)
	@rm -fr $(OBJ_PATH) 2> /dev/null || true
	@make -C $(LIB_PATH) clean
	@echo "\033[1;34m>>\033[0m $(NAME)\033[1;33m object files deleted.\033[0m" 

fclean:
	@make -C $(LIB_PATH) fclean
	@rm -fr $(OBJ)
	@rm -fr $(OBJ_PATH) 2> /dev/null || true
	@echo "\033[1;34m>>\033[0m $(NAME)\033[1;33m object files deleted.\033[0m" 
	@rm -fr $(NAME)
	@echo "\033[0;34m>>\033[0m $(NAME)\033[0;31m binary deleted.\033[0m" 

re: fclean all
