# /* ~~~~~~ SOURCES ~~~~~~ */
SRCS_DIR = srcs/
SRCS = main.c \
	exec/get_path.c \

SRC	= $(addprefix $(SRCS_DIR),$(SRCS))
OBJ_DIR = objs/
OBJS =	$(addprefix $(OBJ_DIR), $(SRCS:.c=.o))

# /* ~~~~~~~ INCLUDING LIBFT ~~~~~~~ */
LIBFT_DIR = libft
LIBFT_MAKE = Makefile
LIBFT_PATH = ${LIBFT_DIR}/libft.a

# /* ~~~~~~~ COMPILING INFO ~~~~~~~ */
CC = clang
CFLAGS = -Wall -Werror -Wextra -pthread -g #-MMD -g -fsanitize=thread
IFLAGS:= -I incl/
LFLAGS:= -L $(LIBFT_DIR) -lft

# /* ~~~~~~~ OTHER ~~~~~~~ */
NAME = minishell
MKDIR		=	mkdir -p
RM = rm -f

# /* ~~~~~~~ Colors ~~~~~~~ */
RED:="\033[1;31m"
GREEN:="\033[1;32m"
PURPLE:="\033[1;35m"
CYAN:="\033[1;36m"
EOC:="\033[0;0m"

all:	${NAME}

${OBJ_DIR}%.o : ${SRCS_DIR}%.c
	@$(MKDIR) $(@D)
	$(CC) $(CFLAGS) $(IFLAGS)  -o $@ -c $< 

$(NAME): $(OBJS)
	@make -C $(LIBFT_DIR)
	@echo $(CYAN) " - Compiling $@" $(RED)
	@$(CC) $(CFLAGS) $(OBJS) $(LFLAGS) $(IFLAGS) -o $(NAME)
	@echo $(GREEN) "[OK COMPILED]" $(EOC)

clean:
		@echo $(PURPLE) "[🧹Cleaning...🧹]" $(EOC)
		@${RM} ${OBJS}
		@${RM} -r ${OBJ_DIR} 
		@make -C ${LIBFT_DIR} -f ${LIBFT_MAKE} clean

fclean: clean
		@echo $(PURPLE) "[🧹FCleaning...🧹]" $(EOC)
		@${RM} ${OBJS} ${NAME} a.out
		@${RM} ${B_OBJS} ${BONUS} a.out

re: 	fclean all

.PHONY: all clean fclean re