# MINISHELL TESTER

# -------- COLORS ----------#

    RESET="\033[0m"
    BLACK="\033[30m"
    RED="\033[31m"
    GREEN="\033[32m"
    YELLOW="\033[33m"
    BLUE="\033[34m"
    MAGENTA="\033[35m"
    CYAN="\033[36m"
    WHITE="\033[37m"

# ---------- BOLD ----------- #

    BOLDBLACK="\033[1m\033[30m"
    BOLDRED="\033[1m\033[31m"
    BOLDGREEN="\033[1m\033[32m"
    BOLDYELLOW="\033[1m\033[33m"
    BOLDBLUE="\033[1m\033[34m"
    BOLDMAGENTA="\033[1m\033[35m"
    BOLDCYAN="\033[1m\033[36m"
    BOLDWHITE="\033[1m\033[37m"

# -------- UNDERLINE --------- #

    UNDERDBLACK="\033[4m\033[30m"
    UNDERDRED="\033[4m\033[31m"
    UNDERDGREEN="\033[4m\033[32m"
    UNDERDYELLOW="\033[4m\033[33m"
    UNDERDBLUE="\033[4m\033[34m"
    UNDERDMAGENTA="\033[4m\033[35m"
    UNDERDCYAN="\033[4m\033[36m"
    UNDERDWHITE="\033[4m\033[37m"

# ----------------------------- #

make re
clear

# ----------------------------- #

function test()
{
    BASH_TEST=$(bash -c "$@")
	MINISHELL_TEST=$(echo "$@" | ./minishell | head -n 1 | cut -d ' ' -f 4-)

    printf ""$BOLDYELLOW$UNDERDYELLOW"Current test:$RESET$BOLDWHITE [$@]\n\n"
    sleep 0.5
    printf "$BOLDGREEN-> Bash output:$RESET $BASH_TEST\n"
	sleep 0.5
    printf "$BOLDRED-> Your output:$RESET $MINISHELL_TEST $BOLDWHITE\n\n"
    sleep 0.5

    DIFF=$(diff <(echo $BASH_TEST) <(echo $MINISHELL_TEST))

    if [ -z "$DIFF" ]; then
    	printf "$BOLDGREEN---- [SUCCESS] ----$RESET\n\n\n"
	else
    	printf "$BOLDRED---- [FAILED] ----$RESET\n\n\n"
	fi

    sleep 0.5
}

# ------------------------------- #

printf "\n"
printf "$BOLDCYAN  -----------------------------------\n"
printf "$BOLDCYAN  |$BOLDWHITE WELCOME TO THE MINISHELL TESTER $BOLDCYAN|\n"
printf "$BOLDCYAN  -----------------------------------\n"
printf "$RESET\n"

sleep 0.5
printf "$BOLDMAGENTA  [loading tests]"
sleep 0.5
printf " ."
sleep 0.5
printf "."
sleep 0.5
printf ".$RESET\n\n"
sleep 0.5

# ----------- ECHO TESTER ----------- #

printf "$BOLDCYAN-------------"
printf "$BOLDCYAN [$BOLDWHITE"ECHO"$BOLDCYAN] "
printf "$BOLDCYAN-------------\n"
printf "$RESET\n"

test 'echo ola'
test 'echo "ola"'
test 'echo ola" boas "pessoal'
test 'echo -n ola'
test 'echo -nnnnnnnnnnnnnnnnnnnnn ola'

# ----------- EXECVE TESTER ----------- #

printf "$BOLDCYAN-------------"
printf "$BOLDCYAN [$BOLDWHITE"EXECVE"$BOLDCYAN] "
printf "$BOLDCYAN-------------\n"
printf "$RESET\n"

test 'date'
test 'pwd'

printf "$BOLDMAGENTA  -----------\n"
printf "$BOLDMAGENTA  |$BOLDWHITE THE END $BOLDMAGENTA|\n"
printf "$BOLDMAGENTA  -----------\n"
printf "$RESET\n"

make fclean