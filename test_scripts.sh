CMD="echo 123";
echo "minishell"
./minishell -c "$CMD"
echo "minishell exit status = $?"
echo "bash"
bash -c "$CMD"
echo "bash exit status = $?"
