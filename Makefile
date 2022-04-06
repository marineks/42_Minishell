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
SRCS = main.c 											\
	00_lexer/tokenize.c									\
	00_lexer/specify_token.c							\
	00_lexer/grammar.c 									\
	01_expander/00_expand_token.c   					\
	01_expander/01_retrieve_value.c     				\
	01_expander/02_identify_var.c      					\
	01_expander/03_replace_var.c						\
	01_expander/04_handle_quotes.c 						\
	01_expander/05_remove_quotes.c 						\
	01_expander/06_tokenize_var.c 						\
	02_parser/00_create_cmds.c							\
	02_parser/01_parse_word.c							\
	02_parser/02_fill_flags.c							\
	02_parser/03_parse_heredoc.c						\
	02_parser/04_parse_redir_in.c 						\
	02_parser/05_parse_redir_out.c 						\
	02_parser/06_parse_append.c 						\
	02_parser/07_parse_pipe.c 							\
	04_exec/get_path.c 									\
	05_utils/gnl/get_next_line.c						\
	05_utils/gnl/get_next_line_utils.c					\
	05_utils/lists_functions/cmd_list_functions.c		\
	05_utils/lists_functions/env_list_functions.c 		\
	05_utils/lists_functions/token_list_functions.c		\
	05_utils/amsterdam.c								\
	05_utils/brazil.c									\
	05_utils/exit_whisperer.c							\
	05_utils/init_struct.c								\

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
