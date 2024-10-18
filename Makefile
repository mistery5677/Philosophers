.SILENT:
MAKEFLAGS += --no-print-directory

GREEN   		= \033[0;32m
TEAL    		= \033[1;36m
RESET 			= \033[0m 

NAME			=	philosophers

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror -gdwarf-4 #-fsanitize=thread

RM				=	rm -rf

INC_DIR			=	includes/

SRC_DIR			=	sources/

OBJ_DIR			=	objs/

#PROG_DIR		=	program/

#MATH_DIR		=	math/

#TYPES_DIR		=	t_types/

#LFT_PATH		=	$(addprefix $(LIBS_DIR), libft/)

SRC				=	$(addprefix $(SRC_DIR), philosophers.c) \

OBJ_DIRS		=	$(OBJ_DIR) $(addprefix $(OBJ_DIR), $(SRC_DIR)) \

OBJ				=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

$(NAME):			$(OBJ) | $(SRC) 
# Pc da escola					$(CC) $(CFLAGS) -lreadline $^ -o $@ -I $(INC_DIR) -L$(LFT_PATH) -lft
					$(CC) $(CFLAGS) $^ -o $@ -I $(INC_DIR)  -lreadline -lncurses
					printf '$(GREEN)$(NAME) compiled successfully!\n $(RESET)'

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c | $(OBJ_DIRS)
#					make dependencies
					printf "$(TEAL)Compiling $(NAME) objects... %-33.33s\n$(RESET)" $(notdir $@) 
					$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR) 

$(OBJ_DIRS):
					mkdir -p $@

all:				$(NAME)

#dependencies:
#					make -C $(LFT_PATH)

clean:
					if [ -d $(OBJ_DIR) ]; then $(RM) $(OBJ_DIR); fi
#					make clean -C $(LFT_PATH)
#					if [ -d $(DEBUG_DIR) ]; then $(RM) $(DEBUG_DIR); fi

fclean:				clean
					$(RM) $(NAME)
#					make fclean -C $(LFT_PATH)

re:					fclean all

val: $(NAME)
	make re 
	clear 
	valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-fds=yes ./$(NAME)

.PHONY:				all clean fclean re val

