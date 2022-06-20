# $EXIT1 $EXIT2 $CMD
exit_log()
{
	echo "	TEST: $3\n" >> test_log.txt
	echo "$4\n" >> test_log.txt
	echo "[ minishell output ]" >> test_log.txt
	cat -e testdir/.result1 >> test_log.txt
	echo "" >> test_log.txt
	echo "[ bash output ]" >> test_log.txt
	cat -e testdir/.result2 >> test_log.txt
	echo "" >> test_log.txt
	echo "[ diff ]" >> test_log.txt
	diff testdir/.result1 testdir/.result2 >> test_log.txt
	echo "" >> test_log.txt
	echo "minishell exit status = $1" >> test_log.txt
	echo "bash exit status = $2" >> test_log.txt
	echo "\n\n\n" >> test_log.txt
}

# $CMD  
test_func()
{
	CMD="$YELLOW_QUOTE$1$YELLOW_QUOTE"
	./minishell -c "$1" 2>> testdir/.result1 >>testdir/.result1 < /dev/null
	EXIT1=$?
	bash -c "$1" 2>> testdir/.result2 >>testdir/.result2 < /dev/null
	EXIT2=$?
	DIFF=$(diff testdir/.result1 testdir/.result2 | cat -e)
	if [ $EXIT1 != $EXIT2 ]
	then
		MSG="[$RED_KO] $CMD"
		STATUS=1
	elif [ "$DIFF" != "" ]
	then
		MSG="[$RED_KO] $CMD"
		STATUS=1
		if echo "$DIFF" | grep "bash" > /dev/null
		then
			MSG="$MSG    <- error message has \"bash\""
		fi
	else
		STATUS=0
		MSG="[$GREEN_OK] $CMD"
	fi
	echo "$MSG"
	exit_log $EXIT1 $EXIT2 $1 $MSG
	rm testdir/.result1 testdir/.result2
	return $STATUS
}

# $TEST_FILE
test_start()
{
	if [ "$1" == "" ]
	then
		echo "please specify test-file.";
		return 0
	fi
	cat $1 2> /dev/null 1> /dev/null
	if [ $? -ne 0 ]
	then
		echo "invalid test-file."
		return 0
	fi
	< $1 cat | while IFS=$NEWLINE; read test_line;
	do
		test_func $test_line;
		STATUS=$(($STATUS | $?))
	done
	if [ "$STATUS" != "0" ]
	then
		echo "if you want to look at test log, type\ncat test_log.txt | less"
	fi
}

rm -f test_log.txt
COLOR_RED='\033[0;31m'
COLOR_GREEN='\033[0;32m'
COLOR_YELLOW='\033[0;33m'
COLOR_END='\033[0m'

RED_KO="${COLOR_RED}KO${COLOR_END}"
GREEN_OK="${COLOR_GREEN}OK${COLOR_END}"
YELLOW_QUOTE="${COLOR_YELLOW}\"${COLOR_END}"

NEWLINE='
'
echo "Use this shell script at the root directory of minishell(where compiled executable created)"

./minishell -c "pwd" > /dev/null && test_start $1 || echo "minishell executable is not found or wrong."
