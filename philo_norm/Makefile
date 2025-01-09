GREEN   		= \033[0;32m
TEAL    		= \033[1;36m
RESET 			= \033[0m 

NAME			=	philo

CC				=	cc

CFLAGS			=	-Wall -Wextra -Werror -gdwarf-4 #-fsanitize=thread

RM				=	rm -rf

INC_DIR			=	includes/

SRC_DIR			=	sources/

OBJ_DIR			=	objs/

SRC				=	$(addprefix $(SRC_DIR), philosophers.c errors.c inicialization.c philo_utils.c time_zone.c actions.c routine.c) \

OBJ_DIRS		=	$(OBJ_DIR) $(addprefix $(OBJ_DIR), $(SRC_DIR)) \

OBJ				=	$(SRC:$(SRC_DIR)%.c=$(OBJ_DIR)%.o)

$(NAME):			$(OBJ) | $(SRC) 
					$(CC) $(CFLAGS) $^ -o $@ -I $(INC_DIR)  -pthread
					printf '$(GREEN)$(NAME) compiled successfully!\n $(RESET)'

$(OBJ_DIR)%.o:		$(SRC_DIR)%.c | $(OBJ_DIRS)
					printf "$(TEAL)Compiling $(NAME) objects... %-33.33s\n$(RESET)" $(notdir $@) 
					$(CC) $(CFLAGS) -c $< -o $@ -I $(INC_DIR) 

$(OBJ_DIRS):
					mkdir -p $@

all:				$(NAME)

clean:
					if [ -d $(OBJ_DIR) ]; then $(RM) $(OBJ_DIR); fi

fclean:				clean
					$(RM) $(NAME)

re:					fclean all

.PHONY:				all clean fclean re val