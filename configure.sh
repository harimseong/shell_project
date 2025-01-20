#!/usr/bin/env bash

READLINE_PATHS=(
  "/opt/homebrew/Cellar/readline/*/lib"
  "/Users/${USER}/.brew/Cellar/readline/*/lib"
  "/usr/lib/*/libreadline*"
)
READLINE_PATH=""
for RL_PATH in ${READLINE_PATHS[@]}
do
  ls $RL_PATH >/dev/null 2>&1
  if [ $? -eq 0 ]; then
    RL_PATH=$(echo $RL_PATH | head -n 1)
    echo $RL_PATH | grep '.a$' >/dev/null \
    || echo $RL_PATH | grep '.dylib$' >/dev/null \
    || echo $RL_PATH | grep '.so$' >/dev/null
    if [ $? -eq 0 ]; then
      RL_PATH=$(dirname $RL_PATH)
    fi
    READLINE_PATH=$RL_PATH
    echo "libreadline found in $RL_PATH"
    break;
  fi
done

if [ -z "$READLINE_PATH" ]; then
  echo "libreadline not found in"
  echo ${READLINE_PATHS[@]}
  exit 1
fi

if [ "${READLINE_PATH:0:8}" == "/usr/lib" ]; then
  READLINE_HEADER="/usr/include"
else
  READLINE_HEADER=$(echo $READLINE_PATH | sed 's/lib/include/')
fi
export READLINE_HEADER
export READLINE_PATH
envsubst < Makefile.temp > Makefile
