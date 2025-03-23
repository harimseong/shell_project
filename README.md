# shell_project

This is a small shell supporting subset of [POSIX shell](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19) standard.

## Supported Features
- redirection operators (<, >, <<, >>)
- commandline pipe (|)
- quoting (', ")
- parameter expansion ($WORD) and environment variables management (export, env, unset)
- bulit-in commands (`cd`, `pwd`, `echo`, `exit`)
- conditional operators (&&, ||)


## Prerequisite
- libreadline developer package (>= 8.12) for terminal input
- `gettext` for configuration

Recommend using package manager like `apt` or `brew` to install the library.

#### macOS
`brew install readline gettext`

#### Ubuntu
`apt-get install libreadline-dev gettext`

## Configure and Build

Run `./configure.sh && make` to configure and build.

You may need to adjust library path manually if configure script does not work.


## Debug
Run `make debug` to build in debug mode. It will enable
- compiler options (debug symbol, sanitizer)
- parser output printing
- exit value


## Test
`test_script.sh` receives a file that has commands to be tested. There is one test case per line. Each test case will be executed in this shell and bash. stdout, exit value pair of both will be compared to decide correctness.


Summary will be printed on stdout and details will be stored in `test_log.txt`.
### Examples

#### test_case_bonus.txt
```
echo 'a'*
echo *$NOTHING
echo $NOTHING*
ls | cat -e && gcc -v || echo "$TERM"
```

#### stdout
```
#9   [OK] "echo 'a'*"
#10  [OK] "echo *$NOTHING"
#11  [OK] "echo $NOTHING*"
#12  [OK] "ls | cat -e && gcc -v || echo "$TERM""
```

#### test_log.txt
```
[ shell output ]
42

[ bash output ]
42

[ diff ]

shell exit status = 0
bash exit status = 0
```


## Notes
- Syntax rules for parser is defined as form of BNF in `bnf.md`.
- [Grammar reference](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_10)
- [Token recognition reference](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_03)
