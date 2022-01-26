#ifndef EXEC_H
#define EXEC_H

#include <unistd.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "../libft/libft.h"

enum output {
	SUCCESS = 0,
	FAILURE = -1,
	ERROR = 2,
	TRUE = 3,
	FALSE = 4
};

# define RESET "\033[0m"
# define BLACK "\033[0;30m"
# define RED "\033[0;31m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"
# define BLUE "\033[0;34m"
# define PURPLE "\033[0;35m"
# define CYAN "\033[0;36m"
# define WHITE "\033[0;37m"

#endif
