```
/* -------------------------------------------------------
   The grammar symbols
   ------------------------------------------------------- */
%token  WORD

/* The following are the operators (see XBD Operator)
   containing more than one character. */

%token  AND_IF    OR_IF
/*      '&&'      '||'      */

%token  DLESS  DGREAT  
/*      '<<'   '>>'     */


/* -------------------------------------------------------
   The Grammar
   ------------------------------------------------------- */
%start program
%%
program          : linebreak
                 | linebreak complete_commands;
                 ;
complete_commands: list
                 | list seperator_op
                 | list seperator_op list
                 ;
list             : pipeline
                 | pipeline AND_IF list
                 | pipeline OR_IF list
                 ;
pipeline         : command
                 | command '|' pipeline
                 ;
command          : simple_command
                 | compound_command
                 | compound_command redirect_list
				 ;
simple_command   : cmd_prefix cmd_word cmd_suffix
                 | cmd_prefix cmd_word
                 | cmd_prefix
                 | cmd_name cmd_suffix
                 | cmd_name
                 ;
compound_command : subshell
                 ;
redirect_list    : io_redirect
                 | io_redirect redirect_list
                 ;
subshell         : '(' list ')'
                 ;
cmd_name         : WORD                   /* Apply rule 7a */
                 ;
cmd_word         : WORD                   /* Apply rule 7b */
                 ;
cmd_prefix       : io_redirect
                 | io_redirect cmd_prefix // left recursion
                 ;
cmd_suffix       : io_redirect
                 | io_redirect cmd_suffix // left recursion
                 | WORD
                 | WORD cmd_suffix // left recursion
                 ;
io_redirect      : io_file
                 | io_here
                 ;
io_file          : '<'       filename
                 | '>'       filename
                 | DGREAT    filename
                 ;
filename         : WORD                      /* Apply rule 2 */
                 ;
io_here          : DLESS     here_end
                 ;
here_end         : WORD                      /* Apply rule 3 */
                 ;
seperator_op     : '&'                       /* Not supported */
                 | ';'
                 ;
linebreak        : 'newline'
                 ;
```
