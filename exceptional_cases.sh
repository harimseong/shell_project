# put some content in abc
< abc | ls
# abc doesn't change
> abc | ls
# abc becomes empty
# $? == 0 && ls works normally on both cases


# parse error
echo "abc" > text.txt | ls -a |||| ls -l


# equal sign
touch a=b && echo "123" > a=b
cat a=b


# $
export TEST=cat
$TEST -e
export TEST2='<'
$TEST $TEST2 some_file


# ""
"echo" abc


cat" -e" 	#fail
cat " -e"	#success 
export TEST1="cat"
export TEST2=" -e"
$TEST1$TEST2		#success(two token)
echo $TEST1$TEST2	#one token

c"a"t -e 	#success
c"a"t$TEST2 #success

""			#"\0" token
"" a		#"\0" "a" tokens
""a			#"a" token

| ls -al
ls -al | #

$			$# $ token
echo $		$# $
$$			# number


# Ctrl-C running process and check its status


ls < 'nonexist file' | ls -a	# only 'ls -a' outputs
