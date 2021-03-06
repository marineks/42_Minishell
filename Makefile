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
#CFLAGS += -fsanitize=address  -Wno-unused
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
	00_lexer/tokenize_utils.c 							\
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
	02_parser/02_00_fill_flags_echo.c					\
	02_parser/02_01_fill_flags_default.c 				\
	02_parser/03_parse_heredoc.c						\
	02_parser/04_parse_redir_in.c 						\
	02_parser/05_parse_redir_out.c 						\
	02_parser/06_parse_append.c 						\
	02_parser/07_parse_pipe.c 							\
	03_builtins/00_echo.c 								\
	03_builtins/01_cd.c 								\
	03_builtins/02_pwd.c 								\
	03_builtins/03_00_export.c 							\
	03_builtins/03_01_sort_export.c 					\
	03_builtins/03_02_export_utils.c 					\
	03_builtins/04_unset.c 								\
	03_builtins/05_env.c 								\
	03_builtins/06_exit.c 								\
	04_exec/exec_builtin.c								\
	04_exec/exec_processes.c							\
	04_exec/exec.c 										\
	05_utils/execve_functions/00_execve_infos.c			\
	05_utils/execve_functions/01_convert_env.c			\
	05_utils/execve_functions/02_get_path.c				\
	05_utils/execve_functions/03_create_cmd_array.c		\
	05_utils/lists_functions/cmd_list_free_functions.c	\
	05_utils/lists_functions/cmd_list_functions.c		\
	05_utils/lists_functions/env_list_functions.c 		\
	05_utils/lists_functions/token_list_functions.c		\
	05_utils/lists_functions/token_list_insert_funct.c	\
	05_utils/signals/sig_handlers.c 					\
	05_utils/signals/signals.c 							\
	05_utils/amsterdam.c								\
	05_utils/brazil.c									\
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
