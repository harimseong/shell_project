# minishell

Minishell is simple shell program which has subset of bash's features. 

### installation
libreadline developer package is required to compile.
installing it with package manager like apt or brew is recommended.
##### Homebrew
`brew install readline`
##### Ubuntu
`apt install libreadline-dev`

### what it does
Some redirect operations(<, >, <<, >>), pipe(|), some quoting and parameter expansion($WORD), and some bulit-ins with a few or without options are implemented.
Further improvements in mind are to include wildcard, pipeline operators, parenthesis for subshell.

### experience
I tried to follow structure of POSIX shell rather than to do it from scratch, because referencing POSIX shell specification is good practice.
Thus writing codes was straightforward except there're some limits about external functions and the project.
the rule allows neither regular expression function nor parser generator like bison and yacc.  but some of C standard library functions and system calls.  
so I hand coded tokenizer and parser and my partner did same for built-ins.

### reference
I referenced [POSIX shell command language specification](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) to make tokenizer and studied about parser to understand parsing process and made [RDP](https://en.m.wikipedia.org/wiki/Recursive_descent_parser) parser.  
bash source code from https://ftp.gnu.org/ was helpful but not much because its old-style codes make it hard to read and understand.
dash source code from https://git.kernel.org/pub/scm/utils/dash/dash.git was better when understanding the shell because it's more readable than bash.
