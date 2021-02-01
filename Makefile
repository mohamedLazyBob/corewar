NAME= corewar

SRC_PATH= src
SRC_NAME=	main_vm_parse.c				read_players.c	ft_read_champion.c \
			arena_initialization.c		op.c \
			ft_any_player.c				ft_chek.c	\
			init_process_arena.c	  	play_battle.c \
			mz_mode_verbos.c		 	ft_print_error.c\
			ft_kill.c					mz_tools.c		mz_print_op.c	\
			ft_pusher.c					battle_start.c	ft_free.c \
			op/add.c \
			op/aff.c \
			op/and.c \
			op/fork.c \
			op/ld.c  \
			op/ldi.c \
			op/lfork.c \
			op/live.c \
			op/lld.c \
			op/lldi.c \
			op/or.c \
			op/st.c \
			op/sti.c \
			op/sub.c \
			op/xor.c \
			op/zjmp.c \
			op/tools_01.c \
			op/tools_02.c \
			op/tools_03.c

HDR_PATH= includes
HDR_NAME= virtual_machine.h op.h

LIB_PATH= ft_printf
LIB= libftprintf.a

VISUALIZER_PATH= visualizer
VISUALIZER= visualizer.a

OBJ_PATH= .obj
OBJ_NAME= $(SRC_NAME:.c=.o)

SRC= $(addprefix $(SRC_PATH)/,$(SRC_NAME))
HDR= $(addprefix $(HDR_PATH)/,$(HDR_NAME))
OBJ= $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

# **************************************************************************** #

COMP= clang
CFLAGES= -Wall -Wextra -Werror

LD_FLAGS= -L$(LIB_PATH)
LD_LIBS= -l$(patsubst lib%.a,%, $(LIB))

HDR_FLAGS= $(HDR_PATH)


# **************************************************************************** #
.PHONY: all lib clean fclean re 

all: lib $(NAME) 

$(NAME): $(LIB_PATH)/$(LIB) $(VISUALIZER_PATH)/$(VISUALIZER) $(OBJ)
	@$(COMP) $(OBJ) $(LD_FLAGS) $(LD_LIBS) $(VISUALIZER_PATH)/$(VISUALIZER) -framework GLUT -framework OpenGL -o $@
	@ echo "\033[1;34m>>\033[0m $(NAME): \033[1;32m binary is ready.\033[0m"

lib:
	@make -sC ft_printf
	@make -C $(VISUALIZER_PATH)

#$(LIB_PATH)/$(LIB): lib
#	@echo "***"

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c $(HDR) | $(OBJ_PATH)
	@$(COMP) $(CFLAGES) -I $(HDR_FLAGS) -o $@ -c $<

$(OBJ_PATH):
	@mkdir $@
	@mkdir $@/op

clean:
	@rm -fr $(OBJ)
	@rm -fr $(OBJ_PATH) 2> /dev/null || true
	@make -C $(LIB_PATH) clean
	@make clean -C $(VISUALIZER_PATH)
	@echo "\033[1;34m>>\033[0m $(NAME): \033[1;33m object files deleted.\033[0m" 

fclean:
	@make -C $(LIB_PATH) fclean
	@make fclean -C $(VISUALIZER_PATH)
	@rm -fr $(OBJ)
	@rm -fr $(OBJ_PATH) 2> /dev/null || true
	@echo "\033[1;34m>>\033[0m $(NAME): \033[1;33m object files deleted.\033[0m" 
	@rm -fr $(NAME)
	@echo "\033[0;34m>>\033[0m $(NAME): \033[0;31m binary deleted.\033[0m" 

re: fclean all
