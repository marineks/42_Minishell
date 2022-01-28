#########################################
#				PROGRAMS				#
#########################################
NAME = minishell

#########################################
#				COMMANDS				#
#########################################
CC = clang
MKDIR =	mkdir -p
RM = rm -rf

#########################################
#			DIRECTORIES					#
#########################################
SRCS_DIR = srcs/
OBJ_DIR = objs/
LIBFT_DIR = libft

#########################################
#			FLAGS COMPILATION			#
#########################################
CFLAGS = -Wall -Werror -Wextra
IFLAGS := -I incl/
LFLAGS := -L$(LIBFT_DIR) -lft
RFLAGS := -lreadline
#########################################
#			FILES PATH					#
#########################################
INC_PATH = ./incl/exec.h

#########################################
#			SOURCES	FILES				#
#########################################
SRCS = main.c 							\
	exec/get_path.c 

SRC	= $(addprefix $(SRCS_DIR),$(SRCS))

#########################################
#            OBJECT FILES    	        #
#########################################
OBJS = $(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

#########################################
#				COLORS					#
#########################################
RED		:="\033[1;31m"
GREEN	:="\033[1;32m"
PURPLE	:="\033[1;35m"
CYAN	:="\033[1;36m"
EOC		:="\033[0;0m"

#########################################
#				RULES					#
#########################################
all:	${NAME}

${OBJ_DIR}%.o : ${SRCS_DIR}%.c
	@$(MKDIR) $(@D)
	$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $< 

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@echo $(CYAN) " - Compiling $@" $(RED)
	@$(CC) $(RFLAGS) $(CFLAGS) $(OBJS) $(LFLAGS) $(IFLAGS) -o $(NAME)  
	@echo $(GREEN) "[OK COMPILED]" $(EOC)

clean:
		@echo $(PURPLE) "[🧹Cleaning...🧹]" $(EOC)
		@${RM} ${OBJS}
		@${RM} ${OBJ_DIR} 
		@make --no-print-directory -C ${LIBFT_DIR} clean

fclean: clean
		@echo $(PURPLE) "[🧹FCleaning...🧹]" $(EOC)
		@${RM} ${NAME}
		@make --no-print-directory -C $(LIBFT_DIR) fclean

re: 	fclean all

.PHONY: all clean fclean re
