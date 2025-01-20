# shell_project

This is a small shell providing features from subset of [POSIX shell](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19).

### Library
libreadline developer package (>= 8.12) is the only dependency.
installing it with package manager like `apt` or `brew` is recommended.

##### macOS
`brew install readline`

##### Ubuntu
`apt-get install libreadline-dev`

### Configure and Build
`envsubst` command must exists. Install `gettext` package unless exist.

##### macOS
`brew install gettext`

##### Ubuntu
`apt-get install gettext`

Run `./configure.sh && make` to configure and build.
You may need to adjust library path manually if configure script does not work as expected.

### Debug
Run `make debug` to build in debug mode. It will enable
- compiler options (debug symbol, sanitizer)
- commandline structure logging
- latest exit value


### Supported Features
- redirection operators (<, >, <<, >>)
- commandline pipe (|)
- quoting (', ")
- parameter expansion ($WORD) and environment variables management (export, env, unset)
- bulit-in commands (cd, pwd, echo, exit)
- conditional operators (&&, ||)


### Test
`test_script.sh` receives a file that has commands to be tested. There is one test case per line. Each test case will be executed in this shell and bash. stdout, exit value pair of both will be compared to decide correctness.


Summary will be printed in stdout and details will be stored `test_log.txt`.
```
# stdout
...
#9   [OK] "echo 'a'*"
#10  [OK] "echo *$NOTHING"
#11  [OK] "echo $NOTHING*"
#12  [OK] "ls | cat -e && gcc -v || echo "$TERM""
...
```
# test_log.txt
...
[ shell output ]
42

[ bash output ]
42

[ diff ]

shell exit status = 0
bash exit status = 0
...
```
```


### Notes
- Parser is hand-coded recursive descent parser based on BNF in `bnf.md`.
- [Grammar reference](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_10)
- [Token recognition reference](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_03)
- Referenced bash's source code to determine the memory model of the commandline.
