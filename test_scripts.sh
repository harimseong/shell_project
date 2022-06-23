# $EXIT1 $EXIT2 $CMD
exit_log()
{
	echo "	TEST: $3\n" >> test_log.txt
	echo "$4\n" >> test_log.txt
	echo "[ minishell output ]" >> test_log.txt
	cat testdir/.result1 >> test_log.txt
	echo "" >> test_log.txt
	echo "[ bash output ]" >> test_log.txt
	cat testdir/.result2 >> test_log.txt
	echo "" >> test_log.txt
	echo "[ diff ]" >> test_log.txt
	diff testdir/.result1 testdir/.result2 | cat -e >> test_log.txt
	echo "" >> test_log.txt
	echo "minishell exit status = $1" >> test_log.txt
	echo "bash exit status = $2" >> test_log.txt
	echo "\n\n\n" >> test_log.txt
}

# $DIFF
remove_prefix()
{
	if echo $1 | grep "bash:" >/dev/null;
	then
		cp testdir/.result1 testdir/.temp1;
		cp testdir/.result2 testdir/.temp2;
		cat <testdir/.temp1 | sed 's/minishell: //' >testdir/.result1;
		cat <testdir/.temp2 | sed 's/bash: //' >testdir/.result2;
	fi
	if echo $1 | grep "line 0:" >/dev/null;
	then
		cp testdir/.result2 testdir/.temp2
		cat <testdir/.temp2 | sed 's/line 0: //' >testdir/.result2
	fi
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
	remove_prefix "$DIFF"
	DIFF=$(diff testdir/.result1 testdir/.result2)
	if [ $EXIT1 != $EXIT2 ] || [ "$DIFF" != "" ]
	then
		if cat testdir/.result2 | grep -f testdir/.result1 >/dev/null
		then
			MSG="[$YELLOW_QQ] $CMD"
		else
			MSG="[$RED_KO] $CMD"
		fi
		STATUS=1
	else
		MSG="[$GREEN_OK] $CMD"
		STATUS=0
	fi
	if [ $EXIT2 -eq 0 ]
	then
		STATUS_COLOR=${COLOR_GREEN}
	else
		STATUS_COLOR=${COLOR_RED}
	fi
	MSG=$(printf "${STATUS_COLOR}#%-3d${COLOR_END} $MSG\n" $TEST_NUMBER)
	echo $MSG
	exit_log $EXIT1 $EXIT2 $1 $MSG
	rm testdir/.result1 testdir/.result2
	TEST_NUMBER=$((TEST_NUMBER + 1))
	return $STATUS
}

# $TEST_FILE
test_start()
{
	if [ "$1" == "" ]
	then
		echo "invaild format. $> sh  test_scripts.sh  test_case";
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
		echo "\n\ttest log:\n\tcat test_log.txt | less"
	fi
}

COLOR_RED='\033[0;31m'
COLOR_GREEN='\033[0;32m'
COLOR_YELLOW='\033[0;33m'
COLOR_END='\033[0m'

RED_KO="${COLOR_RED}KO${COLOR_END}"
GREEN_OK="${COLOR_GREEN}OK${COLOR_END}"
YELLOW_QUOTE="${COLOR_YELLOW}\"${COLOR_END}"
YELLOW_QQ="${COLOR_YELLOW}??${COLOR_END}"

NEWLINE='
'
TEST_NUMBER=0
stat testdir > /dev/null
if [ $? -ne 0 ]
then
	echo "creating test directory"
	mkdir testdir
	if [ $? -ne 0 ]
	then
		echo "temporary directory creation failed"
		return 1
	fi
fi
rm -f test_log.txt
./minishell -c "pwd" > /dev/null && test_start $1 || echo "minishell executable is not found or wrong."
rm -f testdir/.temp1 testdir/.temp2
