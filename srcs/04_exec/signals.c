#include "minishell.h"
#include <signal.h>

/*
		MEMO : 
		SIG INT = CTRL C
		SIG QUIT = CTRL \

		EOF = CTRL D (PAS UN SIGNAL)
*/
#define _XOPEN_SOURCE 700 // Necessary for sigaction (incomplete type error)
#define _POSIX_C_SOURCE 199309L

void	signal_handler(int signal)
{
	if (signal == SIGINT)
	{
		// réafficher le prompt
	}
	else if (signal == SIGQUIT)
	{
		// ignorer ce signal au lieu de core dump
		
		// sauf si process en cours type sleep 5
		// ou cat | cat, auquel cas on doit print qqch
	}
}

int	catch_signals()
{
	struct sigaction	sa;

	sa.sa_handler = signal_handler;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}