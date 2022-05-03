# COLORS
RESET="\e[39m"
BLACK="\e[30m"
BOLD_RED="\e[1;31m"
BOLD_GREEN="\e[1;32m"
BOLD_YELLOW="\e[1;33m"
YELLOW="\e[33m"
BLUE="\e[34m"
MAGENTA="\e[35m"
CYAN="\e[36m"
WHITE="\e[97m"
PINK="\e[38;5;225m"
LIGHT_BLUE="\e[38;5;45m"
ORANGE="\e[1;38;5;214m"

chmod 755 minishell

if [ -f "output.txt" ] ; then
    rm "output.txt"
fi

printf "$LIGHT_BLUE ### Minishell tester ### $RESET"
echo
echo

# Faire une fonction qui exec la ligne dans bash et dans minishell
# Comparer les outputs, les mettre dans un output file
# et print le OK/ KO sur le terminal
test() {
	MINISHELL=$(echo $@ | ./minishell 2>&-)
	EXPECTED=$(echo $@ | bash --posix 2>&-)
	MINISHELL_EXIT=$?
	BASH_EXIT=$?
	if [ "$MINISHELL" = "$EXPECTED" ] && [ "$MINISHELL_EXIT" = "$BASH_EXIT" ]
	then 
		printf "$BOLD_GREEN OK $RESET"
	else
		if [ "$MINISHELL" != "$EXPECTED" ] && [ "$MINISHELL_EXIT" = "$BASH_EXIT" ]
		then
			printf "$PINK KO $RESET"
		elif [ "$MINISHELL" = "$EXPECTED" ] && [ "$MINISHELL_EXIT" != "$BASH_EXIT" ]
		then
			printf "$BOLD_YELLOW EXIT_KO $RESET"
			touch output.txt
			echo "Test : $@" >> output.txt
			echo "Expected exit code : $BASH_EXIT" " Yours : $MINISHELL_EXIT" >> output.txt
			echo >> output.txt
		else
			printf "$BOLD_RED KO $RESET"
		fi
	fi
}

# ---- SYNTAX ERRORS ---- 
printf " $PURPLE Syntax errors \n $RESET "
test '|'
test '<'
test '>'
test '<<'
test '>>'
test 'echo >>> newtest.txt'
test 'echo <<< newtest.txt'
test '||'
echo 

# # ---- BUILTIN TESTS ----
# ECHO (+ a bit of QUOTES and ENV EXPANSION)
printf " $PINK Echo \n $RESET "
test 'echo '
test 'echo -n'
test 'echo-n'
test 'echo -nn'
test 'echo $'
test 'echo $ $'
test 'echo $?'
test 'echo $?$'
test 'echo $HOME'
test 'echo $9HOME'
test 'echo $IDONTEXIST'
test 'echo $USER$HOME'
test 'echo "$"""'
test 'echo '$''''
test 'echo $"HOME"'
test 'echo $''HOME'
test 'echo $""HOME'
test 'echo "$HO"ME'
test 'echo '$HO'ME'
test 'echo "'$HO''ME'" '
test 'echo coucou$HOME"$'USER'"'
test 'echo $_2P$2P$P2$PP2'
test 'echo salut $myu "dssdsi$HOLA user $USER"'
test 'echo $=HOME'
test 'echo $'USER' '
test 'echo $HOME "test with many         many       spaces"'
test 'echo' '"     "' ' |'
test 'echo "buenos dias    "$"USER $HOME teeest ||| "'
test 'echo "buenos dias    '$'USER $HOME teeest ||| "'
echo

# CD
printf " $LIGHT_BLUE CD \n $RESET "
test 'cd | pwd'
test 'cd .. | pwd'
test 'cd / | pwd'
test 'cd ~ | pwd'
test 'cd ~/Documents | pwd'
test 'cd non_existent_path'
test 'cd too many arguments'
test 'cd ../../../../../../../../../../../../../ | pwd'
test 'cd ..///..'
test 'cd ../\//..'
echo

# PWD
printf " $YELLOW PWD \n $RESET "
test 'pwd'
test 'pwd something'
test 'pwdtest'
echo

# EXPORT (+ a bit of ENV EXPANSION)
printf " $BLUE EXPORT \n $RESET "
test 'export'
test 'export a | export'
test 'export 1test'
test 'export 1foo=bar =bar = '
test 'export test=ok | env | sort | grep test'
test 'export test2=foo test3=bar test4=baz | env | sort | grep test'
test 'export test5=ok word test6=ok | env | sort | grep test'
test 'export test7=ok =ko test8=done| env | sort | grep test'
test 'export test9=bonjour test9=hello | env | sort | grep test'
test 'export test10=hola test11=$test10 | env | sort | grep test'
test 'export test12=$? | env | sort | grep test'
test 'export hey="ls "-l"a" | $hey'
test 'export he=ls ho=-la | $he $ho'
echo

# UNSET
printf " $CYAN UNSET \n $RESET "
test 'unset'
test 'unset NON_EXISTENT_VAR | env'
test 'unset USER | env'
test 'unset $USER'
test 'unset $?'
test 'unset HOME USER PWD OLDPWD'
test 'unset USER NON_EXISTENT_VAR PWD'
test 'unset NON_EXISTENT_VAR NON_EXISTENT_VAR'
test 'unset =foo'
test 'unset 42'
echo

# ENV
printf " $WHITE ENV \n $RESET "
test 'env'
test 'env something'
echo

# EXIT
printf " $PINK EXIT \n $RESET "
test 'exit'
test 'exit $?'
test 'exit 0'
test 'exit 257'
test 'exit -42'
test 'exit 9999999999999999999999999999999999999999999999'
test 'exit -2147483648'
test 'exit bye'
test 'exit 0 1 2 3'
test 'exit 255 test 489'
test '                  exit'
test '"exit"'
test 'ex'i't'
test 'export test=1 | exit $test'
echo

# ---- PIPE TESTS ----
printf " $PURPLE PIPE TESTS \n $RESET "
# EMPTY COMMAND
test ''

# ONE COMMAND
test 'ls -la'

# SEVERAL COMMANDS (multipipe)
test 'env | sort | grep pwd > result.txt'
test 'ls | ls | ls | ls | ls'

# CHECK THAT THERE IS ONE PROCESS PER COMMAND
test 'time sleep 3 | sleep 3 | sleep 3'
echo

# ---- REDIR TESTS ----
# REDIR_IN

# REDIR_OUT
test ''

# APPEND

# HEREDOC
echo

rm result.txt