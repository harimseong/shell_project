# minishell

minishell is a 42-cursus C project for quite simplified shell programming language.

installed readline library developer package is required to compile.
installing it with package manager like apt or brew is recommended.

the goal of this project is mimicking bash shell as stated on project specification, so this minishell is not an actual shell programming language, but a simple prompting program mimicking small part of bash shell.
redirection, pipe, simplified quoting and word expansion, and a few bulit-ins are mandatory part. it can be extended to include wildcard, pipeline, parenthesis, etc..

the biggest challenge was making parser because available tools are limited by a rule.
the rule includes neither regular expression function nor bison and yacc, just some of C standard library functions and system calls.
so I hand coded tokenizer and parser and my partner did same for built-ins.

I referenced POSIX shell command language specification for tokenizer and learned recursive descent parser to understand parsing process and make parser.
bash source code from https://ftp.gnu.org/ was helpful but not much. 
