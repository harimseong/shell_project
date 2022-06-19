echo "minishell output and exit status test against bash"
rm -f test_log.txt
COLOR_RED='\033[0;31m'
COLOR_GREEN='\033[0;32m'
COLOR_END='\033[0m'


# $EXIT1 $EXIT2 $CMD
exit_log()
{
	echo "	TEST: $3" >> test_log.txt
	echo "[ minishell output ]" >> test_log.txt
	cat -e testdir/result1 >> test_log.txt
	echo "" >> test_log.txt
	echo "[ bash output ]" >> test_log.txt
	cat -e testdir/result2 >> test_log.txt
	echo "" >> test_log.txt
	echo "[ diff ]" >> test_log.txt
	diff testdir/result1 testdir/result2 >> test_log.txt
	echo "" >> test_log.txt
	echo "" >> test_log.txt
}

# $CMD  
test_func()
{
	echo "TEST: $1"
	./minishell -c "$1" 2>> testdir/result1 >>testdir/result1
	EXIT1=$?
	bash -c "$1" 2>> testdir/result2 >>testdir/result2
	EXIT2=$?
	DIFF=$(diff testdir/result1 testdir/result2 | cat -e)
	if [ $EXIT1 != $EXIT2 ]
	then
	echo "minishell exit status = $1"
	echo "bash exit status = $2"
	exit_log $EXIT1 $EXIT2 $1
	printf "${COLOR_RED}KO${COLOR_END}"
	elif [ "$DIFF" != "" ]
	then
	exit_log $EXIT1 $EXIT2 $1
	printf "${COLOR_RED}KO${COLOR_END}"
	else
	printf "${COLOR_GREEN}OK${COLOR_END}"
	fi
	echo ""
	rm testdir/result1 testdir/result2
}

CMD="echo 123";
test_func $CMD
CMD="echo ";
test_func "$CMD"
CMD="echo \"$USER\"";
test_func "$CMD"
CMD="echo \"$USER\"";
test_func "$CMD"
CMD="echo '$USER'";
test_func "$CMD"
CMD="echo $USER>out1|ls -a&&cat -e<out1";
test_func "$CMD"
CMD="echo \"\"\"$?\"\"\"";
test_func "$CMD"
CMD="cd src";
test_func "$CMD"
CMD="pwd";
test_func "$CMD"
CMD="cd ..";
test_func "$CMD"
CMD="pwd";
test_func "$CMD"
CMD="/bin/ls -a";
test_func "$CMD"
CMD="cat asd"
test_func "$CMD"
CMD="cat asd|||"
test_func "$CMD"
CMD="cat asd || ls"
test_func "$CMD"
CMD="cat asd && ls"
test_func "$CMD"
CMD="echo *"
test_func "$CMD"
CMD="ls | cat -e && gcc -v || ls -a"
test_func "$CMD"
CMD="ls | cat -e && gcc -v && ls -a"
test_func "$CMD"


