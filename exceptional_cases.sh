# put some content in abc
# ls works normally
# $? = 0

< abc | ls
# abc doesn't change

> abc | ls
# abc becomes empty


# parse error
echo "abc" > text.txt | ls -a |||| ls -l

# equal sign
touch a=b && echo "123" > a=b
cat a=b
