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
CFLAGS = -Wall -Werror -Wextra -g
# CFLAGS += -fsanitize=address
IFLAGS := -I incl/
LFLAGS := -L$(LIBFT_DIR) -lft
RFLAGS := -lreadline
#########################################
#			FILES PATH					#
#########################################
INC_PATH = ./incl/minishell.h

#########################################
#			SOURCES	FILES				#
#########################################
SRCS = main.c 							\
	00_lexer/tokenize.c					\
	00_lexer/specify_token.c			\
	00_lexer/grammar.c 					\
	01_expander/00_expand_token.c   	\
	01_expander/01_retrieve_value.c     \
	01_expander/02_identify_var.c      	\
	01_expander/03_replace_var.c		\
	01_expander/04_handle_quotes.c 		\
	01_expander/05_remove_quotes.c 		\
	01_expander/06_tokenize_var.c 		\
	04_exec/get_path.c 					\
	05_utils/amsterdam.c				\
	05_utils/brazil.c					\
	05_utils/exit_whisperer.c			\
	05_utils/init_struct.c				\
	05_utils/token_list_functions.c		\

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
