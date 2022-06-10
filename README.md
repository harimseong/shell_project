# minishell

minishell is a 42-cursus C project to make quite simple shell program.

### installation
installed readline library developer package is required to compile.  
installing it with package manager like apt or brew is recommended.
##### Homebrew
`brew install readline`
##### Ubuntu
`apt install libreadline-dev`

### what it does
the goal of this project is making a simple shell as stated on project specification, so this is not an actual shell programming language, but a simple prompting program mimicking small part of bash shell.  
most simple redirect operations, pipe, part of quoting and parameter expansion, and some bulit-ins with a few or without options are mandatory part. it can be extended to include wildcard, pipeline, parenthesis for subshell, etc..

### experience
the biggest challenge was making parser because available tools are limited by a rule.  
the rule allows neither regular expression function nor parser generator like bison and yacc, but some of C standard library functions and system calls.  
so I hand coded tokenizer and parser and my partner did same for built-ins.

### reference
I referenced [POSIX shell command language specification](https://pubs.opengroup.org/onlinepubs/9699919799/utilities/V3_chap02.html) for tokenizer and studied parser lectures to understand parsing process and made parser called [RDP](https://en.m.wikipedia.org/wiki/Recursive_descent_parser).  
bash source code from https://ftp.gnu.org/ was helpful but not much. 
