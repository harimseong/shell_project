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


### Notes
- Parser is hand-coded recursive descent parser based on BNF in `bnf.md`.
- [Grammar reference](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_10)
- [Token recognition reference](https://pubs.opengroup.org/onlinepubs/9799919799/utilities/V3_chap02.html#tag_19_03)
- Referenced bash's source code to determine the memory model of the commandline.
