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
