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

make 
chmod 755 minishell
clear

# ----------------------------- #

function test()
{
    BASH_TEST=$(bash -c "$@")
    MINISHELL_TEST=$($@ | ./minishell | head -n 1 | cut -d ' ' -f 4-)

    DIFF=$(diff <(echo "$BASH_TEST") <(echo "$MINISHELL_TEST"))

    printf "  "$UNDERDYELLOW"Current test:$RESET $@\n\n"
    sleep 1
    printf "$BOLDGREEN -> Bash Output:$RESET $BASH_TEST\n"
    sleep 0.5
    printf "$BOLDRED -> Your Output:$RESET $MINISHELL_TEST$BOLDWHITE\n\n"
    sleep 0.5

    if [[ -z "$DIFF" ]]; then
        echo "    ❌❌❌"
    else
        echo "    ✅✅✅"
    fi
    
    printf "\n"
    sleep 1
}

# ------------------------------- #

printf "\n"
printf "$BOLDCYAN  -----------------------------------\n"
printf "$BOLDCYAN  |"
printf "$BOLDWHITE WELCOME TO THE MINISHELL TESTER"
printf "$BOLDCYAN |\n"
printf "$BOLDCYAN  -----------------------------------\n"
printf "$RESET\n"

sleep 0.5
printf "$BOLDMAGENTA   [loading tests]"
sleep 0.5
printf " ."
sleep 0.5
printf "."
sleep 0.5
printf ".\n\n"
sleep 0.5

# ----------- TESTER ----------- #

test 'echo ola'
test 'echo "ola"'
test 'echo ola"ola"ola'
test 'echo "ola'ola'ola"'

printf '    THE END\n\n'